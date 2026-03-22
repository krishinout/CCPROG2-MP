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
#include "interface.c"
#include "helpers_2.c"

/******************************************************************************
 * NOTE: These functions are placed here in helpers_1.c to demonstrate code
 * modularization across multiple files. You may move them to different files
 * if it better fits your code organization.
 ******************************************************************************/

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

//for validating username (geane)
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

//for the user interface (con + geane)
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

  //adding the new username sa memory
  strcpy(players[*playerCount].username, newUsername);
  players[*playerCount].games_won = 0;
  players[*playerCount].highest_score = 0;
  (*playerCount)++;

  //saves the new username to the player.txt file
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

//loads the existing players from the players.txt file
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

//loading the mantis.txt deck file
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

//draw card
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

//for dealing initial 4 cards sa players
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

//displays card counts (con + geane)
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

//displays current gamestate
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

//choosing target for stealing
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

//trying to score function of the game
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

         //shifting of cards sa tank 
          for(k=j; k <player->tank_count - 1; k++){
            player->tank[k] = player->tank[k+1];
          }

          player->tank_count = player->tank_count - 1;
        } else {
          j = j + 1;
        }
    }
    
  //just updates the score of the player  
    player->score[player->score_count] = drawnCard;
    player->score_count++;
    player->score_points = player->score_points + drawnCard.points;

  // displays the score earned
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
    printf("Draw pile is empty!\n"); //consideration na what if maubos yung draw pile
    iSetColor(I_COLOR_WHITE);
    result = 0;
  }
  return result;
}

//trying to steal function of the game
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


  //loop lang to look for the drawncard if may kamatch sa targeted player
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

        //just shifting of cards sa tank ng target 
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

void determineWinnerEmptyDeck(GameState* state, int winners[], int* winnerCount){
  int i, maxPoints=0;
  int tempCount=0;
  int maxTankCards;
  int tempWinners[MAX_PLAYERS];
  
//to check kung ano ung highest score sa current players
  for(i=0; i< state->player_count;i++){
    if(state->players[i].score_points > maxPoints){
      maxPoints = state->players[i].score_points;
    }
  }

// to check sino yung equal sa max points na meron
  for(i=0;i< state->player_count;i++){
    if (state->players[i].score_points == maxPoints){
      tempWinners[tempCount] = i;
      tempCount++;
    }
  }

  if (tempCount > 1){
    maxTankCards = 0;

    for(i=0; i<tempCount; i++){
      if(state->players[tempWinners[i]].tank_count > maxTankCards){
        maxTankCards = state->players[tempWinners[i]].tank_count;
      }
    }

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

  //if naubos yung deck
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

  //updates the players stats
  //updates wins count
  for(i=0; i<winnerCount; i++){
    playerIndex = findPlayer(players, *playerCount, state->players[winners[i]].username);
    if (playerIndex >= 0){
      players[playerIndex].games_won++;
    }
  }

  //updates highest score count
  for(i=0; i < state->player_count; i++){
    playerIndex = findPlayer(players, *playerCount, state->players[i].username);
    if (playerIndex >= 0){
      if (state->players[i].score_points > players[playerIndex].highest_score) {
        players[playerIndex].highest_score = state->players[i].score_points;
      }
    }
  }
}

// displays top players based on number of wins
void displayByWins(PlayerRecord players[], int *playerCount) {
  int i;

  sortByWins(players, playerCount);
 
  iClear(0, 0, 200, 50);
  iMoveCursor(0, 0);

  displayGameTitle();
  displayHeader("TOP PLAYERS!");
  printf("=======================================================\n");

  for(i=0; i<*playerCount; i++)
    printf("[%d] %-36s %7d wins\n", i+1, players[i].username, players[i].games_won);

  printf("=======================================================\n\n");
}

//displays top players based on highest scores
void displayByScores(PlayerRecord players[], int *playerCount) {
  int i;

  sortByScores(players, playerCount);

  iClear(0, 0, 200, 50);
  iMoveCursor(0, 0);

  displayGameTitle();
  displayHeader("TOP PLAYERS!");
  printf("=======================================================\n");

  for(i=0; i<*playerCount; i++)
    printf("[%d] %-36s %7d scores\n", i+1, players[i].username, players[i].highest_score);

  printf("=======================================================\n\n");
}

// adjusts shuffling seed and winning points
void adjustSettings(int *winningPoints, int *shuffleSeed, GameSettings *settings) {
  int choice;

  iClear(0, 0, 200, 50);
  iMoveCursor(0, 0);

  displayGameTitle();
  displayHeader("SETTINGS");

  iSetColor(I_COLOR_GREEN);
  printf("Current winning points: %d\n", *winningPoints);
  iSetColor(I_COLOR_PURPLE);
  printf("Current seed: random\n\n");
  iSetColor(I_COLOR_WHITE);

  printf("[1] Modify winning points (1-100)\n");
  printf("[2] Modify shuffling seed\n");
  printf("[3] Return\n");

  do
  {
    printf("\n>> ");
    scanf("%d", &choice);

    if(choice < 1 || choice > 3){
      iSetColor(I_COLOR_RED);
      printf("Invalid choice. Please try again.\n");
      iSetColor(I_COLOR_WHITE);
    }
   

  }while(choice < 1 || choice > 3);

  if(choice == 1) {
     do
    {
      printf("Enter new winning score: ");
      scanf("%d", &settings->winningPoints);

      if(settings->winningPoints < 1 || settings->winningPoints > 100){
        iSetColor(I_COLOR_RED);
        printf("Invalid input. Please try again.\n");
        iSetColor(I_COLOR_WHITE);
      }
    }while(settings->winningPoints < 1 || settings->winningPoints > 100);

    printf("Winning points set to %d", settings->winningPoints);
    *winningPoints = settings->winningPoints;
    printf("\n");
      waitForEnter();
  }

  else if(choice == 2) {
    printf("Enter seed (0 for random): ");
    scanf("%u", &settings->seed);
    settings->customSeed = (settings->seed != 0);

    printf("Seed set to %s.\n\n", settings->customSeed ? "custom" : "random");
    *shuffleSeed = (int)settings->customSeed;
    printf("\n");
      waitForEnter();
  }
}





#endif // HELPERS_1_C; Include this to prevent redefinition error
