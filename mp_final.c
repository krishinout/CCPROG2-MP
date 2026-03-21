/******************************************************************************
 *  Description     : <short description of the project>
 *  Author/s        : <student1 full name (last name, first name)>
 *                    <student2 full name (last name, first name)>
 *  Section         : <your section>
 *  Last Modified   : <date when last revision was made>
 *  Acknowledgments : <list of references used in the making of this project>
 ******************************************************************************/

/* ----- preprocessor directives ----- */
#include <stdio.h>

#include "defs.h"
#include "helpers_1.c"
#include "helpers_2.c"

/* ----- definitions (i.e., constants, typedefs, structs) ----- */

/* ----- function implementations ----- */

/**
 *  Computes the average of the non-negative numbers from a given list of numbers
 *  @param arr The starting address of the array containing the list of numbers
 *  @param arrSize The size of the array
 *  @return The average of the non-negative numbers from the list of numbers
 *  @pre arr can include positive numbers, negative numbers, and zeros
 *  @pre arrSize is the correct size of arr
 */
float getAverage(int arr[], int arrSize)
{
  float average;
  int sum = 0, n = 0, i;

  for (i = 0; i < arrSize; i++)
    if (arr[i] >= 0)
    {
      sum += arr[i];
      n++;
    }

  if (n == 0) // prevent divide by zero
    average = 0;
  else
    average = sum / (float)n;

  return average;
}

int main()
{
  /* your project code */

  Coordinate pointsArray[ARR_SIZE] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  int currentArrSize = 5;

  // Sample call of a function from helpers_2.c to initialize random number generator
  initRandom();

  // Sample call of a function from helpers_2.c to get a random seed
  int seed = randomInt();

  // Sample call of a function from helpers_1.c to display initial array
  printf("Initial array:\n  ");
  displayCoodinates(pointsArray, currentArrSize);

  printf("----- Different seeds produce different shuffle arrangements -----\n\n");

  // Sample call of a function from helpers_2.c to shuffle the array
  shuffle(pointsArray, currentArrSize, sizeof(Coordinate), seed);

  // Sample call of a function from helpers_1.c to display shuffled array
  printf("Shuffled array (seed: %d)\n  ", seed);
  displayCoodinates(pointsArray, currentArrSize);

  // Shuffle again with a different random seed
  seed = randomInt();
  shuffle(pointsArray, currentArrSize, sizeof(Coordinate), seed);
  printf("Shuffled array (seed: %d)\n  ", seed);
  displayCoodinates(pointsArray, currentArrSize);

  // Providing the same seed produces the same shuffle arrangement
  printf("----- Same seed produces the same shuffle arrangement -----\n\n");

  shuffle(pointsArray, currentArrSize, sizeof(Coordinate), 999);
  printf("Shuffled array (seed: 999):\n  ");
  displayCoodinates(pointsArray, currentArrSize);
  printf("Shuffled array (seed: 999):\n  ");
  displayCoodinates(pointsArray, currentArrSize);

  return 0;
}

/**
 * This is to certify that this project is my/our own work, based on my/our personal
 * efforts in studying and applying the concepts learned. I/We have constructed the
 * functions and their respective algorithms and corresponding code by myself/ourselves.
 * The program was run, tested, and debugged by my/our own efforts. I/We further certify
 * that I/we have not copied in part or whole or otherwise plagiarized the work of other
 * students and/or persons, nor did I employ the use of AI in any part of the deliverable.
 *
 * <student1 full name (last name, first name)> (DLSU ID# <number>)
 * <student2 full name (last name, first name)> (DLSU ID# <number>)
 */
