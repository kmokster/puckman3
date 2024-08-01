#ifndef _PCKMAN_PUCKMAN_H
#define _PCKMAN_PUCKMAN_H

#include <SDL.h>

#define PKM_PUCKMAN_WAKA_BMP "./res/graphics/puckman-alive.bmp"
#define PKM_PUCKMAN_DIE_BMP "./res/graphics/PuckMan-Die.bmp"
#define PKM_PUCKMAN_WIDTH 16
#define PKM_PUCKMAN_HEIGHT 16

enum PUCKMAN_STATE
{
    PUCKMAN_ALIVE,
    PUCKMAN_DEAD
};

enum PUCKMAN_DIRECTION
{
    PUCKMAN_LEFT,
    PUCKMAN_RIGHT,
    PUCKMAN_UP,
    PUCKMAN_DOWN,
};

extern int puckman_load_sprite(const SDL_Renderer *renderer);
extern void puckman_free_sprite();

extern int puckman_animate(const SDL_Renderer *renderer, const SDL_Rect *pos2Render);

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