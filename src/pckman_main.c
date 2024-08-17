/**
 * @file pckman_main.c
 * @author Kevin Mok
 * @brief
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <stdbool.h>
#include <SDL.h>
#include <SDL_timer.h>

#include "pckman_main.h"
#include "pckman_state.h"
#include "pckman_puckman.h"
#include "pckman_game.h"
#include "pckman_error.h"

// define all the main components
const SDL_Window *_mainWindow = NULL;
const SDL_Renderer *_mainRenderer = NULL;

// the base layer texture
SDL_Texture *_mainTexture = NULL;

// calculate the row and height for the grid
const int _mainGridRows = PKM_MAIN_WIN_HEIGHT / PKM_MAIN_CELL_HEIGHT;
const int _mainGridColumns = PKM_MAIN_WIN_WIDTH / PKM_MAIN_CELL_WIDTH;

// make the 60fps
const float _mainFPS = 1000 / PKM_MAIN_FPS;

/// @brief initialize SDL, windows and create texture etc.
/// @return 0 if no error, non-zero if error
int initSDL()
{
    int error_code = 0;

    int win_x;                    // x co-ordinate of the window to display
    int win_y;                    // y co-ordinate of the window to display
    SDL_DisplayMode display_mode; // use to enquire the size of the monitor screen
    SDL_Surface main_surface;

    char gameTitle[128];
    Uint32 ticks;

    // format the game title
    sprintf(gameTitle, "%s version %s.%s", PKM_MAIN_APPNAME, PKM_MAIN_MAJOR, PKM_MAIN_MINOR);

    // initialize SDL and its subsystem
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        error_code = PKM_ERROR_MAIN_INIT_SDL_INIT;
        goto error;
    }

    // use display mode to determine the size of the screen
    if (SDL_GetCurrentDisplayMode(0, &display_mode) != 0)
    {
        error_code = PKM_ERROR_MAIN_INIT_SDL_DISP;
        goto error;
    }

    // for now find the halfway mark to set where puckman should be displayed at
    // TODO: check if this is a required step since the start pos is determined by pckman_game
    win_x = (display_mode.w - PKM_MAIN_WIN_WIDTH) / 2;
    win_y = (display_mode.h - PKM_MAIN_WIN_HEIGHT) / 2;

    // create the main window in HIDE mode first
    _mainWindow = SDL_CreateWindow(gameTitle, win_x, win_y, PKM_MAIN_WIN_WIDTH, PKM_MAIN_WIN_HEIGHT, SDL_WINDOW_HIDDEN);

    if (_mainWindow == NULL)
    {
        error_code = PKM_ERROR_MAIN_INIT_SDL_CWIN;
        goto error;
    }

    // create the Renderer
    _mainRenderer = SDL_CreateRenderer(_mainWindow, 0, SDL_RENDERER_ACCELERATED);
    if (_mainRenderer == NULL)
    {
        error_code = PKM_ERROR_MAIN_INIT_SDL_REND;
        goto error;
    }

    // Get the background texture to the whole window
    // TODO: check if this is required or where is should it be created and stored?
    _mainTexture = SDL_CreateTexture(_mainRenderer,
                                     SDL_PIXELFORMAT_RGBX8888,
                                     SDL_TEXTUREACCESS_STREAMING,
                                     PKM_MAIN_WIN_WIDTH, PKM_MAIN_WIN_HEIGHT);

    if (_mainTexture == NULL)
    {
        error_code = PKM_ERROR_MAIN_INIT_SDL_TEXT;
        goto error;
    }

    goto end;

error:
    SDL_Log("main::initGame Game Init Error: %d", error_code);
    return error_code;

end:
    SDL_Log("main::initGame Game Init successful!");
    return 0;
}

/// @brief use to load all assets for the game e.g. images, audio etc
/// @return 0 if no error
int loadAssets()
{
    int error_code = 0;

    error_code = puckman_load_sprite(_mainRenderer);

    if (error_code != 0)
        goto error;

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

    goto end;

error:
    SDL_Log("main:loadAssets loadAsset error: %d", error_code);
    return error_code;

end:
    SDL_Log("main:loadAssets loadAsset successful: %d", error_code);
    return error_code;
}

/// @brief Initialize the SDL System, Create the window at the center of the screen and then get the renderer
/// @return
///         0 - if no error
///        -1 - window creation error
///        -2 - renderer creation error
int initGame()
{
    int error_code = 0;

    if ((error_code = initSDL()) != 0)
    {
        goto error;
    }

    // TODO - 10/8
    // move game init to the main game loop?
    pkm_game_init(); // initialise the game structure

    error_code = loadAssets();
    if (error_code != 0)
    {
        goto error;
    }

    goto end;

error:
    printf("main::initApp Error: %d\n", error_code);
    return error_code;

end:
    SDL_Log("main::initApp Game Init successful!");
    return 0;
}

/// @brief this is the main game loop
/// @return
int startGame()
{
    int error_code = 0;
    bool quit_flag = false; // track if user hit quit button or close the window
    SDL_Event e;            // track all events
                            //    SDL_Rect puckmanRect;
    float lastTick, nextTick, diffTick;
    float wakaFrameCount = 0;
    float puckmanMoveFrameCount = 0;

    SDL_ShowWindow(_mainWindow); // display the hidden window

    if (SDL_RenderClear(_mainRenderer) != 0) // clear screen
    {
        error_code = PKM_ERROR_MAIN_STARTGAME_RENCLR;
        goto error;
    }

    drawGrid();                                  // for now draw the grid
    puckman_alive_animate2(_mainRenderer, true); // draw puckman
    SDL_RenderPresent(_mainRenderer);
    lastTick = SDL_GetTicks();

    while (quit_flag == false)
    {
        nextTick = (float)SDL_GetTicks();
        diffTick = (float)(nextTick - lastTick);
        if (diffTick >= _mainFPS) // going into FPS
        {
            // animate every 60fps
            SDL_RenderClear(_mainRenderer); // clear the screen
            drawGrid();                     // draw the grid for now

            // TODO: MOVE THE WAKA COUNT TO PUCKMAN?
            bool wakaRefresh = false;
            if (wakaFrameCount == PKM_MAIN_WAKA_FRAME_COUNT)
            {
                // do the animation
                wakaRefresh = true;
                wakaFrameCount = 0;
            }
            else
            {
                wakaRefresh = false;
                wakaFrameCount++;
            }

            // this section moves puckman base on the speed delta in wich puckman moves
            if (puckmanMoveFrameCount >= PKM_MAIN_GAME_FRAME_COUNT)
            {
                // update the game first
                pkm_game_updateGame();     // move puckman by the number of pixel
                puckmanMoveFrameCount = 0; // reset the game frame count
            }
            else
            {
                puckmanMoveFrameCount = puckmanMoveFrameCount + (1 * pkm_game_getPuckmanSpeedDelta());
            }

            puckman_alive_animate2(_mainRenderer, wakaRefresh);
            SDL_RenderPresent(_mainRenderer);

            lastTick = SDL_GetTicks();
        }
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit_flag = true;
                SDL_Log("Program quit after %i ticks!\n", e.quit.timestamp);
            }
            else if (e.type == SDL_KEYDOWN)
            {
                SDL_KeyCode keycode = e.key.keysym.sym;

                if ((keycode == SDLK_a) || (keycode == SDLK_LEFT))
                {
                    SDL_Log("Puckman direction LEFT ->");
                    pkm_game_setPuckmanDirection(PUCKMAN_DIRECTION_LEFT);
                }
                else if ((keycode == SDLK_d) || (keycode == SDLK_RIGHT))
                {
                    SDL_Log("Puckman direction RIGHT <-");
                    pkm_game_setPuckmanDirection(PUCKMAN_DIRECTION_RIGHT);
                }
                else if ((keycode == SDLK_w) || (keycode == SDLK_UP))
                {
                    SDL_Log("Puckman direction UP ^");
                    pkm_game_setPuckmanDirection(PUCKMAN_DIRECTION_UP);
                }
                else if ((keycode == SDLK_s) || (keycode == SDLK_DOWN))
                {
                    SDL_Log("Puckman direction DOWN v");
                    pkm_game_setPuckmanDirection(PUCKMAN_DIRECTION_DOWN);
                }
            }
        }
    }
    goto end;

error:
    return error_code;
end:
    return 0;
}

// draw the grid
void drawGrid()
{
    Uint8 u8r, u8g, u8b, u8a; // store the current color

    SDL_GetRenderDrawColor(_mainRenderer, &u8r, &u8g, &u8b, &u8a);
    SDL_SetRenderDrawBlendMode(_mainRenderer, SDL_BLENDMODE_BLEND); // new blend mode for alpha
    SDL_SetRenderDrawColor(_mainRenderer,
                           PKM_MAIN_GRID_COLOR_R,
                           PKM_MAIN_GRID_COLOR_G,
                           PKM_MAIN_GRID_COLOR_B,
                           PKM_MAIN_GRID_COLOR_A);

    // draw the row first
    for (int row = PKM_MAIN_CELL_HEIGHT; row < PKM_MAIN_WIN_HEIGHT; row += PKM_MAIN_CELL_HEIGHT)
    {
        SDL_RenderDrawLine(_mainRenderer, 0, row, PKM_MAIN_WIN_WIDTH, row);
    }

    // draw the column next
    for (int column = PKM_MAIN_CELL_WIDTH; column < PKM_MAIN_WIN_WIDTH; column += PKM_MAIN_CELL_WIDTH)
    {
        SDL_RenderDrawLine(_mainRenderer, column, 0, column, PKM_MAIN_WIN_HEIGHT);
    }

    SDL_SetRenderDrawBlendMode(_mainRenderer, SDL_BLENDMODE_NONE);

    SDL_SetRenderDrawColor(_mainRenderer, u8r, u8g, u8b, u8a);
}

void unloadAssets()
{
    puckman_free_sprite();
    // maze_free_sprite();
    // blinky_free_sprite();
    // inky_free_sprite();
    // pinky_free_sprite();
    // clyde_free_sprite();
    // weakGhost_free_sprite();
    // pallets_free_sprite();
    // fruits_free_sprite():
    // menu_free_sprite();

    // pkm_font_free();
    // pkm_audio_free();
}

void quitGame()
{
    unloadAssets();

    if (_mainTexture != NULL)
        SDL_DestroyTexture(_mainTexture);

    if (_mainRenderer != NULL)
        SDL_DestroyRenderer(_mainRenderer);

    if (_mainWindow != NULL)
        SDL_DestroyWindow(_mainWindow);

    SDL_Quit();
}

/// @brief The main function.
/// @param argc
/// @param args
/// @return
int main(int argc, char *args[])
{
    int error_code;

    if ((error_code = initGame()) != 0) // initialise the application
        goto error;

    if ((error_code = startGame()) != 0) // start the game loop
        goto error;

    goto end;

error:
    printf("Critical error in main loop with error code: %d \n", error_code);
    return error_code;

end:
    quitGame();
    return 0;
}