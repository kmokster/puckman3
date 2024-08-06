#ifndef _PCKMAN_STATE_H
#define _PCKMAN_STATE_H

///////////////////////////////////////////////////////////////////////////////////////////
//
// Placeholder to track the state of the game
//
///////////////////////////////////////////////////////////////////////////////////////////

// this is where the puckman is facing
extern enum PUCKMAN_DIRECTION {
    PUCKMAN_RIGHT = 0, // puckman is moving right
    PUCKMAN_LEFT = 1,  // puckman is moving left
    PUCKMAN_UP = 2,    // puckman is moving up
    PUCKMAN_DOWN = 3,  // puckman is moving down
};

extern enum PKM_PUCKMAN_STATE {
    PUCKMAN_ALIVE, // puckman is alive but weak so ghost can kill em
    PUCKMAN_AGGRO, // puckman is now in aggro state and can eat ghost
    PUCKMAN_DEAD   // puckman is dead
};

extern enum PKM_GHOST_STATE {
    HOME,
    HUNTING,
    RUNNING,
    SPAWNING,
};

extern enum PKM_MAIN_STATE {
    MENU = 0,
    GAME = 1,
    SCREENSAVER = 2,
};

extern enum PKM_MENU_STATE {
    CUSTOM1,
    CUSTOM2,
    CUSTOM3
};

extern enum PKM_GAME_STATE {
    START = 0,
    ACTIVE = 1,
    PAUSE = 2,
    LEVEL_CLEARED = 3,
    DEAD = 4,
    END = 5
};

#endif