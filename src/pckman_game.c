/**
 * @file pckman_game.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-08-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdbool.h>
#include <SDL.h>

#include "pckman_game.h"
#include "pckman_state.h"

typedef struct puckman_character_structure
{
    SDL_Point location;
    int status;
    int direction;
} pkm_char_struct;

struct puckman_game_structure
{
    Uint32 high_score;
    Uint32 current_score;
    // maze data store
    //  pallet data store
    pkm_char_struct puckman_track;
    pkm_char_struct blinky_track;
    pkm_char_struct inky_track;
    pkm_char_struct clyde_track;
    int puckman_lives_left;
    // struct for fruits

    int puckman_direction;
} pkm_game_struct;

int _gameHiScore = 0; // track the games hi score

extern void pkm_game_init()
{
    pkm_game_struct.high_score = _gameHiScore;
}

extern void pkm_game_quit()
{
}

extern void pkm_game_setPuckmanDirection(int direction)
{
    return;
}

extern void pkm_game_updateGame()
{
    return;
}