/******************************************************************************
 *  Description     : Header file containing structures, constants, and type 
 *                    definitions for the Mantis card game.
 *  Author/s        : Danieles, Maricon
 *                    Suazon, Krisha
 *  Section         : S12A & S22A
 *  Last Modified   : March 12, 2026
 ******************************************************************************/

#ifndef DEFS_H // Include this to prevent redefinition error
#define DEFS_H // Include this to prevent redefinition error

/******************************************************************************
 * NOTE: These definitions are placed here in defs.h to demonstrate code
 * modularization across multiple files. You may move them to different files
 * if it better fits your code organization.
 ******************************************************************************/

 /* ==================== Constants ==================== */
#define MAX_PLAYERS_FILE 50
#define MAX_USERNAME 36
#define MIN_PLAYERS 3
#define MAX_PLAYERS 6
#define DECK_SIZE 84
#define HAND_SIZE 4
#define COLORS 7
#define WINNING_POINTS_DEFAULT 20
#define MAX_CARDS_PER_PLAYER 100

/* ==================== Color Codes ==================== */
typedef enum {
    RED,        
    ORANGE,     
    YELLOW,     
    GREEN,      
    BLUE,       
    INDIGO,     
    VIOLET      
} Color;

/**
 * Represents a Mantis card
 */
typedef struct {
    char front;                 // Front color letter (R, O, Y, G, B, I, V)
    char back1;                 // First back color letter
    char back2;                 // Second back color letter
    char back3;                 // Third back color letter
    int points;                 // Point value (1-3)
} Card;

/**
 * Represents a player in the persistent records (for file storage)
 */
typedef struct {
    char username[MAX_USERNAME];    // Player's username
    int games_won;                   // Number of games won
    int highest_score;               // Highest score achieved
} PlayerRecord;

/**
 * Represents a player in an active game
 */
typedef struct {
    char username[MAX_USERNAME];              // Player's username
    Card tank[MAX_CARDS_PER_PLAYER];    // Tank pile cards
    int tank_count;                      // Number of cards in tank
    Card score[MAX_CARDS_PER_PLAYER];    // Score pile cards
    int score_count;                      // Number of cards in score
    int score_points;                     // Total points in score pile
    int is_new;                           // Flag for new players
} GamePlayer;

/**
 * Represents the current game state
 */
typedef struct {
    Card deck[DECK_SIZE];                    // The deck of cards
    int deck_size;                            // Current deck size
    GamePlayer players[MAX_PLAYERS];     // Players in current game
    int player_count;                          // Number of players in game
    int winning_points;                        // Points needed to win
    int current_player;                        // Index of current player
    int game_over;                             // Game over flag
} GameState;

/**
 * Represents player stats across the entire game
 */
typedef struct
{
  char username[MAX_USERNAME+1];
  int wins;
  int games;
  int highestScore;
} playerStats; // to create full player list and current player list

/**
* Represents game settings that are adjustable
*/
typedef struct
{
  int winningPoints;
  unsigned int seed;

} GameSettings;

#endif // DEFS_H; Include this to prevent redefinition error