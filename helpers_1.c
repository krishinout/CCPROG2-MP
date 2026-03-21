/******************************************************************************
 *  Description     : Helper functions for the Mantis card game
 *  Author/s        : Danieles, Maricon
 *                    Suazon, Krisha Geane A.
 *  Section         : S12A & S22A
 *  Last Modified   : March 12, 2026
 ******************************************************************************/

#ifndef HELPERS_1_C // Include this to prevent redefinition error
#define HELPERS_1_C // Include this to prevent redefinition error

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "defs.h"

/******************************************************************************
 * NOTE: These functions are placed here in helpers_1.c to demonstrate code
 * modularization across multiple files. You may move them to different files
 * if it better fits your code organization.
 ******************************************************************************/

 void displayGameTitle()
{
  iSetColor(I_COLOR_YELLOW);
  printf("    ##    ##   ###    ##    ##  ######  ###### ######\n");
  iSetColor(I_COLOR_YELLOW);
  printf("    ###  ###  ##  ##  ###   ##    ##      ##   ##    \n");
  iSetColor(I_COLOR_YELLOW);
  printf("    ## ## ##  ######  ## ## ##    ##      ##   ######\n");    
  iSetColor(I_COLOR_YELLOW);
  printf("    ##    ##  ##  ##  ##   ###    ##      ##       ##\n");  
  iSetColor(I_COLOR_YELLOW); 
  printf("    ##    ##  ##  ##  ##    ##    ##    #####  ######\n\n");
}



#endif // HELPERS_1_C; Include this to prevent redefinition error