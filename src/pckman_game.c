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

/// @brief structure to track puckman
typedef struct puckman_character_structure
{
    SDL_Point location; // set the location of puckman
    int health_status;  // tracks the health of puckman
    int alive_status;   // tracks the status while puckman is still alive
    int direction;      // tracks the current direction of puckman
} _puckmanStatus;

typedef struct ghost_character_structure
{
    SDL_Point location;
    int health_status;
    int alive_status;
    int direction;
} _ghostStatus;

struct puckman_game_structure
{
    Uint32 high_score;
    Uint32 current_score;
    // maze data store
    //  pallet data store
    _puckmanStatus puckman;
    _ghostStatus blink;
    _ghostStatus pinky;
    _ghostStatus inky;
    _ghostStatus clyde;
    int puckman_lives_left;
    // struct for fruits

    int puckman_direction;
} _pkm_game;

int _gameHiScore = 0; // track the games hi score

extern void pkm_game_init()
{
    _pkm_game.high_score = _gameHiScore;
    _pkm_game.current_score = 0;

    // setup the puckman health
    _pkm_game.puckman.health_status = PUCKMAN_ALIVE;
    _pkm_game.puckman.alive_status = PUCKMAN_ALIVE_START;
    _pkm_game.puckman.direction = PUCKMAN_DIRECTION_NONE;

    // initialize the puckman starting position
    // for now at the center of the screen
    _pkm_game.puckman.location.x = (PKM_MAIN_WIN_WIDTH - PKM_MAIN_CHAR_WIDTH) / 2;
    _pkm_game.puckman.location.y = (PKM_MAIN_WIN_HEIGHT - PKM_MAIN_CHAR_HEIGHT) / 2;

    SDL_Log("x location for puckman is: %d", _pkm_game.puckman.location.x);
    SDL_Log("y location for puckman is: %d", _pkm_game.puckman.location.y);

    // loadMazeMap();
}

extern void pkm_game_quit()
{
}

extern void pkm_game_setPuckmanDirection(int direction)
{
    _pkm_game.puckman.direction = direction;
    _pkm_game.puckman.alive_status = PUCKMAN_ALIVE_MOVING;
    return;
}

extern int pkm_game_getPuckmanDirection()
{
    return _pkm_game.puckman.direction;
}

extern int pkm_game_getPuckmanHealthStatus()
{
    return _pkm_game.puckman.health_status;
}

extern int pkm_game_getPuckmanAliveStatus()
{
    return _pkm_game.puckman.alive_status;
}

extern SDL_Point pkm_game_getPuckmanLocation()
{
    return _pkm_game.puckman.location;
}

/// @brief
extern void pkm_game_movePuckman()
{
    int pixel2move = PKM_MAIN_REGULAR_SPEED;
    int puckman_x = _pkm_game.puckman.location.x;
    int puckman_y = _pkm_game.puckman.location.y;

    switch (_pkm_game.puckman.direction)
    {
    case PUCKMAN_DIRECTION_LEFT: // calculate the next pixel 2 move to
                                 // for now just check if it negative after moving left and if so, set the x pos to 0
        puckman_x = puckman_x - pixel2move;
        if (puckman_x <= 0)
        {
            puckman_x = 0;
            // set the puckman to stop
            // this will hopefully cause the puckman render to just display puckman in a open mouth status
            _pkm_game.puckman.alive_status = PUCKMAN_ALIVE_STOP;
            // we now await for gamer to send us the next direction
            _pkm_game.puckman.direction = PUCKMAN_DIRECTION_NONE;
        }
        else
        {
            _pkm_game.puckman.location.x = puckman_x;
        }
        return;
    case PUCKMAN_DIRECTION_RIGHT:
        // this forward check have to check for the puckman position being off screen
        // this is because we are using the top left co-ordinate as reference
        puckman_x = puckman_x + (pixel2move + PKM_MAIN_CHAR_WIDTH);
        if (puckman_x >= PKM_MAIN_WIN_WIDTH)
        {
            puckman_x = (PKM_MAIN_WIN_WIDTH - PKM_MAIN_CHAR_WIDTH);
            // this will hopefully cause the puckman render to just display puckman in a open mouth status
            _pkm_game.puckman.alive_status = PUCKMAN_ALIVE_STOP;
            // we now await for gamer to send us the next direction
            _pkm_game.puckman.direction = PUCKMAN_DIRECTION_NONE;
        }
        else
        {
            // need to remove the offset
            _pkm_game.puckman.location.x = puckman_x - PKM_MAIN_CHAR_WIDTH;
        }
        return;
    case PUCKMAN_DIRECTION_UP:
        puckman_y = puckman_y - pixel2move;
        if (puckman_y <= 0)
        {
            puckman_y = 0;
            _pkm_game.puckman.alive_status = PUCKMAN_ALIVE_STOP;
            _pkm_game.puckman.direction = PUCKMAN_DIRECTION_NONE;
        }
        else
        {
            _pkm_game.puckman.location.y = puckman_y;
        }
        return;
    case PUCKMAN_DIRECTION_DOWN:
        // this check have to offset the height
        // otherwise the render goes off screen
        puckman_y = puckman_y + (pixel2move + PKM_MAIN_CHAR_HEIGHT);
        if (puckman_y >= PKM_MAIN_WIN_HEIGHT)
        {
            puckman_y = PKM_MAIN_WIN_HEIGHT - PKM_MAIN_CHAR_HEIGHT;
            _pkm_game.puckman.alive_status = PUCKMAN_ALIVE_STOP;
            _pkm_game.puckman.direction = PUCKMAN_DIRECTION_NONE;
        }
        else
        {
            _pkm_game.puckman.location.y = puckman_y - PKM_MAIN_CHAR_HEIGHT;
        }
        return;
    default: // no direction and its just at the start of the game
        return;
    }

    // here is what needs to happen on a simple level
    // check the current position of puckman
    // check if there is any collision with ghost
    // update all the states

    // of course we need to check if puckman is on aggro
    return;
}
