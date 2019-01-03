#ifndef LOGIC_SEEN
#define LOGIC_SEEN

#include "gba.h"

#define GAME_OVER "The Fungus Got You! Game OVER!"

typedef struct {
    int active;
    int row;
    int col;
    int height;
    int width;
    unsigned short color;
} Fungus;

typedef struct {
    int active;
    int row;
    int col;
    int rd;
    int cd;
    unsigned short color;
} Bleach;

typedef struct {
    //int top_left_row;   should always be aligned to the top...
    int top_left_col;
    int width;
    int lt_diag;
    int rt_diag;
    int down;
} Sprayer;

typedef struct {
    // Store whether or not the game is over in this member:
    int gameOver;
    int reset;
    int warning;
    int level_up;

    /*
    * TA-TODO: Add any logical elements you need to keep track of in your app.
    *
    * For example, for a Snake game, those could be:
    *
    * Snake snake;
    * Food foods[10];
    * int points;
    *
    */
    int level;
    int mold_killed;
    Sprayer sprayer;
    Bleach bleach;
    Fungus fungi[36]; 

} AppState;

// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);

// This function will be used to process app frames.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);

// If you have anything else you need accessible from outside the logic.c
// file, you can add them here. You likely won't.

#endif
