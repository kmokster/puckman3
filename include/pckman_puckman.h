#ifndef _PCKMAN_PUCKMAN_H
#define _PCKMAN_PUCKMAN_H

#include <SDL.h>

#define PKM_PUCKMAN_WAKA_BMP "./res/graphics/puckman-alive.bmp"
#define PKM_PUCKMAN_DIE_BMP "./res/graphics/PuckMan-Die.bmp"
#define PKM_PUCKMAN_WIDTH 16
#define PKM_PUCKMAN_HEIGHT 16

// the PUCKMAN_WAKA is the represenation of the 4 sequence in which puckman is animated
enum PUCKMAN_WAKA
{
    PUCKMAN_FULL = 0,
    PUCKMAN_OPEN = 1,
    PUCKMAN_WIDE = 2,
    PUCKMAN_CLOSE = 3
};

extern int puckman_load_sprite(const SDL_Renderer *renderer);
extern void puckman_free_sprite();

extern int puckman_alive_animate(const SDL_Renderer *renderer, const SDL_Rect *pos2Render);
extern int puckman_alive_animate2(const SDL_Renderer *renderer, bool nextFrame, const SDL_Rect *pos2Render);

extern void puckman_setHealthStatus(int status);
extern void puckman_setAliveStatus(int status);

extern void puckman_setDirection(int direction);

extern void puckman_setDirectionRight();
extern void puckman_setDirectionLeft();
extern void puckman_setDirectionUp();
extern void puckman_setDirectionDown();

// setPuckmanState
// animateWaka
// animateDeath

// getLastPosXY
// setCurrentPosXY

#endif