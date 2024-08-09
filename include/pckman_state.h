#ifndef _PCKMAN_STATE_H
#define _PCKMAN_STATE_H

///////////////////////////////////////////////////////////////////////////////////////////
//
// Placeholder to track the state of the game
//
///////////////////////////////////////////////////////////////////////////////////////////

// this is where the puckman is facing
extern enum PUCKMAN_DIRECTION {
    PUCKMAN_DIRECTION_RIGHT = 0, // puckman is moving right
    PUCKMAN_DIRECTION_LEFT = 1,  // puckman is moving left
    PUCKMAN_DIRECTION_UP = 2,    // puckman is moving up
    PUCKMAN_DIRECTION_DOWN = 3,  // puckman is moving down
    PUCKMAN_DIRECTION_NONE = 4
};

extern enum PKM_PUCKMAN_HEALTH_STATE {
    PUCKMAN_ALIVE, // puckman is alive but weak so ghost can kill em
    PUCKMAN_AGGRO, // puckman is now in aggro state and can eat ghost
    PUCKMAN_DEAD   // puckman is dead
};

extern enum PKM_PUCKMAN_ALIVE_STATE {
    PUCKMAN_ALIVE_START,  // its at the start position
    PUCKMAN_ALIVE_MOVING, // puckman is moving
    PUCKMAN_ALIVE_STOP    // puckman is stopped
};

extern enum PKM_GHOST_CHASE_DIRECTION {
    GHOST_DIRECTION_RIGHT = 0,
    GHOST_DIRECTOIN_LEFT = 1,
    GHOST_DIRECTION_UP = 2,
    GHOST_DIRECTION_DOWN = 3,
    GHOST_DIRECTION_NONE = 4
};

extern enum PKM_GHOST_STATE {
    GHOST_HOME,       // ghost is at home
    GHOST_CHASE,      // ghost is hunting puckman
    GHOST_SCATTER,    // ghost gives up the chase for a few seconds and return to their home corner
    GHOST_FRIGHTENED, // ghost is weak and running away from puckman
    GHOST_SPAWNING,   // ghost is dead and going home to spawn
};

extern enum PKM_MAIN_STATE {
    GAME_MAIN_MENU = 0,
    GAME_MAIN_PLAYING = 1,
    GAME_MAIN_SCREENSAVER = 2,
};

extern enum PKM_MENU_STATE {
    MENU_CUSTOM1,
    MENU_CUSTOM2,
    MENU_CUSTOM3
};

extern enum PKM_GAME_STATE {
    GAME_START = 0,
    GAME_ACTIVE = 1,
    GAME_PAUSE = 2,
    GAME_LEVEL_CLEARED = 3,
    GAME_DEAD = 4,
    GAME_END = 5
};

extern enum PKM_MAZE_CELL_STATE {
    MAZE_CELL_BLOCK = 0,
    MAZE_CELL_UNBLOCK = 1
};

extern enum PKM_MAZE_DISPLAY_STATE {
    MAZE_ACTIVE = 0, // display maze in regular mode
    MAZE_BLINK = 1   // blink the maze
};

#endif