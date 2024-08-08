#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_timer.h>

// #include "pckman_graphics.h"
#include "pckman_main.h"
#include "pckman_state.h"
#include "pckman_puckman.h"
#include "pckman_game.h"

// define all the main components
const SDL_Window *_mainWindow = NULL;
const SDL_Renderer *_mainRenderer = NULL;

// the base layer texture
SDL_Texture *_mainTexture = NULL;

// calculate the row and height for the grid
const int _mainGridRows = PKM_MAIN_WIN_HEIGHT / PKM_MAIN_CELL_HEIGHT;
const int _mainGridColumns = PKM_MAIN_WIN_WIDTH / PKM_MAIN_CELL_WIDTH;

int loadAssets()
{
    int error_code = 0;

    error_code = puckman_load_sprite(_mainRenderer);

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

end:
    return error_code;
}

void unloadAssets()
{
    puckman_free_sprite();
}

void displayWindow()
{
    SDL_ShowWindow(_mainWindow);
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
    SDL_Surface main_surface;
    char gameTitle[64];
    Uint32 ticks;

    // intialize all the main application variables
    sprintf(gameTitle, "%s version %s.%s", PKM_MAIN_APPNAME, PKM_MAIN_MAJOR, PKM_MAIN_MINOR);

    // initialize SDL and its subsystem here
    error_code = SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Init(SDL_INIT_TIMER);

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
            else
            {
                // _mainTexture = SDL_CreateTexture(_mainRenderer,
                // SDL_PIXELFORMAT_RGBX8888,
                // SDL_TEXTUREACCESS_STREAMING,
                // 640, 480);

                _mainTexture = SDL_CreateTexture(_mainRenderer,
                                                 SDL_PIXELFORMAT_RGBX8888,
                                                 SDL_TEXTUREACCESS_STREAMING,
                                                 PKM_MAIN_WIN_WIDTH, PKM_MAIN_WIN_HEIGHT);
            }

            // initialize the main game logic controller
            SDL_Log("initializing the main game logic");
            pkm_game_init();
        }
    }

    return error_code;
}

int quitGame()
{

    if (_mainTexture != NULL)
        SDL_DestroyTexture(_mainTexture);

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
    SDL_Rect puckmanRect;
    Uint32 lastTick, nextTick, diffTick;
    int wakaFrameCount = 0;
    int gameFrameCount = 0;

    error_code = initGame();

    if (error_code == 0)
    {
        error_code = loadAssets();

        if ((error_code == 0))
        {
            puckmanRect.x = pkm_game_getPuckmanLocation().x;
            puckmanRect.y = pkm_game_getPuckmanLocation().y,
            puckmanRect.w = PKM_MAIN_CHAR_WIDTH;  // 32px
            puckmanRect.h = PKM_MAIN_CHAR_HEIGHT; // 32px

            displayWindow();
            // clear the renderer
            SDL_RenderClear(_mainRenderer);
            drawGrid();

            puckman_alive_animate(_mainRenderer, &puckmanRect);

            SDL_RenderPresent(_mainRenderer);
            lastTick = SDL_GetTicks();

            while (quit_flag == false)
            {
                nextTick = SDL_GetTicks();
                diffTick = nextTick - lastTick;

                // TODO
                // A redesign of the animation sequence needs to be done
                // the speed of both the waka and the movement has to be brought down
                // so better to test both movement and waka speed to see if it hits
                // if so then go into the clear screen and figure out if this is a
                // waka or a move
                //
                // there is a possibility that the waka maybe slower than the move

                if (diffTick >= PKM_MAIN_FPS) // going into FPS
                {
                    // animate
                    SDL_RenderClear(_mainRenderer); // clear the screen
                    drawGrid();                     // draw the grid for now

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

                    if (gameFrameCount == PKM_MAIN_GAME_FRAME_COUNT)
                    {
                        // update the game first
                        pkm_game_movePuckman(); // move puckman by the number of pixel
                        puckmanRect.x = pkm_game_getPuckmanLocation().x;
                        puckmanRect.y = pkm_game_getPuckmanLocation().y,
                        puckmanRect.w = PKM_MAIN_CHAR_WIDTH;  // 32px
                        puckmanRect.h = PKM_MAIN_CHAR_HEIGHT; // 32px

                        // SDL_Log("PuckmanRect.x is %d", puckmanRect.x);
                        // SDL_Log("PuckmanRect.y is %d", puckmanRect.y);

                        gameFrameCount = 0; // reset the game frame count
                    }
                    else
                    {
                        gameFrameCount++;
                    }
                    puckman_alive_animate2(_mainRenderer, wakaRefresh, &puckmanRect);
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
                            // NOTE:
                            // we let the pckman_game determine if it is possible to set a direction
                            // so it checks for correctness or collision etc.
                            // then we pass the result to pckman_puckman to render
                            pkm_game_setPuckmanDirection(PUCKMAN_DIRECTION_LEFT);
                            puckman_setDirection(pkm_game_getPuckmanDirection());
                            puckman_setHealthStatus(pkm_game_getPuckmanHealthStatus());
                            puckman_setAliveStatus(pkm_game_getPuckmanAliveStatus());
                        }
                        else if ((keycode == SDLK_d) || (keycode == SDLK_RIGHT))
                        {
                            SDL_Log("Puckman direction RIGHT <-");
                            pkm_game_setPuckmanDirection(PUCKMAN_DIRECTION_RIGHT);
                            puckman_setDirection(pkm_game_getPuckmanDirection());
                            puckman_setHealthStatus(pkm_game_getPuckmanHealthStatus());
                            puckman_setAliveStatus(pkm_game_getPuckmanAliveStatus());
                        }
                        else if ((keycode == SDLK_w) || (keycode == SDLK_UP))
                        {
                            SDL_Log("Puckman direction UP ^");
                            pkm_game_setPuckmanDirection(PUCKMAN_DIRECTION_UP);
                            puckman_setDirection(pkm_game_getPuckmanDirection());
                            puckman_setHealthStatus(pkm_game_getPuckmanHealthStatus());
                            puckman_setAliveStatus(pkm_game_getPuckmanAliveStatus());
                        }
                        else if ((keycode == SDLK_s) || (keycode == SDLK_DOWN))
                        {
                            SDL_Log("Puckman direction DOWN v");
                            pkm_game_setPuckmanDirection(PUCKMAN_DIRECTION_DOWN);
                            puckman_setDirection(pkm_game_getPuckmanDirection());
                            puckman_setHealthStatus(pkm_game_getPuckmanHealthStatus());
                            puckman_setAliveStatus(pkm_game_getPuckmanAliveStatus());
                        }
                    }
                }
            }

            unloadAssets();
        }
    }
    else
    {
        printf("ERORR in initialisation\n");
    }

    quitGame();

    return 0;
}