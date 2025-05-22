#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define bool char
#define true 1
#define false 0

const char words[10][10] = {"Pibble", "Joker", "Banana","Math","Drums","Window","Firefox", "Camera", "Zebra", "Homework"};


static bool continue_game = true;
const char* game_word = NULL;
static int length;
static int wrong_guesses = 0;
static char* display_string = NULL;
static char letters_guessed[26];
static int letters_guessed_index = 0;

char Hangman[9][15] = {
  "|-------\n",
  "|      ^\n",
  "|      O\n",
  "|\n",
  "|\n",
  "|\n",
  "|\n",
  "|\n",
  "^___________\n"
};

void print_curr_man() {
  int i;
  for (i = 0; i < 9; i++) {
    printf(Hangman[i]);
  }
}


void init_game() {
  //Seed the random to determine a random word
  srand(time(NULL));
  
  //Set the game word to the first index of a random value within words
  game_word = &words[rand()%10][0];
  int i = 0;
  
  //Set the global length for future use
  while (*(game_word+i)!= '\0') {
    length++;
    i++;
  }
  display_string = malloc(sizeof(char)*length + 1);

  //Error handling for potential failure in setting the game word
  if (length == 0) {
    printf("Something went wrong string length was %d", length);
    exit(1);
  } else {
    printf("Word initialized succesfully the word length is %d\n", length);
  }
}

//Update the game state when the user makes a guess
void update_game_state(char* action, char* guess) {
  bool wrong_guess = true;
  int i = 0;
  switch (tolower(*action)) {
    case 'l':
      while(*(game_word+i) != '\0') {
        if (tolower(*(game_word+i)) == tolower(*guess)) {
          *(display_string+i) = *(guess);
          wrong_guess = false;
        }
        i++;
      }
      letters_guessed[letters_guessed_index] = *(guess);
      letters_guessed_index++;
      break;
    case 'w':
      //Initialize word pointer and guess pointer
      char* w_ptr = NULL;
      char* g_ptr = NULL;
      w_ptr = malloc(sizeof(char)*length+1);
      g_ptr = malloc(sizeof(char)*length+1);
      for (i = 0; i < length; i++) {
        *(w_ptr+i) = tolower(*(game_word+i));
        *(g_ptr+i) = tolower(*(guess+i));
      }

      if (strncmp(w_ptr, g_ptr, length) == 0) {
        printf("You guessed the word good game");
        exit(0);
      }

      free(w_ptr);
      free(g_ptr);
      break;
    default:
      printf("Incorrect action passed try again");
      break;
  }
  
  if (wrong_guess) {
    wrong_guesses++;
    switch (wrong_guesses) {
      case 1:
        strcpy(Hangman[3], "|      |\n");
        break;
      case 2:
        strcpy(Hangman[3], "|     /|\n");
        break;
      case 3:
        strcpy(Hangman[3], "|     /|\\ \n");
      case 4:
        strcpy(Hangman[4], "|      ^\n");
        strcpy(Hangman[5], "|     /\n");
        break;
      case 5:
        strcpy(Hangman[5], "|      /\\ \n");
        break;
      case 6: 
        print_curr_man();
        printf("\n YOU LOST the word was %s, good try", game_word);
        exit(0);
    }
  } else {
    char* g_ptr = NULL;
    char* d_ptr = NULL;
    g_ptr = malloc(sizeof(char)*length+1);
    d_ptr = malloc(sizeof(char)*length+1);

    for (i = 0; i < length; i++) {
      *(g_ptr+i) = tolower(*(game_word+i));
      if (*(display_string+i) == '_') {
        return;
      } else {
        *(d_ptr+i) = tolower(*(display_string+i));
      }
    }
    if (strncmp(d_ptr, g_ptr, length) == 0) {
      printf("You won the word was %s,good game", game_word);
      exit(0);
    }
  }
}




int main() {
  //Creates a pointer to the first element of a random element in the array to use as our string pointer
  init_game();

  
  //Initialize the first game state before running the game
  
  
  print_curr_man();


  int i;
  printf("Current word:\n");
  for (i = 0; i < length; i++) {
    *(display_string+i) = '_';
  }
  printf("%s", display_string);
  printf("\nMake your first guess!\n");
  char* action = NULL;
  char* guess = NULL;

  action = malloc(sizeof(char)*3);
  guess = malloc(sizeof(char)*20);
  while (continue_game) {
    printf("Would you like to guess a letter or the word [L/W]: ");
    scanf("%1s",action);
    if (tolower(*(action)) == 'l') {
      printf("\nEnter a letter to be guessed: ");
      scanf("%1s", guess);
      update_game_state(action, guess);
    } else if (tolower(*action) == 'w') {
      printf("\nEnter a word to be guessed: ");
      scanf("%19s", guess);
      update_game_state(action, guess);
    } else {
      printf("Invalid letter passed please try again");
    }
    print_curr_man();
    printf("\n%s\n[",display_string);
    i = 0;
    while (letters_guessed[i]!=0) {
      printf("%c, ",letters_guessed[i]);
      i++;
    }
    printf("]: Letters guessed\n");
  }
  
  return 0;
}
