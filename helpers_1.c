/******************************************************************************
 *  Description     : Helper functions for the Mantis card game
 *  Author/s        : Danieles, Maricon
 *                    Suazon, Krisha Geane A.
 *  Section         : S12A & S22A
 *  Last Modified   : March 25, 2026
 ******************************************************************************/

#ifndef HELPERS_1_C // Include this to prevent redefinition error
#define HELPERS_1_C // Include this to prevent redefinition error

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "defs.h"
#include "interface.c"
#include "helpers_2.c"

/******************************************************************************
 * NOTE: These functions are placed here in helpers_1.c to demonstrate code
 * modularization across multiple files. You may move them to different files
 * if it better fits your code organization.
 ******************************************************************************/

/**
 * Displays the game title in ASCII art format
 * (Suazon)*/
 void displayGameTitle()
{
  iSetColor(I_COLOR_YELLOW);
  printf("    ##    ##   ####   ##    ##  ######  ###### ######\n");
  iSetColor(I_COLOR_YELLOW);
  printf("    ###  ###  ##  ##  ###   ##    ##      ##   ##    \n");
  iSetColor(I_COLOR_YELLOW);
  printf("    ## ## ##  ######  ## ## ##    ##      ##   ######\n");    
  iSetColor(I_COLOR_YELLOW);
  printf("    ##    ##  ##  ##  ##   ###    ##      ##       ##\n");  
  iSetColor(I_COLOR_YELLOW); 
  printf("    ##    ##  ##  ##  ##    ##    ##    #####  ######\n\n");
}

/**
 * Validates if a username is valid and unique
 * @param players Array of existing player records
 * @param playerCount Number of existing players
 * @param newUsername Username to validate
 * @return 1 if valid, 0 if invalid
 * @pre players array contains valid player records
 * @pre playerCount is the correct size of players array
 * (Suazon)*/
int IsUsernameValid(PlayerRecord players[], int playerCount, char newUsername[])
{
  int i, valid = 1;

  if (strlen(newUsername) > MAX_USERNAME)
    valid = 0;

  for (i = 0; i < playerCount; i++)
    if (strcmp(players[i].username, newUsername) == 0)
      valid = 0;

  return valid;
}

/**
 * Adds a new player to the records and saves to file immediately
 * @param players Array of player records
 * @param playerCount Pointer to number of players (will be incremented)
 * @param newUsername Buffer to store the new username
 * @return 1 if successful
 * @pre players array has space for at least one more player
 * @pre playerCount points to a valid integer less than MAX_PLAYERS_FILE
 * (Danieles + Suazon)*/
int AddNewPlayer(PlayerRecord players[], int* playerCount, char newUsername[])
{
  int valid = 0;
  FILE* fp;
  int i;

  do { 
    printf("Enter new username (max %d chars): ", MAX_USERNAME);
    scanf("%s", newUsername);

    valid = IsUsernameValid(players, *playerCount, newUsername);

    if (valid == 0){
      iSetColor(I_COLOR_RED);
      printf("Invalid username. Must be unique and max %d chars.\n", MAX_USERNAME);
      iSetColor(I_COLOR_WHITE);
    }
  } while (valid == 0);

  // Add to memory
  strcpy(players[*playerCount].username, newUsername);
  players[*playerCount].games_won = 0;
  players[*playerCount].highest_score = 0;
  (*playerCount)++;

  // Save to file immediately
  fp = fopen("players.txt", "w");
  if (fp != NULL){
    for (i=0; i < *playerCount; i++){
      fprintf(fp, "%s|%d|%d\n", 
        players[i].username, 
        players[i].games_won, 
        players[i].highest_score);
    }
    fclose(fp);
  }
 
  iSetColor(I_COLOR_GREEN);
  printf("New player '%s' added!\n", newUsername);
  iSetColor(I_COLOR_WHITE);

  return 1;
}

/**
 * Loads existing players from players.txt file into memory
 * @param players Array to store player records
 * @param playerCount Pointer to store number of players loaded
 * @pre players array has size at least MAX_PLAYERS_FILE
 * (Danieles)*/
