/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Classical game called hangman
 *
 *        Version:  1.0
 *       Compiler:  gcc
 *
 * =====================================================================================
 */

#include <string.h> /* strcmp fn */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> /* C99 only */
#include <ctype.h> /* for toupper function */

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32im"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/* external variables*/
char secret_sentence[250] = "This is secret message";
char sentence_to_guess[250];
char current_char;
int letters_used[26][2];
int count;
int num_of_missed_ch;
bool has_won, game_over, char_exists;


/* prototypes*/
void new_game(void);
void read_guess(void);
void analyse_guess(void);
void print_result(void);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  Calls read_guess, analyse_guess, print_result repeatedly.
 * =====================================================================================
 */

int main ( void )
{
  new_game();
  
  for (;;){
    read_guess();
    analyse_guess();
    print_result();
  }
}				/* ----------  end of function main  ---------- */

 /* 
 * ===  FUNCTION  ======================================================================
 *         Name:  new_game
 *  Description:  Sets external variables to their default values
 * =====================================================================================
 */
void new_game (void)
{
 
  /* set count to 0 */
  count = 0;
  num_of_missed_ch = 0;
  has_won = false;
  game_over = false;
  
  /* please check this number 26*/
  int i, ascii = 97;

  for(i = 0; i < 26; i++){
    letters_used[i][0] = ascii;
    letters_used[i][1] = false;
    ascii++; 
  }
  /* Generate secret sentence*/

  /* Generate masked secret sentence */
  for (i = 0; i <= 250; i++){
    if (secret_sentence[i] == ' ')
      sentence_to_guess[i] = ' ';
    else if (secret_sentence[i] !=0)
      sentence_to_guess[i] = '_';
  }

  print_result();

}		/* -----  end of function new_game  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  read_guess
 *  Description:  Reads the guess into the external variable current_char and updates
 *                external variable letters_used array to keep track on used chars; 
 *                checks for bad guess and dublicates.
 * =====================================================================================
 */
void read_guess (void)
{
  
  bool bad_char, dublicated_char;
  char ch, letter_ch, letter; 
  int i, chars_read = 0;
  
  if (game_over){
 
    /* Checks if user wishes to play more*/
    while (chars_read < 1){ 
      bad_char = false;
      printf("Do you wanna play again? yes[y], no[n]: ");
     
      letter_ch = tolower(getchar());   
      switch (letter_ch){
        case '0': exit (EXIT_SUCCESS);
        case 'y': letter = 'y'; break;
        case 'n': letter = 'n'; break;  
        default: bad_char = true;                
      }
   
      while ((ch = getchar()) != '\n')
        if (ch != ' ') bad_char = true;
    
      if (bad_char){
        printf(ANSI_COLOR_RED "Bad char; ignored.\n" ANSI_COLOR_RESET);   
      }else{
        if(letter == 'y'){
          new_game();
          chars_read++;
        }else{
          exit (EXIT_SUCCESS);
        } 
      }   
    }
    chars_read = 0;
  }
  /* input for char to guess */
  while (chars_read < 1){
    
    bad_char = false;
    dublicated_char = false;
           
    printf("Enter a char: ");
    
    letter_ch = tolower(getchar());
    switch (letter_ch){
      case '0': exit (EXIT_SUCCESS);
      case 'a': letter = 'a'; break;
      case 'b': letter = 'b'; break;
      case 'c': letter = 'c'; break;
      case 'd': letter = 'd'; break;
      case 'e': letter = 'e'; break;
      case 'f': letter = 'f'; break;
      case 'g': letter = 'g'; break; 
      case 'h': letter = 'h'; break;
      case 'i': letter = 'i'; break;
      case 'j': letter = 'j'; break;
      case 'k': letter = 'k'; break;
      case 'l': letter = 'l'; break;
      case 'm': letter = 'm'; break;
      case 'n': letter = 'n'; break;
      case 'o': letter = 'o'; break;
      case 'p': letter = 'p'; break;
      case 'q': letter = 'q'; break;    
      case 'r': letter = 'r'; break;
      case 's': letter = 's'; break;
      case 't': letter = 't'; break; 
      case 'u': letter = 'u'; break;
      case 'v': letter = 'v'; break;          
      case 'w': letter = 'w'; break;
      case 'x': letter = 'x'; break;
      case 'y': letter = 'y'; break;
      case 'z': letter = 'z'; break;          
      default:  bad_char = true;          
    }

    /* Check for dublicated chars*/
    for (i=0; i <= 26; i++){     
      if (letters_used[i][0] == letter && letters_used[i][1] == true)
        dublicated_char = true;      
    }

    while ((ch = getchar()) != '\n')
        if (ch != ' ') bad_char = true;

    if (bad_char)
      printf(ANSI_COLOR_RED "Bad char; ignored.\n" ANSI_COLOR_RESET);   
    else if(dublicated_char)
      printf(ANSI_COLOR_RED "Dublicated char; ignored.\n" ANSI_COLOR_RESET);
    else {
     count++;
      chars_read++;
      current_char = letter;
      /* insert char into letters_used array */
      for (i = 0; i <= 26; i++){      
        if (letters_used[i][0] == letter)
          letters_used[i][1] = true;      
      }      
    }     
  }


}		/* -----  end of function read_guess  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  analyse_guess
 *  Description:  Check is char is inside secret word and if yes then updates word to guess
 *                variable, an check if user has won the game. or lost and offer newgame option
 * =====================================================================================
 */
