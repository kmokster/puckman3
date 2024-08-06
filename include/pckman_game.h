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

extern void pkm_game_init();
extern void pkm_game_quit();

// update all of puckman's status and direction
extern void pkm_game_setPuckmanDirection(int direction);
extern void pkm_game_updateGame(); // call this functoin at every interval

// pkm_game_timerUpdate();
// pkm_game_userUpdate();

// pkm_menu_userUpdate();