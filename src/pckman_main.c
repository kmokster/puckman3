#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

// #include "pckman_graphics.h"
#include "pckman_main.h"
#include "pckman_state.h"

// define all the main components
const SDL_Window *_mainWindow = NULL;
const SDL_Renderer *_mainRenderer = NULL;

int loadAssets()
{
    int error_code = 0;

    // pkm_puckman_loadSprite();
    // pkm_maze_loadSprite();
    // pkm_blinky_loadSprite();
    // pkm_inky_loadSprite();
    // pkm_pinky_loadSprite();
    // pkm_clyde_loadSprite();
    // pkm_weakGhost_loadSprite();
    // pkm_pallets_loadSprite();
    // pkm_fruits_loadSprite():
    // pkm_menu_loadSprite();

    // pkm_font_load();
    // pkm_audio_load();

    return error_code;
}

void displayWindow()
{
    SDL_ShowWindow(_mainWindow);
}

/// @brief Initialize the SDL System, Create the window at the center of the screen and then get the renderer
/// @return
///         0 - if no error
///        -1 - window creation error
///        -2 - renderer creation error
int initGame()
{
    int error_code;
    int win_x;
    int win_y;
    SDL_DisplayMode display_mode;
    char gameTitle[64];

    // intialize all the main application variables
    sprintf(gameTitle, "%s version %d.%d", PKM_MAIN_APPNAME, PKM_MAIN_MAJOR, PKM_MAIN_MINOR);

    // initialize SDL and its subsystem here
    error_code = SDL_Init(SDL_INIT_EVERYTHING);

    if (error_code == 0)
    {
        // use display mode to determine the size of the screen
        error_code = SDL_GetCurrentDisplayMode(0, &display_mode);
        win_x = (display_mode.w - PKM_MAIN_WIN_WIDTH) / 2;
        win_y = (display_mode.h - PKM_MAIN_WIN_HEIGHT) / 2;

        _mainWindow = SDL_CreateWindow(gameTitle, win_x, win_y, PKM_MAIN_WIN_WIDTH, PKM_MAIN_WIN_HEIGHT, SDL_WINDOW_HIDDEN);

        if (_mainWindow == NULL)
        {
            SDL_Log("Unable to create Window!!");
            error_code = -1;
        }
        else
        {
            _mainRenderer = SDL_CreateRenderer(_mainWindow, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (_mainRenderer == NULL)
            {
                SDL_Log("Unable to create Renderer!!");
                error_code = -2;
            }
        }
    }

    return error_code;
}

int quitGame()
{
    if (_mainRenderer != NULL)
        SDL_DestroyRenderer(_mainRenderer);

    if (_mainWindow != NULL)
        SDL_DestroyWindow(_mainWindow);

    SDL_Quit();
}

int main(int argc, char *args[])
{
    int error_code;
    bool quit_flag = false;
    SDL_Event e;

    error_code = initGame();

    if (error_code == 0)
    {
        displayWindow();

        if ((error_code == 0))
        {
            SDL_Log("Hello world from SDL2.\n");

            loadAssets();

            while (quit_flag == false)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit_flag = true;
                        SDL_Log("Program quit after %i ticks!\n", e.quit.timestamp);
                    }
                }
            }

            // unloadAssets();
        }
    }
    else
    {
        printf("ERORR in initialisation\n");
    }

    quitGame();

    return 0;
}