#ifndef LOGIC_SEEN
#define LOGIC_SEEN

#include "gba.h"
#include <string.h>

#define MAZEWIDTH 150
#define MAZEHEIGHT 150
#define NUMBLOCKWIDTH 25
#define NUMBLOCKHEIGHT 25
#define BLOCKWIDTH ((MAZEWIDTH)/(NUMBLOCKWIDTH))
#define BLOCKHEIGHT ((MAZEHEIGHT)/(NUMBLOCKHEIGHT))
#define XOFFSET ((WIDTH)-(MAZEWIDTH))/2
#define YOFFSET ((HEIGHT)-(MAZEHEIGHT))/2
static const char maze1[NUMBLOCKHEIGHT * NUMBLOCKWIDTH] = "1111111111111011111111111"\
              "1R000000000010000011101R1"\
              "1110111111101111101110101"\
              "1000100011101000000000101"\
              "1010101011101011111111101"\
              "1010001011100011100000001"\
              "1011111011111111101011111"\
              "1010000010000000001000001"\
              "1010111110111111101110111"\
              "1010100000000000101010001"\
              "1110101011111110111010101"\
              "1000101011100000111010101"\
              "1011101011101111111011100"\
              "1010001011100011100000001"\
              "1011111011111011101110101"\
              "1000111011111000001110101"\
              "1110111011111111111110111"\
              "1110111010000000111000001"\
              "1110111010111010111011101"\
              "1110000000100010000011101"\
              "1111111110111110101111101"\
              "1000000010100000101000001"\
              "1011101010101011101011111"\
              "1R111010000010111010000R1"\
              "1111111111111111111111111";
#define STARTROW 12
#define STARTCOL 24
#define ENDROW 0
#define ENDCOL 13
#define SCALE 5

typedef struct {
    u8 x;
    u8 y;
    u8 isWall;
    u8 isReward;
} MazeBlock;


typedef struct {
    // Store whether or not the game is over in this member:
    // int scale;
    u8 gameOver;
    u16 playerBlockIndex;
    u8 timer;
    MazeBlock blocks[NUMBLOCKWIDTH * NUMBLOCKHEIGHT];
    u16 endBlockIndex;
    u8 cornersRemaining;
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

} AppState;

/*
* TA-TODO: Add any additional structs that you need for your app.
*
* For example, for a Snake game, one could be:
*
* typedef struct {
*   int heading;
*   int length;
*   int x;
*   int y;
* } Snake;
*
*/


// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);

// This function will be used to process app frames.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);

// If you have anything else you need accessible from outside the logic.c
// file, you can add them here. You likely won't.

#endif
