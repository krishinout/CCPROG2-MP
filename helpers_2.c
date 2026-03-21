/******************************************************************************
 *  Description     : <short description of the file>
 *  Author/s        : <student1 full name (last name, first name)>
 *                    <student2 full name (last name, first name)>
 *  Section         : <your section>
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef HELPERS_2_C // Include this to prevent redefinition error
#define HELPERS_2_C // Include this to prevent redefinition error

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

#endif // HELPERS_2_C; Include this to prevent redefinition error