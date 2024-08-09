/**
 * @file pckman_game.h
 * @author your name (you@domain.com)
 * @brief all the game brain and logic is here
 * @version 0.1
 * @date 2024-08-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <SDL.h>

#define PKM_MAIN_WIN_WIDTH 496
#define PKM_MAIN_WIN_HEIGHT 640

#define PKM_MAIN_HEADER WIDTH 448
#define PKM_MAIN_HEADER HEIGHT 64
#define PKM_MAIN_GAME_WIDTH 448
#define PKM_MAIN_GAME_HEIGHT 576
#define PKM_MAIN_FOOTER WIDTH 448
#define PKM_MAIN_FOOTER HEIGHT 64

// the number of pixel to move
// base on pac-man dossier, 100% speed = 75.7575625 pixels/second
// on a 224 x 288 pixel area
// but because our pixel area is double at 448 x 576
// we need to acheive a rough pixel speed of 150 pixels/second
#define PKM_MAIN_FPS 75             //  75 frames per second for our refresh rate
#define PKM_MAIN_GAME_FRAME_COUNT 2 // we update the game every 3 frames?
#define PKM_MAIN_REGULAR_SPEED 4    // use 4 pixel movement for regular speed

// frame count before updates
#define PKM_MAIN_WAKA_FRAME_COUNT 3 // we waka every 3 frames?

#define PKM_MAIN_CELL_WIDTH 16
#define PKM_MAIN_CELL_HEIGHT 16
#define PKM_MAIN_CHAR_WIDTH 32
#define PKM_MAIN_CHAR_HEIGHT 32

#define PKM_GAME_FRUIT_FIRST_APPEAR 70   // fruit appears when 70 pallets are eaten
#define PKM_GAME_FRUIT_SECOND_APPEAR 170 // second appearance is when 170 pallets is eaten

///////////////////////////////////////////////////////////////////////
// All the scoring constants
///////////////////////////////////////////////////////////////////////
#define PKM_GAME_SMALL_PALLETS_NUM 240
#define PKM_GAME_BIG_PALLETS_NUM 4

#define PKM_GAME_SMALL_PALLET_POINTS 10 // each small pallet is worth 10 points
#define PKM_GAME_BIG_PALLET_POINTS 50   // each big pallet is worth 50 points

#define PKM_GAME_GHOST1_POINTS 200  // base point for ghost starts 200
#define PKM_GAME_GHOST2_POINTS 400  // second ghost is worth 400
#define PKM_GAME_GHOST3_POINTS 800  // base point for ghost starts 800
#define PKM_GAME_GHOST4_POINTS 1600 // second ghost is worth 1600

#define PKM_GAME_FRUIT_CHERRIES_POINTS 100
#define PKM_GAME_FRUIT_STRAWBERRY_POINTS 300
#define PKM_GAME_FRUIT_PEACH_POINTS 500
#define PKM_GAME_FRUIT_APPLE_POINTS 700
#define PKM_GAME_FRUIT_GRAPES_POINTS 1000
#define PKM_GAME_FRUIT_GALAXIAN_POINTS 2000
#define PKM_GAME_FRUIT_BELL_POINTS 3000
#define PKM_GAME_FRUIT_KEY_POINTS 5000

extern void pkm_game_init();
extern void pkm_game_quit();

// update all of puckman's status and direction
extern void pkm_game_setPuckmanDirection(int direction); // when a direction key is hit
extern int pkm_game_getPuckmanDirection();

extern void pkm_game_updateGame(); // call this function at every interval

extern int pkm_game_getPuckmanAliveStatus();
extern int pkm_game_getPuckmanHealthStatus();
extern SDL_Point pkm_game_getPuckmanLocation();
extern float pkm_game_getPuckmanSpeedDelta();

// pkm_game_timerUpdate();
// pkm_game_userUpdate();

// pkm_menu_userUpdate();