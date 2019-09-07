#include "logic.h"


void initializeAppState(AppState* appState) {
    appState -> gameOver = 0;
    appState -> timer = 20;
    appState -> cornersRemaining = 4;
    // appState -> scale = 5;
    for (int i = 0; i < NUMBLOCKWIDTH * NUMBLOCKHEIGHT; i++) {
        appState -> blocks[i].x = i % NUMBLOCKWIDTH;
        appState -> blocks[i].y = i/NUMBLOCKWIDTH;
        if (maze1[i] == '1') {
            appState -> blocks[i].isWall = 1;
        } else if (maze1[i] == 'R') {
            appState -> blocks[i].isReward = 1;
        }
    }
    appState -> playerBlockIndex = (STARTROW * NUMBLOCKWIDTH) + STARTCOL;
    appState -> endBlockIndex = (ENDROW * NUMBLOCKWIDTH) + ENDCOL;

}

// TA-TODO: Add any process functions for sub-elements of your app here.
// For example, for a snake game, you could have a processSnake function
// or a createRandomFood function or a processFoods function.
//
// e.g.:
// static Snake processSnake(Snake* currentSnake);
// static void generateRandomFoods(AppState* currentAppState, AppState* nextAppState);

// This function processes your current app state and returns the new (i.e. next)
// state of your application.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
    /* TA-TODO: Do all of your app processing here. This function gets called
     * every frame.
     *
     * To check for key presses, use the KEY_JUST_PRESSED macro for cases where
     * you want to detect each key press once, or the KEY_DOWN macro for checking
     * if a button is still down.
     *
     * To count time, suppose that the GameBoy runs at a fixed FPS (60fps) and
     * that VBlank is processed once per frame. Use the vBlankCounter variable
     * and the modulus % operator to do things once every (n) frames. Note that
     * you want to process button every frame regardless (otherwise you will
     * miss inputs.)
     *
     * Do not do any drawing here.
     *
     * TA-TODO: VERY IMPORTANT! READ THIS PART.
     * You need to perform all calculations on the currentAppState passed to you,
     * and perform all state updates on the nextAppState state which we define below
     * and return at the end of the function. YOU SHOULD NOT MODIFY THE CURRENTSTATE.
     * Modifying the currentAppState will mean the undraw function will not be able
     * to undraw it later.
     */

    AppState nextAppState = *currentAppState;
    int playerInd = currentAppState -> playerBlockIndex;
    int upInd = playerInd - NUMBLOCKWIDTH;
    int downInd = playerInd + NUMBLOCKWIDTH;
    int rightInd = playerInd + 1;
    int leftInd = playerInd - 1;
    if (KEY_JUST_PRESSED(BUTTON_UP, keysPressedNow, keysPressedBefore) != 0 && upInd > 0 
        && upInd < (NUMBLOCKWIDTH*NUMBLOCKHEIGHT) && currentAppState -> blocks[upInd].isWall != 1) {
            nextAppState.playerBlockIndex = upInd;
    }
    if (KEY_JUST_PRESSED(BUTTON_DOWN, keysPressedNow, keysPressedBefore) != 0 && downInd > 0 
        && downInd < (NUMBLOCKWIDTH*NUMBLOCKHEIGHT) && currentAppState -> blocks[downInd].isWall != 1) {
            nextAppState.playerBlockIndex = downInd;
    }
    if (KEY_JUST_PRESSED(BUTTON_RIGHT, keysPressedNow, keysPressedBefore) != 0 && rightInd > 0 
        && rightInd < (NUMBLOCKWIDTH*NUMBLOCKHEIGHT) && currentAppState -> blocks[rightInd].isWall != 1) {
            nextAppState.playerBlockIndex = rightInd;
    }
    if (KEY_JUST_PRESSED(BUTTON_LEFT, keysPressedNow, keysPressedBefore) != 0 && leftInd > 0 
        && leftInd < (NUMBLOCKWIDTH*NUMBLOCKHEIGHT) && currentAppState -> blocks[leftInd].isWall != 1) {
            nextAppState.playerBlockIndex = leftInd;
    }
    if (nextAppState.blocks[playerInd].isReward == 1) {
        nextAppState.blocks[playerInd].isReward = 0;
        nextAppState.timer = nextAppState.timer + 5;
        nextAppState.cornersRemaining = nextAppState.cornersRemaining -1;
    }
    return nextAppState;
}