void loadPlayers(PlayerRecord players[], int* playerCount){
  FILE* fp;
  int count=0;
  int readResult;

  fp = fopen("players.txt", "r");
  *playerCount = 0;

  if (fp != NULL){
    readResult = fscanf(fp, "%36[^|]|%d|%d\n", 
      players[count].username, 
      &players[count].games_won,
      &players[count].highest_score);

    while (readResult == 3 && count < MAX_PLAYERS_FILE){
      count = count+1;
      if (count < MAX_PLAYERS_FILE){
        readResult = fscanf(fp, "%36[^|]|%d|%d\n", 
          players[count].username, 
          &players[count].games_won, 
          &players[count].highest_score);
      }
    }
    fclose(fp);
    *playerCount = count;
  }
}

/**
 * Loads the deck from mantis.txt file
 * @param deck Array to store cards
 * @param filename Name of the file to load
 * @return Number of cards loaded
 * @pre deck array has size at least DECK_SIZE
 * (Danieles)*/
int loadDeck(Card deck[], const char* filename){
  FILE* fp;
  int count = 0;
  int readResult;

  fp = fopen(filename, "r");

  if(fp != NULL) {
    readResult = fscanf(fp, " %c | %c%c%c %d\n", &deck[count].front, 
      &deck[count].back1, &deck[count].back2, 
      &deck[count].back3,&deck[count].points);

    while(readResult == 5 && count < DECK_SIZE){
      count = count + 1;
      if (count < DECK_SIZE) {
        readResult = fscanf(fp, " %c | %c%c%c %d\n", &deck[count].front, 
      &deck[count].back1, &deck[count].back2, 
      &deck[count].back3,&deck[count].points);
      }
    }
    fclose(fp);

  }
  return count;
}

/**
 * Draws the top card from the deck (index 0) and shifts remaining cards
 * @param state Pointer to the game state
 * @param card Pointer to store the drawn card
 * @return 1 if successful, 0 if deck is empty
 * @pre state is a valid GameState
 * (Danieles))*/
int DrawnCard(GameState* state, Card* card){
  int result = 0;
  int i;

// draws at index 0
  if (state->deck_size > 0){
    *card = state->deck[0];

  //for shifting the cards in the deck
    for (i=0; i < state->deck_size - 1; i++){
      state->deck[i] = state->deck[i+1];
    }

    state->deck_size = state->deck_size - 1;
    result = 1;
  }
  return result;
}

/**
 * Deals 4 initial cards to each player at the start of the game
 * @param state Pointer to the game state
 * @pre state contains valid players and a shuffled deck
 * (Danieles)*/
void dealInitialCards (GameState* state){
  int i, j;
  Card drawnCard;

  for(i=0; i < state->player_count; i++){
    for(j=0; j<HAND_SIZE; j++){
      if (DrawnCard(state, &drawnCard) == 1){
        state->players[i].tank[j] = drawnCard;
        state->players[i].tank_count++;
      }
    }
  }
}

/**
 * Displays a player's card counts in a colorful box format
 * @param player Pointer to the player
 * (Danieles + Suazon)*/
void DisplayCardCounts(GamePlayer* player){
  int colorCounts[7] = {0};
  int i;
  int index;

  for (i=0; i<player->tank_count; i++){
    index = getColorIndex(player->tank[i].front);
    colorCounts[index]++;
  }
  iSetColor(I_COLOR_YELLOW);
  printf("%s\n", player->username);
  iSetColor(I_COLOR_WHITE);

  printf(" _____  _____  _____  _____  _____  _____  _____\n");
  iSetColor(I_COLOR_RED);     
  printf("|  R  |");
  iSetColor(I_COLOR_RED);     
  printf("|  O  |");
  iSetColor(I_COLOR_YELLOW);  
  printf("|  Y  |");
  iSetColor(I_COLOR_GREEN);   
  printf("|  G  |");
  iSetColor(I_COLOR_BLUE);    
  printf("|  B  |");
  iSetColor(I_COLOR_BLUE);    
  printf("|  I  |");
  iSetColor(I_COLOR_PURPLE);  
  printf("|  V  |");
  iSetColor(I_COLOR_WHITE);
  printf("\n");
  printf("|_____||_____||_____||_____||_____||_____||_____|\n");
  iSetColor(I_COLOR_RED);     
  printf("| %2d  |", colorCounts[0]);
  iSetColor(I_COLOR_RED);    
   printf("| %2d  |", colorCounts[1]);
  iSetColor(I_COLOR_YELLOW);  
  printf("| %2d  |", colorCounts[2]);
  iSetColor(I_COLOR_GREEN);   
  printf("| %2d  |", colorCounts[3]);
  iSetColor(I_COLOR_BLUE);    
  printf("| %2d  |", colorCounts[4]);
  iSetColor(I_COLOR_BLUE);    
  printf("| %2d  |", colorCounts[5]);
  iSetColor(I_COLOR_PURPLE);  
  printf("| %2d  |", colorCounts[6]);
  iSetColor(I_COLOR_WHITE);
  printf("\n");
  printf("|_____||_____||_____||_____||_____||_____||_____|\n");
  printf("\n");
  printf("Score: %2d pts | Score Pile: %2d | Tank Pile: %2d\n\n", 
    player->score_points, player->score_count, player->tank_count);

}

