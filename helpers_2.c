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

//for design display header
void displayHeader(const char* title)
{
  printf("\n");
  iSetColor(I_COLOR_CYAN);
  printf("╔");
  for (int i = 0; i < 53; i++) {
    printf("═");
  }
  printf("╗\n");
  
  printf("║");
  iSetColor(I_COLOR_YELLOW);
  printf("%-53s", title);
  iSetColor(I_COLOR_CYAN);
  printf("║\n");
  
  printf("╚");
  for (int i = 0; i < 53; i++) {
    printf("═");
  }
  printf("╝\n");
  iSetColor(I_COLOR_WHITE);
  printf("\n");
}

Color charToColor(char c)
{
  Color color;
  
  if (c == 'R') {
    color = RED;
  } else if (c == 'O') {
    color = ORANGE;
  } else if (c == 'Y') {
    color = YELLOW;
  } else if (c == 'G') {
    color = GREEN;
  } else if (c == 'B') {
    color = BLUE;
  } else if (c == 'I') {
    color = INDIGO;
  } else if (c == 'V') {
    color = VIOLET;
  } else {
    color = RED;
  }
  
  return color;
}

int getColorIndex(char front)
{
  int index;
  
  if (front == 'R') {
    index = 0;
  } else if (front == 'O') {
    index = 1;
  } else if (front == 'Y') {
    index = 2;
  } else if (front == 'G') {
    index = 3;
  } else if (front == 'B') {
    index = 4;
  } else if (front == 'I') {
    index = 5;
  } else if (front == 'V') {
    index = 6;
  } else {
    index = 0;
  }
  
  return index;
}

void waitForEnter()
{
  char c;
  
  printf("\nPress Enter to continue...");
  c = getchar();
  while (c != '\n') {
    c = getchar();
  }
  getchar();
}


// sorts player list by wins
void sortByWins(PlayerRecord players[], int* playerCount) {
  int i, j, max;
  PlayerRecord temp;

  for(i=0; i < *playerCount-1; i++)
  {
    max = i;

    for(j=i+1; j < *playerCount; j++)
    {
      if(players[max].games_won < players[j].games_won)
        max = j;
    }

    if(i != max) {
      temp = players[i];
      players[i] = players[max];
      players[max] = temp;
    }
  }
}

// sorts player list by highest score
void sortByScores(PlayerRecord players[], int* playerCount) {
  int i, j, max;
  PlayerRecord temp;

  for(i=0; i< *playerCount - 1; i++)
  {
    max = i;

    for(j=i+1; j< *playerCount; j++)
    {
      if(players[max].highest_score < players[j].highest_score)
        max = j;
    }

    if(i != max)
    {
      temp = players[i];
      players[i] = players[max];
      players[max] = temp;
    }
  }
}


int findPlayer(PlayerRecord players[], int count, const char* username)
{
  int index = -1;
  int i = 0;
  
  while (i < count && index == -1) {
    if (strcmp(players[i].username, username) == 0) {
      index = i;
    }
    i++;
  }
  
  return index;
}

int savePlayers(PlayerRecord players[], int count)
{
  FILE* fp = fopen("players.txt", "w");
  int result;
  
  if (fp == NULL) {
    result = 0;
  } else {
    for (int i = 0; i < count; i++) {
      fprintf(fp, "%s|%d|%d\n", 
              players[i].username, 
              players[i].games_won, 
              players[i].highest_score);
    }
    
    fclose(fp);
    result = 1;
  }
  
  return result;
}



#endif // HELPERS_2_C; Include this to prevent redefinition error