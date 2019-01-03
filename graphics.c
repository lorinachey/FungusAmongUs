#include "graphics.h"
#include "gba.h"

#include "images/tile.h"
#include "images/sprayer.h"
#include "images/fungus.h"
#include "images/gameover.h"

// This function will be used to draw everything about the app
// including the background and whatnot.
void fullDrawAppState(AppState *state) {
    fillScreenDMA(0xFFFF);
    drawRectDMA(0, 60, 240, 60, 0x0000);
    drawImageDMA(state->sprayer.top_left_col, 0, state->sprayer.width, state->sprayer.width, sprayer);
}

//This function will be used to undraw (i.e. erase) things that might
//move in a frame. E.g. in a Snake game, erase the Snake, the food & the score.
void undrawAppState(AppState *state) {
    //fillScreenDMA(0xFFFF);
    //drawRectDMA(0,state->sprayer.top_left_col+1, state->sprayer.width, state->sprayer.width, 0xFFFF);
    drawRectDMA(0,0,240,60,0xFFFF);
    drawRectDMA(0,100,240,60,0xFFFF);
    //drawRectDMA(0, 40, 240, 120, 0xFFFF);
    UNUSED(state);
}

// This function will be used to draw things that might have moved in a frame.
// For example, in a Snake game, draw the snake, the food, the score.
void drawAppState(AppState *state) {

    // Draw the sprayer and the hold line
    drawImageDMA(state->sprayer.top_left_col, 0, state->sprayer.width, state->sprayer.width, sprayer);
    //drawRectDMA(0, 60, 240, 25, 0x0000);

    int active_count = 0;
    for (int i = 18; i < 36; i++) {
        if (state->fungi[i].active == 1) {
            drawImageDMA(state->fungi[i].col, 
                state->fungi[i].row, 
                state->fungi[i].width, 
                state->fungi[i].height,
                fungus);
            active_count++;
        }
        
        if (active_count >= 18) {
            state->gameOver = 1;
        }
    }

    if(state->level_up == 1 && state->level <= 2) {
        char level[] = "L+";
        drawString(5, 40, level, 0x0000);

        if (vBlankCounter % 100 == 0) {
            state->level_up = 0;
        }
    }

    if (state->bleach.active == 1) {
        //fire a bleach bomb
        drawRectDMA(state->bleach.col, state->bleach.row, 3, 3, state->bleach.color);
    }

    switch(state->level) {
        case 1:
            if (vBlankCounter % 100 == 0) {
                int random = randint(30, 36);
                int rand2 = randint(25, 30);
                
                state->fungi[random].active = 1;
                state->fungi[rand2].active = 1;
            }
            break;
        case 2:
            if (vBlankCounter % 90 == 0) {
            int rand2 = randint(18, 25);
            int rand3 = randint(25, 30);
            
            state->fungi[30].active = 1;
            state->fungi[31].active = 1;
            state->fungi[32].active = 1;
            state->fungi[33].active = 1;
            state->fungi[34].active = 1;
            state->fungi[35].active = 1;
            state->fungi[rand2].active = 1;
            state->fungi[rand3].active = 1;
            }
            break;
        default:
            if (vBlankCounter % 75 == 0) {
            int random = randint(18, 25);
            int rand2 = randint(25, 30);
            int rand3 = randint(18, 30);
            
            state->fungi[30].active = 1;
            state->fungi[31].active = 1;
            state->fungi[32].active = 1;
            state->fungi[33].active = 1;
            state->fungi[34].active = 1;
            state->fungi[35].active = 1;
            state->fungi[rand2].active = 1;
            state->fungi[random].active = 1;
            state->fungi[rand3].active = 1;
            }            
    }
}
