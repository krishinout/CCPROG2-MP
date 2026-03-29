/******************************************************************************
 *  Description     : Mantis Card Game - A text-based implementation of the 
 *                    Mantis card game by Exploding Kittens
 *  Author/s        : Danieles, Maricon
 *                    Suazon, Krisha Geane A.
 *  Section         : S12A & S22A
 *  Last Modified   : March 26,2026
 *  Acknowledgments : Based on Mantis game by Exploding Kittens,
 *                    interface.c library for UI functions
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

/**
 * Displays the main menu with game options
 * (Danieles)*/
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

/**
 * Selects players for the current game (new or existing)
 * @param gamePlayers Array to store selected players for the game
 * @param gameCount Pointer to store number of players in this game
 * @param players Array of existing player records
 * @param playerCount Pointer to number of existing players (may increase)
 * (Danieles + Suazon)*/
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

// Validate number of players
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

    //For the display of existing players
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

/**
 * Plays a complete game of Mantis
 * @param players Array of player records
 * @param playerCount Pointer to number of players in records
 * @param winningPoints Points needed to win
 * @param shuffleSeed Seed for shuffling the deck
 * (Danieles)*/
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
    printf("\n>>");
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

/**
 * Displays menu for viewing top players (by wins or scores)
 * @param player Array of player records
 * @param playerCount Number of players in the records
 * (Suazon)*/
void displayTopScorers(PlayerRecord player[], int playerCount) {
  int choice;

  iClear(0, 0, 200, 50);
  iMoveCursor(0, 0);

  displayGameTitle();
  displayHeader("TOP PLAYERS!");
  iSetColor(I_COLOR_PURPLE);
  printf("[1] Display By Highest Score\n");
  iSetColor(I_COLOR_RED);
  printf("[2] Display By Highest Win\n");
  iSetColor(I_COLOR_WHITE);

  do {
    printf("\n>> ");
    scanf("%d", &choice);

    if(choice < 1 || choice > 2) {
      iSetColor(I_COLOR_RED);
      printf("Invalid choice. Please Try Again.\n");
      iSetColor(I_COLOR_WHITE);
    }

}while(choice < 1 || choice > 2);

  if(choice == 1){
    displayByScores(player, &playerCount);
    waitForEnter();
  }
  
  else if (choice == 2){
    displayByWins(player, &playerCount);
    waitForEnter();
  }
}

/**
 * Adjusts game settings (winning points and shuffle seed)
 * @param winningPoints Pointer to current winning points
 * @param shuffleSeed Pointer to current shuffle seed
 * @param settings Pointer to game settings structure
 * (Suazon)*/
void adjustSettings(int *winningPoints, int *shuffleSeed, GameSettings *settings) {
  int choice;

  iClear(0, 0, 200, 50);
  iMoveCursor(0, 0);

  printf("Current winning points: %d\n", settings->winningPoints);
  printf("Current seed: random\n\n");

  printf("[1] Modify winning points (1-100)\n");
  printf("[2] Modify shuffling seed\n");
  printf("[3] Return\n");

  do
  {
    printf(">> ");
    scanf("%d", &choice);

    if(choice < 1 || choice > 3) {
      iSetColor(I_COLOR_RED);
      printf("\nInvalid choice. Please try again.\n\n");
      iSetColor(I_COLOR_WHITE);
    }

  }while(choice < 1 || choice > 3);

  if(choice == 1) {
     do
    {
      printf("Enter new winning score: ");
      scanf("%d", &settings->winningPoints);

      if(settings->winningPoints < 1 || settings->winningPoints > 100) {
        iSetColor(I_COLOR_RED);
        printf("\nInvalid input. Please try again.\n\n");
        iSetColor(I_COLOR_WHITE);
      }
    }while(settings->winningPoints < 1 || settings->winningPoints > 100);

    *winningPoints = settings->winningPoints;
    iSetColor(I_COLOR_GREEN);
    printf("Winning points set to %d", *winningPoints);
    iSetColor(I_COLOR_WHITE);
    printf("\n");
      waitForEnter();
  }

  else if(choice == 2) {
    printf("Enter seed (0 for random): ");
    scanf("%u", &settings->seed);

    if(settings->seed == 0) {
      *shuffleSeed = randomInt();
      iSetColor(I_COLOR_GREEN);
      printf("Seed set to random.\n\n");
       iSetColor(I_COLOR_WHITE);
    }

    else {
      *shuffleSeed = (int)settings->seed;
      iSetColor(I_COLOR_GREEN);
      printf("Seed set to %u.\n\n", settings->seed);
       iSetColor(I_COLOR_WHITE);
    }
      waitForEnter();
  }
}


int main()
{
  PlayerRecord players[MAX_PLAYERS_FILE];
  GameSettings settings;
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
      adjustSettings(&winningPoints, &shuffleSeed, &settings);

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
 * <Danieles, Maricon> (DLSU ID# 12507199)
 * <Suazon, Krisha Geane A.> (DLSU ID# 12506427)
 */
