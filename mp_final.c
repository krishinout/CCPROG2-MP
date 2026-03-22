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
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "helpers_1.c"
#include "helpers_2.c"

/* ----- definitions (i.e., constants, typedefs, structs) ----- */


/* ----- function implementations ----- */

// displays the main menu (con)
void displayMainMenu()
{
  iClear(0, 0, 200, 50);
  iMoveCursor(0, 0);
  
  printf("\n");

  displayGameTitle();
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

//for the selection of players part in [1] New Game (geane + con)
void SelectGamePlayers(GamePlayer gamePlayers[], int* gameCount, PlayerRecord players[], int* playerCount){
  int numPlayers;
  int i,j,k;
  int choice;
  int alreadySelected;

  iClear(0, 0, 200, 50);
  iMoveCursor(0, 0);
  displayGameTitle();
  displayHeader("PLAYER SELECTION");

  printf("Number of players (%d-%d): ", MIN_PLAYERS, MAX_PLAYERS);
  scanf("%d", &numPlayers);

//for validation of input
  while (numPlayers < MIN_PLAYERS || numPlayers > MAX_PLAYERS){
    iSetColor(I_COLOR_RED);
    printf("Invalid. Please enter %d-%d: ", MIN_PLAYERS, MAX_PLAYERS);
    iSetColor(I_COLOR_WHITE);
    scanf("%d", &numPlayers);
  }

  *gameCount = numPlayers;

  //selection of players
  for (i=0; i<numPlayers; i++){
    printf("\nSelect Player %d:\n", i + 1);
    printf("[0] <Add new player>\n");

    //for the display of existing players
    for (j = 0; j < *playerCount; j++) {
      printf("[%d] %s\n", j + 1, players[j].username);
  }

  printf(">> ");
  scanf("%d", &choice);

  if (choice == 0){
    char newUsername[MAX_USERNAME];
    AddNewPlayer(players, playerCount, newUsername);
    
    strcpy(gamePlayers[i].username, newUsername);
    gamePlayers[i].tank_count = 0;
    gamePlayers[i].score_count = 0;
    gamePlayers[i].score_points = 0;
    gamePlayers[i].is_new = 1;

    iSetColor(I_COLOR_GREEN);
    printf("New player added to game!\n");
    iSetColor(I_COLOR_WHITE);
  } else if (choice >=1 && choice <= *playerCount) {
   alreadySelected = 0;
      for (k = 0; k < i; k++) {
        if (strcmp(gamePlayers[k].username, players[choice - 1].username) == 0) {
          alreadySelected = 1;
        }
      }
      
      if (alreadySelected == 1) {
        iSetColor(I_COLOR_RED);
        printf("Player already selected! Choose a different player.\n");
        iSetColor(I_COLOR_WHITE);
        i--;  // Repeat this player selection
      } else {
        strcpy(gamePlayers[i].username, players[choice - 1].username);
        gamePlayers[i].tank_count = 0;
        gamePlayers[i].score_count = 0;
        gamePlayers[i].score_points = 0;
        gamePlayers[i].is_new = 0;

        iSetColor(I_COLOR_GREEN);
        printf("Selected: %s\n", gamePlayers[i].username);
        iSetColor(I_COLOR_WHITE);
      }
  } else {
    iSetColor(I_COLOR_RED);
    printf("Invalid choice. Please try again.\n");
    iSetColor(I_COLOR_WHITE);
    i--;
    }
  }
}

//playgame function
void playGame(PlayerRecord players[], int* playerCount, int winningPoints, int shuffleSeed){
  GameState game;
  int choice;

  game.player_count = 0;
  game.winning_points = winningPoints;
  game.deck_size = loadDeck(game.deck, "mantis.txt");

  shuffle(game.deck, game.deck_size, sizeof(Card), shuffleSeed);
  SelectGamePlayers(game.players, &game.player_count, players, playerCount);
  dealInitialCards(&game);

  game.current_player = 0;
  game.game_over = 0;

  while(game.game_over == 0){
    DisplayGameState (&game);
    printf("%s's turn:\n", game.players[game.current_player].username);
    printf("[1] Try to Score\n");
    printf("[2] Try to Steal\n");
    printf(">>");
    scanf("%d", &choice);

    while(choice != 1 && choice != 2){
      iSetColor(I_COLOR_RED);
      printf("Invalid. Please enter 1 or 2: ");
      iSetColor(I_COLOR_WHITE);
      scanf("%d", &choice);
    }

    if (choice ==1){
      TryToScore(&game, game.current_player);
    } else {
      TryToSteal(&game, game.current_player);
    }

    game.game_over = CheckGameOver(&game);

    if (game.game_over == 0){
      game.current_player = game.current_player + 1;
      if (game.current_player >= game.player_count){
        game.current_player = 0; 
      }
    }
    waitForEnter();
  }
  ShowGameResults(&game, players, playerCount);
  savePlayers(players, *playerCount); 

  waitForEnter();
}


//top scorers function
void displayTopScorers(PlayerRecord player[], int playerCount) {
  int choice;

 // iClear(0, 0, 200, 50);
 // iMoveCursor(0, 0);

  printf("[1] Display By Highest Score\n");
  printf("[2] Display By Highest Win\n");

  do {
    printf(">> ");
    scanf("%d", &choice);

    if(choice < 1 || choice > 2)
      printf("Invalid choice. Please Try Again.\n");

}while(choice < 1 || choice > 2);

  if(choice == 1){
    displayByScores(player, &playerCount);
    waitForEnter();
  }
  
  else if (choice == 2){
    displayByWins(player, &playerCount);}
    waitForEnter();
}


//settings function


int main()
{
  PlayerRecord players[MAX_PLAYERS_FILE];
  int playerCount = 0;
  int winningPoints;
  int shuffleSeed;
  int choice;

  winningPoints = WINNING_POINTS_DEFAULT;

  initRandom();
  shuffleSeed = randomInt();
  loadPlayers(players, &playerCount);
  iHideCursor();

  do {
    displayMainMenu();
    scanf("%d", &choice);

    if (choice == 1){
      playGame(players, &playerCount, winningPoints, shuffleSeed);

    } else if (choice == 2){
      displayTopScorers(players, playerCount);


    } else if (choice == 3) {
      printf("settings");

    }
  } while (choice != 4);

  iShowCursor();
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