/**
 * Displays the current game state including all players' cards
 * @param state Pointer to the game state
 * (Danieles + Suazon)*/
void DisplayGameState(GameState* state){
  int i;
  
  iClear(0, 0, 200, 50);
  iMoveCursor(0, 0);
  displayGameTitle();
  displayHeader("CURRENT GAME STATE");

  printf("Draw Pile: %d cards remaining\n", state->deck_size);
  printf("Winning Points: %d\n\n", state->winning_points);

  for(i=0; i<state->player_count; i++){
    if(i ==  state->current_player){
      iSetColor(I_COLOR_YELLOW);
      printf(">> ");
    } else {
      printf("   ");
    }
    DisplayCardCounts(&state->players[i]);
    }
    iSetColor(I_COLOR_WHITE);
    printf("\n");
}

/**
 * Prompts the current player to choose a target player to steal from
 * @param state Pointer to the game state
 * @param currentPlayer Index of current player
 * @return Index of the chosen target player
 * @pre currentPlayer is between 0 and state->player_count - 1
 * (Danieles + Suazon)*/
int ChooseTargetPlayer(GameState* state, int currentPlayer){
  int choice;
  int valid = 0;
  int i;

  printf("\nChoose player to steal from:\n");
  for(i=0; i< state->player_count; i++){
    if (i != currentPlayer){
      printf("[%d] %s\n", i, state->players[i].username);
    }
  }

  while(valid == 0){
    printf(">> ");
    scanf("%d", &choice);

    if(choice == currentPlayer){
      iSetColor(I_COLOR_RED);
      printf("Cannot steal from yourself. Choose another player.\n");
      iSetColor(I_COLOR_WHITE);
    } else if(choice >= 0 && choice < state->player_count){
      valid = 1;
    } else {
      iSetColor(I_COLOR_RED);
      printf("Invalid choice. Please try again.\n");
      iSetColor(I_COLOR_WHITE);
    }
  }
  return choice;
}

/**
 * Handles the Try to Score action for a player
 * @param state Pointer to the game state
 * @param playerIndex Index of current player
 * @return 1 if successful, 0 if deck is empty
 * (Danieles + Suazon)*/
int TryToScore(GameState*  state, int playerIndex){
  GamePlayer* player;
  int result, found, i, j, k;
  Card drawnCard;
  Color drawnColor;

  player = &state->players[playerIndex];
  result = 0;
  found = 0;

  if(DrawnCard(state, &drawnCard) == 1){
    drawnColor = charToColor(drawnCard.front);

    printf("\nDrew card: ");
    iSetColor(I_COLOR_YELLOW);
    printf("%c", drawnCard.front);
    iSetColor(I_COLOR_WHITE);
    printf(" (Points: %d)\n", drawnCard.points);

    for(i=0; i<player->tank_count && found ==0; i++){
      if (charToColor(player->tank[i].front) == drawnColor){
        found = 1;
      }
    }

    if(found == 1){
      j = 0;
      while (j < player->tank_count) {
        if (charToColor(player->tank[j].front) == drawnColor) {
          player->score[player->score_count] = player->tank[j];
          player->score_count++;
          player->score_points = player->score_points + player->tank[j].points;

         //Shifting of cards in tank 
          for(k=j; k <player->tank_count - 1; k++){
            player->tank[k] = player->tank[k+1];
          }

          player->tank_count = player->tank_count - 1;
        } else {
          j = j + 1;
        }
    }
    
  //Updates the score of the player  
    player->score[player->score_count] = drawnCard;
    player->score_count++;
    player->score_points = player->score_points + drawnCard.points;

  // Displays the score earned
    iSetColor(I_COLOR_GREEN);
      printf("SCORED! +%d points! Total: %d\n", drawnCard.points, player->score_points);
      iSetColor(I_COLOR_WHITE);
      result = 1;

      } else {
        player->tank[player->tank_count] = drawnCard;
        player->tank_count = player->tank_count + 1;
        iSetColor(I_COLOR_BLUE);
        printf("Added to tank.\n");
        iSetColor(I_COLOR_WHITE);
        result = 1;
    }
  } else { 
    iSetColor(I_COLOR_RED);
    printf("Draw pile is empty!\n"); //Consideration if draw pile is empty
    iSetColor(I_COLOR_WHITE);
    result = 0;
  }
  return result;
}

