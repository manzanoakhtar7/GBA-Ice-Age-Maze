#include "graphics.h"
#include "gba.h"
#include "images/squirrel.h"
#include "images/ice.h"
#include "images/acorn.h"
// TA-TODO: Include any header files for images generated by nin10kit.
// Example for the provided garbage image:
//#include "images/garbage.h"

// TA-TODO: Add any draw/undraw functions for sub-elements of your app here.
// For example, for a snake game, you could have a drawSnake function
// or a drawFood function
//
// e.g.:
// static void drawSnake(Snake* snake);
// static void drawFood(Food* food);
void drawMaze(AppState *state) {
	int playerInd = state -> playerBlockIndex;
	// int scale = state -> scale;
	int topLeftRow = state -> blocks[playerInd].y - ((NUMBLOCKHEIGHT/(2*SCALE))-1);
	if (topLeftRow < 0) {
		topLeftRow = 0;
	}
	if (topLeftRow + ((NUMBLOCKHEIGHT/SCALE)-1) > 24) {
		topLeftRow = 24 - ((NUMBLOCKHEIGHT/SCALE)-1);
	}
	int topLeftCol = state -> blocks[playerInd].x - ((NUMBLOCKWIDTH/(2*SCALE))-1);
	if (topLeftCol < 0) {
		topLeftCol = 0;
	}
	if (topLeftCol + ((NUMBLOCKWIDTH/SCALE)-1) > 24) {
		topLeftCol = 24 - ((NUMBLOCKWIDTH/SCALE)-1);
	}
	int topLeftInd = (topLeftRow * NUMBLOCKWIDTH) + topLeftCol;
	int xOff = state -> blocks[topLeftInd].x;
	int yOff = state -> blocks[topLeftInd].y;
	int playerX = XOFFSET + ((state -> blocks[playerInd].x - xOff)*SCALE*BLOCKWIDTH);
    int playerY = YOFFSET + ((state -> blocks[playerInd].y - yOff)*SCALE*BLOCKHEIGHT);
	drawImageDMA(playerX, playerY, BLOCKWIDTH*SCALE, BLOCKHEIGHT*SCALE, squirrel);
    for (int r = 0; r < NUMBLOCKHEIGHT/SCALE; r++) {
    	for (int c = 0; c < NUMBLOCKWIDTH/SCALE; c++) {
    		int index = ((r + topLeftRow) * NUMBLOCKWIDTH) + (c + topLeftCol);
    		int newX = XOFFSET + ((state -> blocks[index].x - xOff)*SCALE*BLOCKWIDTH);
    		int newY = YOFFSET + ((state -> blocks[index].y - yOff)*SCALE*BLOCKHEIGHT);
    		if (state -> blocks[index].isWall == 1) {
    			drawImageDMA(newX, newY, BLOCKWIDTH*SCALE, BLOCKHEIGHT*SCALE, ice);
    		}
    		if (state -> blocks[index].isReward == 1) {
    			drawImageDMA(newX, newY, BLOCKWIDTH*SCALE, BLOCKHEIGHT*SCALE, acorn);
    		}
    	}
    }
}

// This function will be used to draw everything about the app
// including the background and whatnot.
void fullDrawAppState(AppState *state) {
	fillScreenDMA(LIGHTBLUE);
	drawRectDMA(XOFFSET, YOFFSET, MAZEWIDTH, MAZEHEIGHT, WHITE);
	char *timeString = "Time:";
	drawCenteredString(0,YOFFSET, XOFFSET, 10,timeString, RED);
	char *acornString = "Acorns";
	char *leftString = "Left:";
	drawCenteredString(XOFFSET + MAZEWIDTH,YOFFSET, XOFFSET, 10, acornString, RED);
	drawCenteredString(XOFFSET + MAZEWIDTH,YOFFSET + 10, XOFFSET, 10, leftString, RED);
	drawMaze(state);
}

// This function will be used to undraw (i.e. erase) things that might
// move in a frame. E.g. in a Snake game, erase the Snake, the food & the score.
void undrawAppState(AppState *state) {
    drawRectDMA(XOFFSET, YOFFSET, MAZEWIDTH, MAZEHEIGHT, LIGHTBLUE);
    UNUSED(state);
}

// This function will be used to draw things that might have moved in a frame.
// For example, in a Snake game, draw the snake, the food, the score.
void drawAppState(AppState *state) {
    drawMaze(state);
    
}
