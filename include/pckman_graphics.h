#ifndef _PCKMAN_GRAPHICS_H
#define _PCKMAN_GRAPHICS_H

#include <SDL.h>

#define PKM_GRP_WIN_WIDTH 480
#define PKM_GRP_WIN_HEIGHT 680

#define PKM_GRP_RES_DIR "./res/"
#define PKM_GRP_RES_GRP "graphics/"
#define PKM_GRP_FILE_PKMAN_BMP "pkman.bmp"

#define PKM_GRP_TRANSPARENCY_HEX 0x00FFFF

#define PKM_GRP_PKMAN_SPRITE_HEIGHT 16
#define PKM_GRP_PKMAN_SPRITE_WIDTH 16
#define PKM_GRP_PKMAN_SPRITE_ANIMATE 9
#define PKM_GRP_PKMAN_SPRITE_LENGTH 16 * 9

enum PKM_GRP_PKMAN_ANIMATE_SEQUENCE
{
    E_PKMAN_CLOSE,
    E_PKMAN_RIGHT_OPEN,
    E_PKMAN_RIGHT_WIDE,
    E_PKMAN_LEFT_OPEN,
    E_PKMAN_LEFT_WIDE,
    E_PKMAN_UP_OPEN,
    E_PKMAN_UP_WIDE,
    E_PKMAN_DOWN_OPEN,
    E_PKMAN_DOWN_WIDE
};

///////////////////////////////////////////////////////////////////////////////////////////
//
// Placeholder for all graphic base functions including display and asset loading
//
///////////////////////////////////////////////////////////////////////////////////////////

extern const SDL_Window *pckman_grp_getWindow();
extern const SDL_Renderer *pckman_grp_getRenderer();

// init functions
extern int pckman_grp_initVideo();

// init the window without displaying it
extern int pckman_grp_initWindow(char *title);

// load the packman image assets
extern int pckman_grp_loadSprite();

// display the window
extern int pckman_grp_displayWindow(char *title, int x, int y, int width, int height, Uint32 flags);

// display the window centered
extern int pckman_grp_displayWindowCentered(char *title, int width, int height, Uint32 flags);

// destroy the window when done
extern void pckman_grp_destroyWindow();

// quit the video
extern void pckman_grp_quitVideo();

#endif