/**
 * Handles the Try to Steal action for a player
 * @param state Pointer to the game state
 * @param playerIndex Index of current player
 * @return 1 if successful, 0 if deck is empty
 * (Danieles + Suazon)*/
int TryToSteal(GameState* state, int playerIndex){
  int targetIndex;
  GamePlayer* current;
  GamePlayer* target;
  int result = 0, found = 0;
  Card drawnCard;
  Color drawnColor;
  int stolenCount;
  int i,j,k;

  targetIndex = ChooseTargetPlayer(state, playerIndex);
  current = &state->players[playerIndex];
  target = &state->players[targetIndex];

  if(DrawnCard(state, &drawnCard) == 1){
    drawnColor = charToColor(drawnCard.front);

    printf("\nDrew card: ");
    iSetColor(I_COLOR_YELLOW);
    printf("%c", drawnCard.front);
    iSetColor(I_COLOR_WHITE);
    printf(" (Points: %d)\n", drawnCard.points);


  //Loop to look for the drawncard if there is a match with the targeted player
    for(i=0; i<target->tank_count && found==0; i++){
      if (charToColor(target->tank[i].front) == drawnColor) {
      found = 1;
      }
    }
    
    if (found == 1){
      stolenCount = 0;
      j=0;

      while(j < target->tank_count){
        if(charToColor(target->tank[j].front) == drawnColor){
          current->tank[current->tank_count] = target->tank[j];
          current->tank_count++;
          stolenCount++;

        //Shifting of cards in the tank of the target 
          k=j;
          while(k < target->tank_count-1){
            target->tank[k] = target->tank[k+1];
            k++;
          }
          target->tank_count--;
        } else {
          j++;
        }
      }
      current->tank[current->tank_count] = drawnCard;
      current->tank_count++;
      stolenCount++;
      
      iSetColor(I_COLOR_PURPLE);
      printf("STOLE %d card(s) from %s!\n", stolenCount, target->username);
      iSetColor(I_COLOR_WHITE);
      result = 1;
    } else {
      target->tank[target->tank_count] = drawnCard;
      target->tank_count++;
      iSetColor(I_COLOR_BLUE);
      printf("No %c cards to steal. Card added to %s's tank.\n", drawnCard.front, target->username);
      iSetColor(I_COLOR_WHITE);
      result = 1;
    }
  } else {
    iSetColor(I_COLOR_RED);
    printf("Draw pile is empty!\n");
    iSetColor(I_COLOR_WHITE);
    result = 0;
  }
  return result;
}

/**
 * Checks if the game is over (winning points reached or deck empty)
 * @param state Pointer to the game state
 * @return 1 if game is over, 0 otherwise
 * (Danieles + Suazon)*/
int CheckGameOver(GameState* state){
  int gameOver = 0;
  int i;
  
  for(i=0; i< state->player_count && gameOver == 0; i++){
    if(state->players[i].score_points >= state->winning_points){
      gameOver = 1;
    }
  }

  if(gameOver == 0 && state->deck_size<=0){
    gameOver = 1;
  }

  return gameOver;
}

/**
 * Determines winner(s) when the deck is empty (tie-breaking by points then tank size)
 * @param state Pointer to the game state
 * @param winners Array to store winner indices
 * @param winnerCount Pointer to store number of winners
 * (Danieles + Suazon)*/
