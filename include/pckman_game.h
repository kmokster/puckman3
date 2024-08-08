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

#define PKM_MAIN_WIN_WIDTH 496
#define PKM_MAIN_WIN_HEIGHT 640

// frame count before updates
#define PKM_MAIN_WAKA_FRAME_COUNT 2 // we waka every 4 frames?
#define PKM_MAIN_GAME_FRAME_COUNT 3 // we update the game every 6 frames?

// the number of pixel to move
#define PKM_MAIN_REGULAR_SPEED 4 // use 4 pixel movement for regular speed
#define PKM_MAIN_UP_SPEED 6      // use 6 pixel movement for speed ups

#define PKM_MAIN_CELL_WIDTH 16
#define PKM_MAIN_CELL_HEIGHT 16
#define PKM_MAIN_CHAR_WIDTH 32
#define PKM_MAIN_CHAR_HEIGHT 32

extern void pkm_game_init();
extern void pkm_game_quit();

// update all of puckman's status and direction
extern void pkm_game_setPuckmanDirection(int direction); // when a direction key is hit
extern int pkm_game_getPuckmanDirection();

extern void pkm_game_movePuckman(); // call this functoin at every interval

extern int pkm_game_getPuckmanAliveStatus();
extern int pkm_game_getPuckmanHealthStatus();
extern SDL_Point pkm_game_getPuckmanLocation();

// pkm_game_timerUpdate();
// pkm_game_userUpdate();

// pkm_menu_userUpdate();