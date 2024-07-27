#include <stdbool.h>
#include <stdio.h>

#include <SDL.h>
#include "pckman_graphics.h"
#include "pckman_state.h"

const SDL_Window *_pkmanWindow = NULL;
const SDL_Renderer *_pkmanRenderer = NULL;
const SDL_Texture *_pkmanSpriteTexture = NULL;

/// @brief Initialises the SDL video subsystem
/// @return 0 if no error otherwise the error code returned by SDL_Init
extern int pckman_grp_initVideo()
{
    int error_code = 0;

    error_code = SDL_Init(SDL_INIT_VIDEO);

    return error_code;
}

extern int pckman_grp_displayWindow(char *title, int x, int y, int width, int height, Uint32 flags)
{
    int error_code = 0;
    char app_name[64];

    if (error_code == 0)
    {
        if (SDL_WasInit(SDL_INIT_VIDEO) == 0)
            error_code = pckman_grp_initVideo();

        if (error_code == 0)
        {
            _pkmanWindow = SDL_CreateWindow(title, x, y, width, height, flags);

            if (_pkmanWindow == NULL)
            {
                error_code = SDL_GetError();
            }
        }
    }

    return error_code;
}

extern int pckman_grp_displayWindowCentered(char *title, int width, int height, Uint32 flags)
{
    // get the current screen width and height
    int error_code = 0;
    int centerX = 0;
    int centerY = 0;

    SDL_DisplayMode displayMode;

    error_code = SDL_GetCurrentDisplayMode(0, &displayMode);

    centerX = (displayMode.w / 2) - (width / 2);
    centerY = (displayMode.h / 2) - (height / 2);

    error_code = pckman_grp_displayWindow(title, centerX, centerY, width, height, flags);

    if (error_code != 0)
        SDL_Log("error detected in pckman_grp_displayWindowCentered");
    else
        SDL_Log("No Error and window should be displaying");

    return error_code;
}

extern int pckman_grp_initWindow(char *title)
{
    int error_code = 0;
    error_code = pckman_grp_displayWindowCentered(title, 480, 640, SDL_WINDOW_HIDDEN);

    if (error_code == 0)
    {
        // get the renderer
        _pkmanRenderer = SDL_CreateRenderer(_pkmanWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (_pkmanRenderer == NULL)
        {
            error_code = -1;
        }
    }

    return error_code;
}

extern int pckman_grp_loadSprite()
{
    int error_code = 0;
    char *pkmanSpriteFile;
    SDL_Surface *pkmanSurface = NULL;
    SDL_Rect pkmanRect = {0, 0, 16, 16};
    SDL_Rect displayRect = {(PKM_GRP_WIN_WIDTH - 16) / 2,
                            (PKM_GRP_WIN_HEIGHT - 16) / 2,
                            16, 16};
    // load the bmp sprite first
    sprintf(pkmanSpriteFile, "%s%s%s", PKM_GRP_RES_DIR, PKM_GRP_RES_GRP, "PuckMan-Main.bmp");
    SDL_Log(pkmanSpriteFile);

    pkmanSurface = SDL_LoadBMP(pkmanSpriteFile);
    // set the transparent color key
    // we use cyan (0x0FFFFF) as the background colour
    SDL_SetColorKey(pkmanSurface, SDL_TRUE, PKM_GRP_TRANSPARENCY_HEX);

    if (pkmanSurface != NULL)
    {
        _pkmanSpriteTexture = SDL_CreateTextureFromSurface(_pkmanRenderer, pkmanSurface);

        if (_pkmanSpriteTexture != NULL)
        {
            // now we free the surface since we are done
            SDL_FreeSurface(pkmanSurface);

            // set the background colour
            SDL_SetRenderDrawColor(_pkmanRenderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(_pkmanRenderer);

            // display onto the window
            SDL_RenderCopyEx(_pkmanRenderer, _pkmanSpriteTexture, &pkmanRect, &displayRect, 0, NULL, SDL_FLIP_NONE);
            SDL_RenderPresent(_pkmanRenderer);
        }
        else
        {
            error_code = -2;
        }
    }
    else
    {
        // unable to initialise the surface
        error_code = -1;
    }

    // to test this code, we display it here

    return error_code;
}

extern const SDL_Window *pckman_grp_getWindow()
{
    return _pkmanWindow;
}

extern const SDL_Renderer *pckman_grp_getRenderer()
{
    return _pkmanRenderer;
}

extern void pckman_grp_destroyWindow()
{
    // free all texture
    if (_pkmanSpriteTexture != NULL)
        SDL_DestroyTexture(_pkmanSpriteTexture);

    // if the renderer is not null, destroy it
    if (_pkmanRenderer != NULL)
        SDL_DestroyRenderer(_pkmanRenderer);

    // finally destroy the window
    if (_pkmanWindow != NULL)
        SDL_DestroyWindow(_pkmanWindow);
}

extern void pckman_grp_quitVideo()
{
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}