void analyse_guess (void)
{
  char_exists = false;
  has_won = false;
  game_over = false;
  int i;

  /* Check if char exists */
  for (i = 0; i <=250; i++){
    if (secret_sentence[i] == current_char || secret_sentence[i] == toupper(current_char)){
      char_exists = true;     
    }    
  }

  /* Update */
  if (char_exists)
    for (i = 0; i <= 250; i++){
      if (secret_sentence[i] == current_char)
        sentence_to_guess[i] = current_char;
      else if (secret_sentence[i] == toupper(current_char))
        sentence_to_guess[i] = toupper(current_char); 
    }
  else
    num_of_missed_ch++;

  /*  Check if user won or game is over*/
  if ( strcmp(secret_sentence, sentence_to_guess) == 0){
    has_won = true; 
    game_over= true;    
  }
  else if (num_of_missed_ch == 5){
    game_over = true;
    has_won = false;
  }
  
}		/* -----  end of function analyse_guess  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  print_result
 *  Description:  Prints out chars used, word to guess and hangman frame. 
 *                Also takes care to print out if winning/losing message. 
 * =====================================================================================
 */
void print_result ( void )
{
  int i;

  printf("\033[2J\033[1;1H");/* for kind of clearing the screen in *nix */ 

  /* Hangman frames */
  switch (num_of_missed_ch){
    case 0:        
      printf("____________   \n");
      printf("|              \n");
      printf("|              \n");
      printf("|              \n");
      printf("|              \n");
      printf("|              \n");
      printf("|              \n");
      printf("|              \n");
      printf("|              \n");
      printf("|              \n");
      printf("|              \n");
      printf("============== \n");
      break;   
    case 1:     
     printf("____________   \n");
     printf("|      |       \n");
     printf("|      |       \n");
     printf("|     ( )      \n");
     printf("|              \n");
     printf("|              \n");
     printf("|              \n");
     printf("|              \n");
     printf("|              \n");
     printf("|              \n");
     printf("|              \n");
     printf("============== \n");
      break;
    case 2:     
     printf("____________   \n");
     printf("|      |       \n");
     printf("|      |       \n");
     printf("|     ( )      \n");
     printf("|      |       \n");
     printf("|     /        \n");
     printf("|              \n");
     printf("|              \n");
     printf("|              \n");
     printf("|              \n");
     printf("|              \n");
     printf("============== \n");
      break;
    case 3:
     printf("____________   \n");
     printf("|      |       \n");
     printf("|      |       \n");
     printf("|     ( )      \n");
     printf("|      |       \n");
     printf("|     / \\     \n");
     printf("|              \n");
     printf("|              \n");
     printf("|              \n");
     printf("|              \n");
     printf("|              \n");
     printf("============== \n");
      break;
    case 4:
     printf("____________   \n");
     printf("|      |       \n");
     printf("|      |       \n");
     printf("|     ( )      \n");
     printf("|      |       \n");
     printf("|     /|\\     \n");     
     printf("|      |       \n");
     printf("|     /        \n");     
     printf("|              \n");
     printf("|              \n");
     printf("|              \n");
     printf("============== \n");
      break;
    default:
     printf("____________   \n");
     printf("|      |       \n");
     printf("|      |       \n");
     printf("|     ( )      \n");
     printf("|      |       \n");
     printf("|     /|\\     \n");     
     printf("|      |       \n");
     printf("|     / \\     \n");
     printf("|              \n");
     printf("|              \n");
     printf("|              \n");
     printf("============== \n");
  }

  /* print sentence_to_guess */
  for (i = 0; i <= 250; i++){
    if (sentence_to_guess[i] == ' ')
      printf("-");
    else if (sentence_to_guess[i] == 0)
      break;
    else      
      printf("%c", sentence_to_guess[i]);
    
    printf(" ");
  }
  printf("\n");

  /* Print out used chars */
  printf(ANSI_COLOR_YELLOW "Chars used: " ANSI_COLOR_RESET);
  for (i = 0; i <= 26; i++){
    if (letters_used[i][1] == true)
      printf(ANSI_COLOR_MAGENTA"%c "ANSI_COLOR_RESET, letters_used[i][0]);
  }
  printf("\n");  
  
  if (game_over){
    printf("Game over!\n");
    if (has_won)
      printf("Conqratulate, You won!!\n");    
    else
     printf("Sucker..\n"); 
  }
}		  /* -----  end of function print_result  ----- */

