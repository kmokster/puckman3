#ifndef _PCKMAN_PUCKMAN_H
#define _PCKMAN_PUCKMAN_H

#include <SDL.h>

#define PKM_PUCKMAN_WAKA_BMP "./res/graphics/PuckMan-Main.bmp"
#define PKM_PUCKMAN_DIE_BMP "./res/graphics/PuckMan-Die.bmp"
#define PKM_PUCKMAN_WIDTH 16
#define PKM_PUCKMAN_HEIGHT 16
#define PKM_PUCKMAN_WAKA_SEQUENCE 9
#define PKM_PUCKMAN_DEAD_SEQUENCE 10

enum PUCKMAN_STATE
{
    PUCKMAN_ALIVE,
    PUCKMAN_DEAD
};

extern int puckman_loadAsset(const SDL_Renderer *renderer);

// setPuckmanState
// animateWaka
// animateDeath
// moveLeft
// moveRight
// moveUp
// moveDown
// getLastPosXY
// setCurrentPosXY

#endif