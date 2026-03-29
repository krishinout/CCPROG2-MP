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
    RED,        // Represents the color Red        
    ORANGE,     // Represents the color Orange     
    YELLOW,     // Represents the color Yellow
    GREEN,      // Represents the color Green
    BLUE,       // Represents the color Blue
    INDIGO,     // Represents the color Indigo
    VIOLET      // Represents the color Violet
} Color;

/**
 * Represents a Mantis card with front color, back colors, and point value
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
    char username[MAX_USERNAME];     // Player's username
    int games_won;                   // Number of games won by the player
    int highest_score;               // Highest score achieved by the player
} PlayerRecord;

/**
 * Represents a player in an active game session
 */
typedef struct {
    char username[MAX_USERNAME];          // Player's username
    Card tank[MAX_CARDS_PER_PLAYER];      // Tank pile cards (unscored cards)
    int tank_count;                       // Number of cards in tank pile
    Card score[MAX_CARDS_PER_PLAYER];     // Score pile cards (scored cards)
    int score_count;                      // Number of cards in score pile
    int score_points;                     // Total points in score pile
    int is_new;                           // Flag for new players (1 if new, 0 if existing)
} GamePlayer;

/**
 * Represents the current game state
 */
typedef struct {
    Card deck[DECK_SIZE];                    // The deck of cards
    int deck_size;                           // Current number of cards in deck
    GamePlayer players[MAX_PLAYERS];         // Players in current game
    int player_count;                        // Number of players in current game
    int winning_points;                      // Points needed to win the game
    int current_player;                      // Index of current player
    int game_over;                           // Flag indicating if game is over (1 if over)
} GameState;

/**
* Represents game settings that are adjustable
*/
typedef struct
{
  int winningPoints;    // Points required to win the game
  unsigned int seed;    // Seed value for shuffling

} GameSettings;

#endif // DEFS_H; Include this to prevent redefinition error
