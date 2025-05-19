#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define bool char
#define true 1
#define false 0

//Checks if the inputs passed are valid input
int check_inputs(char* str) {
  return strcmp(str, "rock") || strcmp(str, "scissors"), strcmp(str, "paper");
}

int main() {
  printf("Would you like to play rock paper scissors. [y/N]\n");
  char* answer;
  scanf("%s", answer);
  if (*answer == 'n' || *answer == 'N') {
    printf("Ending game");
    return 0;
  }
  int comp_num = rand()%3;
  
  char* player;
  printf("Enter your choice (valid inputs: rock, paper, scissors) anything else results in error\n");
  scanf("%s", player);
  if (!check_inputs) {
    printf("invalid input you inputted '%s' which wasnt an allowed entry run the program again to play");
    return 0;
  }

  //Assign a random string with an extra char for terminator byte
  char* comp_choice;
  switch (comp_num){
  case 0:
    comp_choice = malloc(sizeof("rock")+1);
    strcpy(comp_choice, "rock");
    break;
  case 1:
    comp_choice = malloc(sizeof("paper")+1);
    strcpy(comp_choice, "paper");
    break;
  case 2:
    comp_choice = malloc(sizeof("scissors")+1);
    strcpy(comp_choice, "scissors");
    break;
  }
  
  if (*comp_choice == *player) {
    printf("There was a tie good game you picked %s the computer picked %s", player, comp_choice);
    return 0;
  }
  
  char c = *(comp_choice+0);
  char p = *(player+0);
  if ((c == 'r' && p == 's') || (c == 's' && p == 'p') || (c == 'p' && p == 'r')) {
    printf("Computer wins, you picked %s, the computer picked %s", player, comp_choice);
  } else {
    printf("Player wins, you picked %s, the computer picked %s", player, comp_choice);
  }
  return 0;
}
