/******************************************************************************
 *  Description     : Helper functions for the Mantis card game
 *  Author/s        : Danieles, Maricon
 *                    Suazon, Krisha Geane A.
 *  Section         : S12A & S22A
 *  Last Modified   : March 12, 2026
 ******************************************************************************/

#ifndef HELPERS_2_C // Include this to prevent redefinition error
#define HELPERS_2_C // Include this to prevent redefinition error

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "defs.h"


/******************************************************************************
 * NOTE: These functions are placed here in helpers_2.c to demonstrate code
 * modularization across multiple files. You may move them to different files
 * if it better fits your code organization.
 ******************************************************************************/

/**
 * Initializes the random number generator
 * @pre Should only be called once at the start of the program
 */
void initRandom()
{
  srand(time(0)); // Initialize the seed for the random number generator
}

/**
 * Generates and returns a random integer between 0 and 99
 * @return A random integer between 0 and 99
 * @pre initRandom() has been called prior to this function call
 */
int randomInt()
{
  return rand() % 100; // Generate a random number from 0 to 99
}

/**
 * Shuffles an array of any data type using the Fisher-Yates algorithm
 * @param array Pointer to the array to be shuffled
 * @param n Number of elements in the array
 * @param elem_size Size of each element in the array (use sizeof(data_type))
 * @param seed For setting the random order (providing thes same seed value
 *          will produce the same shuffle arrangement)
 */
void shuffle(void *array, size_t n, size_t elem_size, unsigned int seed)
{
  unsigned char *arr = (unsigned char *)array;
  srand(seed); // Set the seed for reproducibility

  for (size_t i = n - 1; i > 0; i--)
  {
    size_t j = rand() % (i + 1); // Random index from 0 to i

    // Swap elements
    unsigned char temp[elem_size];
    memcpy(temp, arr + i * elem_size, elem_size);
    memcpy(arr + i * elem_size, arr + j * elem_size, elem_size);
    memcpy(arr + j * elem_size, temp, elem_size);
  }
}

/**
 * Verifies if created username is unique and does not exceed 36 characters
 * @param playerList is a data struct array that represents the list of existing players and their information
 * @param playerCount is an integer pointer that represents the number of existing players
 * @param newUsername is a string that represents the newly created username
 * @return 0 if username is NOT valid and 1 if otherwise
 */
int IsUsernameValid(PlayerRecord playerList, int playerCount, char newUsername[]) // no need to dereference since di naman imomodify value ng playerCount
{
  int i, valid = 1;

  if (strlen(newUsername)>MAX_USERNAME) // first checks if username doesnt exceed 36 char
      valid = 0;

  for(i=0; i< playerCount; i++)
    if(strcmp(playerList.username, newUsername) == 0)
      valid = 0;

  return valid;
}

/**
 * Adds new player to player list
 * @param playerList is data struct array that represents the list of existing players and their information
 * @param playerCount is an integer pointer that represents the number of existing players
 */
void addNewPlayer(playerStats playerList[], int *playerCount)
{
  char newUsername[MAX_USERNAME+1];
  int addedPlayer = 0;

  do // uses do to repeat until valid na username and player is added succesfully
  {
    printf("Enter new username: ");
    scanf("%s", newUsername);

    if(IsUsernameValid(playerList, *playerCount, newUsername) == 0) // calls function to validate username
      printf("Username is invalid. Please Try Again.\n");

    else
    {
      strcpy(playerList[*playerCount].username, newUsername); // doesn't do assignment agad since need to set every other element to 0
      playerList[*playerCount].wins = 0;
      playerList[*playerCount].games = 0;
      playerList[*playerCount].highestScore = 0;
      (*playerCount)++; 
      addedPlayer = 1;
    }
  }while(addedPlayer == 0);
}

void addPlayer(GamePlayer game_players[], PlayerRecord players[], int* count, const char* username)
{
  valid = 0;
      do {
        printf("Enter new username (max %d chars): ", MAX_USERNAME - 1);
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0;
        
        if (strlen(username) == 0) {
          iSetColor(I_COLOR_RED);
          printf("Username cannot be empty.\n");
          iSetColor(I_COLOR_WHITE);
        } else if (strlen(username) >= MAX_USERNAME) {
          iSetColor(I_COLOR_RED);
          printf("Username too long. Max %d characters.\n", MAX_USERNAME - 1);
          iSetColor(I_COLOR_WHITE);
        } else if (findPlayer(players, player_count, username) >= 0) {
          iSetColor(I_COLOR_RED);
          printf("Username already exists. Choose another.\n");
          iSetColor(I_COLOR_WHITE);
        } else {
          valid = 1;
        }
      } while (valid == 0);

  strcpy(game_players[i].username, username);
      game_players[i].tank_count = 0;
      game_players[i].score_count = 0;
      game_players[i].score_points = 0;
      game_players[i].is_new = 1;
}

#endif // HELPERS_2_C; Include this to prevent redefinition error