/******************************************************************************
 *  Description     : Mantis Card Game - A text-based implementation of the 
 *                    Mantis card game by Exploding Kittens
 *  Author/s        : <student1 full name (last name, first name)>
 *                    <student2 full name (last name, first name)>
 *  Section         : S12A & S22A
 *  Last Modified   : March 25,2026
 *  Acknowledgments : <list of references used in the making of this project>
 ******************************************************************************/

/* ----- preprocessor directives ----- */
#include <stdio.h>

#include "defs.h"
#include "helpers_1.c"
#include "helpers_2.c"
#include "interface.c"

/* ----- definitions (i.e., constants, typedefs, structs) ----- */


/* ----- function implementations ----- */

void displayMainMenu()
{
  iClear(0, 0, 200, 50);
  iMoveCursor(0, 0);
  
  printf("\n");
  iSetColor(I_COLOR_CYAN);
  printf("╔");
  for (int i = 0; i < 78; i++) {
    printf("═");
  }
  printf("╗\n");
  
  printf("║");
  iSetColor(I_COLOR_YELLOW);
  printf("%-78s", "MANTIS CARD GAME");
  iSetColor(I_COLOR_CYAN);
  printf("║\n");
  
  printf("╚");
  for (int i = 0; i < 78; i++) {
    printf("═");
  }
  printf("╝\n");
  iSetColor(I_COLOR_WHITE);
  printf("\n");
  
  iSetColor(I_COLOR_GREEN);
  printf("  [1] New Game\n");
  iSetColor(I_COLOR_BLUE);
  printf("  [2] Top Players\n");
  iSetColor(I_COLOR_PURPLE);
  printf("  [3] Settings\n");
  iSetColor(I_COLOR_RED);
  printf("  [4] Exit\n\n");
  iSetColor(I_COLOR_WHITE);
  printf("  Enter your choice: ");
}

int main()
{
  /* your project code */



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
