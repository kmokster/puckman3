#ifndef _PCKMAN_STATE_H
#define _PCKMAN_STATE_H

///////////////////////////////////////////////////////////////////////////////////////////
//
// Placeholder to track the state of the game
//
///////////////////////////////////////////////////////////////////////////////////////////

extern enum PMAN_DIRECTION { PMAN_UP,
                             PMAN_DOWN,
                             PMAN_LEFT,
                             PMAN_RIGHT };

extern struct PCKMAN_STATE_PACMAN
{
    /* data */
    int state;
    enum PMAN_DIRECTION direction;
} pckman_state_pacman;

#endif