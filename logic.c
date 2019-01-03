#include "logic.h"

void initializeAppState(AppState* appState) {
    // Initialize everything that's part of this AppState struct here.
    // Suppose the struct contains random values, make sure everything gets
    // the value it should have when the app begins.
    appState->sprayer.top_left_col = 100;
    appState->sprayer.width = 40;

    for (int row = 2; row < 8; row++) {
        for (int col = 0; col < 6; col++) {
            Fungus new_fungi = {0, (row*20), (col*40), 20, 40, 0xFF00};
            appState->fungi[((row-2) * 6) + col] = new_fungi;
        }
    }

    //initialize two random starting values
    int random = randint(20, 36);
    int random2 = randint(6, 20);
    appState->fungi[random].active = 1;
    appState->fungi[random2].active = 1;

    appState->level = 1;
    appState->mold_killed = 0;
    appState->gameOver = 0;
    appState->reset = 0;
    appState->warning = 0;
    appState->level_up = 0;

    appState->sprayer.lt_diag = 0;
    appState->sprayer.rt_diag = 0;
    appState->sprayer.down = 0;

    Bleach new_bleach = {0, 0, 100, 2, 2, 0x0000};
    appState->bleach = new_bleach;
}

// This function processes your current app state and returns the new (i.e. next)
// state of your application.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
    // Do all of your app processing here. This function gets called every frame.

    if (KEY_DOWN(BUTTON_RIGHT, keysPressedBefore) 
        || KEY_JUST_PRESSED(BUTTON_RIGHT, keysPressedNow, keysPressedBefore)
        || KEY_DOWN(BUTTON_LEFT, keysPressedBefore)
        || KEY_JUST_PRESSED(BUTTON_LEFT, keysPressedNow, keysPressedBefore)) {
            if (KEY_DOWN(BUTTON_RIGHT, keysPressedBefore)) {
                if (currentAppState->sprayer.top_left_col < 200) {
                    currentAppState->sprayer.top_left_col++;
                } else {
                    currentAppState->sprayer.top_left_col = 200;
                }
            }

            if (KEY_JUST_PRESSED(BUTTON_RIGHT, keysPressedNow, keysPressedBefore)) {
                if (currentAppState->sprayer.top_left_col < 200) {
                    currentAppState->sprayer.top_left_col++;
                } else {
                    currentAppState->sprayer.top_left_col = 200;
                }
            }

            if (KEY_DOWN(BUTTON_LEFT, keysPressedBefore)) {
                if (currentAppState->sprayer.top_left_col > 0) {
                    currentAppState->sprayer.top_left_col--;
                } else {
                    currentAppState->sprayer.top_left_col = 0;
                }
            }

            if (KEY_JUST_PRESSED(BUTTON_LEFT, keysPressedNow, keysPressedBefore)) {
                if (currentAppState->sprayer.top_left_col > 0) {
                    currentAppState->sprayer.top_left_col--;
                } else {
                    currentAppState->sprayer.top_left_col = 0;
                }
            }
    } else {
        if (KEY_JUST_PRESSED(BUTTON_DOWN, keysPressedNow, keysPressedBefore)) {
            //fire on the fungus!
            if (currentAppState->bleach.active == 0) {
                currentAppState->bleach.active = 1;
                currentAppState->sprayer.down = 1;
                currentAppState->sprayer.lt_diag = 0;
                currentAppState->sprayer.rt_diag = 0;
                currentAppState->bleach.row = 40;
                currentAppState->bleach.col = currentAppState->sprayer.top_left_col + 7;
            } 
        }

        if (KEY_JUST_PRESSED(BUTTON_L, keysPressedNow, keysPressedBefore)) {
            //fire on the fungus!
            if (currentAppState->bleach.active == 0) {
                currentAppState->bleach.active = 1;
                currentAppState->sprayer.down = 0;
                currentAppState->sprayer.lt_diag = 1;
                currentAppState->sprayer.rt_diag = 0;
                currentAppState->bleach.row = 40;
                currentAppState->bleach.col = currentAppState->sprayer.top_left_col + 7;
            } 
        }

        if (KEY_JUST_PRESSED(BUTTON_R, keysPressedNow, keysPressedBefore)) {
            //fire on the fungus!
            if (currentAppState->bleach.active == 0) {
                currentAppState->bleach.active = 1;
                currentAppState->sprayer.down = 0;
                currentAppState->sprayer.lt_diag = 0;
                currentAppState->sprayer.rt_diag = 1;
                currentAppState->bleach.row = 40;
                currentAppState->bleach.col = currentAppState->sprayer.top_left_col + 7;
            } 
        }
    }

    if (currentAppState->bleach.col >= 236 || currentAppState->bleach.col <= 0) {
        currentAppState->bleach.active = 0;
    }

    if (currentAppState->bleach.active == 1) {
        if (currentAppState->bleach.row < 160) {
            if (currentAppState->sprayer.down == 1) {
                currentAppState->bleach.row = currentAppState->bleach.row + currentAppState->bleach.rd;
            } else if (currentAppState->sprayer.lt_diag == 1) {
                currentAppState->bleach.row += currentAppState->bleach.rd;
                currentAppState->bleach.col -= currentAppState->bleach.cd;
            } else {
                currentAppState->bleach.row += currentAppState->bleach.rd;
                currentAppState->bleach.col += currentAppState->bleach.cd;
            }

            for (int i = 18; i < 36; i++) {
                if (currentAppState->fungi[i].active == 1
                    && currentAppState->bleach.row >= currentAppState->fungi[i].row
                    && currentAppState->bleach.col > currentAppState->fungi[i].col
                    && currentAppState->bleach.col < (currentAppState->fungi[i].col + currentAppState->fungi[i].width)) {
                        currentAppState->fungi[i].active = 0;
                        currentAppState->bleach.active = 0;
                        currentAppState->mold_killed++;
                }
                if (currentAppState->mold_killed > 5) {
                    currentAppState->level_up = 1;
                    currentAppState->mold_killed = 0;
                    currentAppState->level = currentAppState->level + 1;
                }
            }
        } else {
            currentAppState->bleach.active = 0;
        }
    }

    if (KEY_JUST_PRESSED(BUTTON_SELECT, keysPressedNow, keysPressedBefore)) {
        currentAppState->reset = 1;
    }

    AppState nextAppState = *currentAppState;

    return nextAppState;
}