void determineWinnerEmptyDeck(GameState* state, int winners[], int* winnerCount){
  int i, maxPoints=0;
  int tempCount=0;
  int maxTankCards;
  int tempWinners[MAX_PLAYERS];
  
// Find highest score
  for(i=0; i< state->player_count;i++){
    if(state->players[i].score_points > maxPoints){
      maxPoints = state->players[i].score_points;
    }
  }

// Collect players with max points
  for(i=0;i< state->player_count;i++){
    if (state->players[i].score_points == maxPoints){
      tempWinners[tempCount] = i;
      tempCount++;
    }
  }

  if (tempCount > 1){
    maxTankCards = 0;

   // Find highest tank size among tied players
    for(i=0; i<tempCount; i++){
      if(state->players[tempWinners[i]].tank_count > maxTankCards){
        maxTankCards = state->players[tempWinners[i]].tank_count;
      }
    }

   // Collect players with max tank cards
    *winnerCount = 0;
    for(i=0; i<tempCount; i++){
      if(state->players[tempWinners[i]].tank_count == maxTankCards){
        winners[*winnerCount] = tempWinners[i];
        *winnerCount = *winnerCount + 1;
      }
    }
  } else {
    *winnerCount = tempCount;
    for(i=0; i<tempCount; i++){
      winners[i] = tempWinners[i];
    }
  } 
}

/**
 * Displays game results and updates player statistics
 * @param state Pointer to the game state
 * @param players Array of player records
 * @param playerCount Pointer to number of players in records
 * (Danieles + Suazon)*/
void ShowGameResults(GameState* state, PlayerRecord players[], int* playerCount){
  int i;
  int winners[MAX_PLAYERS];
  int winnerCount;
  int playerIndex;
  
  iClear(0, 0, 200, 50);
  iMoveCursor(0, 0);
  displayGameTitle();
  displayHeader("GAME RESULTS");

  printf("Final Scores:\n\n");
  
  for(i=0; i<state->player_count;i++){
    printf("%s: %d points (%d cards in tank, %d cards in score)\n", state->players[i].username, 
    state->players[i].score_points, state->players[i].tank_count, state->players[i].score_count);
  }
  printf("\n");

  // Determine winners
  if (state->deck_size <= 0){
    determineWinnerEmptyDeck(state, winners, &winnerCount);
  } else {
    winnerCount = 0;
    for(i=0; i<state->player_count;i++){
      if(state->players[i].score_points >= state->winning_points){
        winners[winnerCount] = i;
        winnerCount++;
      }
    }
  }

 // Display winner(s)
  if(winnerCount == 1){
    iSetColor(I_COLOR_YELLOW);
    printf("🏆 WINNER: %s with %d points! 🏆\n", 
      state->players[winners[0]].username, 
      state->players[winners[0]].score_points);
    iSetColor(I_COLOR_WHITE);
  } else {
    iSetColor(I_COLOR_YELLOW);
    printf("🎉 TIE! Winners: 🎉\n");
    for(i=0; i<winnerCount;i++){
      printf("  - %s (%d points)\n", state->players[winners[i]].username, 
      state->players[winners[i]].score_points);
    }
    iSetColor(I_COLOR_WHITE);
  }

  // Update wins for winners
  for(i=0; i<winnerCount; i++){
    playerIndex = findPlayer(players, *playerCount, state->players[winners[i]].username);
    if (playerIndex >= 0){
      players[playerIndex].games_won++;
    }
  }

  // Update highest scores for all players
  for(i=0; i < state->player_count; i++){
    playerIndex = findPlayer(players, *playerCount, state->players[i].username);
    if (playerIndex >= 0){
      if (state->players[i].score_points > players[playerIndex].highest_score) {
        players[playerIndex].highest_score = state->players[i].score_points;
      }
    }
  }
}

/**
 * Displays top players sorted by number of wins
 * @param players Array of player records
 * @param playerCount Pointer to number of players
 * (Suazon)*/
void displayByWins(PlayerRecord players[], int *playerCount) {
  int i;

  sortByWins(players, playerCount);

  displayHeader("TOP PLAYERS!");
  printf("==========================================================\n\n");

  for(i=0; i<*playerCount; i++)
    printf("%d. %s \t\t %d wins\n", i+1, players[i].username, players[i].games_won);

  printf("==========================================================\n\n");
}

/**
 * Displays top players sorted by highest scores
 * @param players Array of player records
 * @param playerCount Pointer to number of players
 * (Suazon)*/
void displayByScores(PlayerRecord players[], int *playerCount) {
  int i;

  sortByScores(players, playerCount);

  displayHeader("TOP PLAYERS!");
  printf("==========================================================\n\n");

  for(i=0; i<*playerCount; i++)
    printf("%d. %s \t\t %d scores\n", i+1, players[i].username, players[i].highest_score);

  printf("==========================================================\n\n");
}

#endif // HELPERS_1_C; Include this to prevent redefinition error
