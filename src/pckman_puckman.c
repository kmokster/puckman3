/**
 * @file pckman_puckman.c
 * @author kmokster
 * @brief
 *
 * contains all functions that animates the puckman character
 * it never tracks the logic of puckman
 * just pure graphical animation
 *
 * @version 0.1
 * @date 2024-08-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdbool.h>

#include "pckman_game.h"
#include "pckman_puckman.h"
#include "pckman_state.h"

const SDL_Texture *_puckmanAliveTexture;
const SDL_Texture *_puckmanDeadTexture;

// TODO: to remove the following since we are now taking all the states from the game
int _puckmanHealthState = PUCKMAN_ALIVE;
int _puckmanAliveState = PUCKMAN_ALIVE_START;
int _puckmanDirection = PUCKMAN_DIRECTION_NONE;

int _puckmanWakaCount = 0;
int _puckmanDeadCount = 0;
bool _puckmanDirectionIsChanged = false;

extern int puckman_load_sprite(const SDL_Renderer *renderer)
{
    int error_code = 0;
    SDL_Surface *pmanAliveSurface = NULL;
    SDL_Surface *pmanDeadSurface = NULL;

    if (renderer != NULL)
    {
        pmanAliveSurface = SDL_LoadBMP(PKM_PUCKMAN_WAKA_BMP);
        if (pmanAliveSurface != NULL)
        {
            // set the color key
            SDL_SetColorKey(pmanAliveSurface, SDL_TRUE, 0x00FFFF);
            _puckmanAliveTexture = SDL_CreateTextureFromSurface(renderer, pmanAliveSurface);
            SDL_FreeSurface(pmanAliveSurface);

            if (_puckmanAliveTexture == NULL)
            {
                error_code = 2002;
                goto end;
            }
        }
        else
        {
            error_code = 2001;
            goto end;
        }

        pmanDeadSurface = SDL_LoadBMP(PKM_PUCKMAN_DIE_BMP);
        if (pmanDeadSurface != NULL)
        {
            // set the color key
            SDL_SetColorKey(pmanDeadSurface, SDL_TRUE, 0x00FFFF);
            _puckmanDeadTexture = SDL_CreateTextureFromSurface(renderer, pmanDeadSurface);
            SDL_FreeSurface(pmanDeadSurface);

            if (_puckmanDeadTexture == NULL)
            {
                error_code = 2003;
                goto end;
            }
        }
        else
        {
            error_code = 2004;
            goto end;
        }
    }

end:
    if (error_code != 0)
        SDL_Log("PUCKMAN LOAD ASSET ERROR = %d", error_code);
    return error_code;
}

extern void puckman_free_sprite()
{
    if (_puckmanAliveTexture != NULL)
        SDL_DestroyTexture(_puckmanAliveTexture);

    if (_puckmanDeadTexture != NULL)
        SDL_DestroyTexture(_puckmanDeadTexture);
}

extern void puckman_setHealthStatus(int status)
{
    _puckmanHealthState = status;
}

extern void puckman_setAliveStatus(int status)
{
    _puckmanAliveState = status;
}

// extern int puckman_alive_animate(const SDL_Renderer *renderer, const SDL_Rect *pos2Render)
// {
//     int error_code;
//     SDL_Rect sourceRect = {0,
//                            0,
//                            0,
//                            0};

//     if (renderer == NULL)
//     {
//         error_code = 2005;
//         goto end;
//     }
//     else
//     {
//         // render the current state of puckman to the pos2Render

//         // TODO: check the current state of Puckman (Alive or Dead?)

//         // for now we just render the first sprite sequence alive puckman
//         sourceRect.x = (_puckmanWakaCount * PKM_PUCKMAN_WIDTH);
//         sourceRect.y = (_puckmanDirection * PKM_PUCKMAN_HEIGHT);
//         sourceRect.w = PKM_PUCKMAN_WIDTH;
//         sourceRect.h = PKM_PUCKMAN_HEIGHT;

//         SDL_Log("puckman_alive_animate pos2Render.x = %d", pos2Render->x);
//         SDL_Log("puckman_alive_animate pos2Render.y = %d", pos2Render->y);

//         error_code = SDL_RenderCopy(renderer, _puckmanAliveTexture, &sourceRect, pos2Render);

//         // update the sequence
//         switch (_puckmanWakaCount)
//         {
//         case PUCKMAN_FULL:
//             _puckmanWakaCount++; // update the next animation to mouth open
//             break;
//         case PUCKMAN_OPEN:
//             _puckmanWakaCount++; // update the next animation to mouth wide
//             break;
//         case PUCKMAN_WIDE:
//             _puckmanWakaCount++; // update the next animation to mouth closing
//             break;
//         case PUCKMAN_CLOSE:
//             _puckmanWakaCount = 0; // update the next animation to fully closed
//             break;
//         default:
//             break;
//         }
//     }

// end:
//     return error_code;
// }

extern int puckman_alive_animate2(const SDL_Renderer *renderer, bool nextFrame, const SDL_Rect *pos2Render)
{
    int error_code;
    SDL_Rect sourceRect = {0,
                           0,
                           0,
                           0};

    if (renderer == NULL)
    {
        error_code = 2005;
        goto end;
    }
    else
    {
        // render the current state of puckman to the pos2Render

        // TODO: check the current state of Puckman (Alive or Dead?)

        // when puckman is alive and is moving
        if (pkm_game_getPuckmanHealthStatus() == PUCKMAN_ALIVE)
        {
            if (pkm_game_getPuckmanAliveStatus() == PUCKMAN_ALIVE_START) // the game has just started
            {
                // map it to the first frame in the puckman sprite
                sourceRect.x = 0;
                sourceRect.y = 0;
                sourceRect.w = PKM_PUCKMAN_WIDTH;
                sourceRect.h = PKM_PUCKMAN_HEIGHT;

                error_code = SDL_RenderCopy(renderer, _puckmanAliveTexture, &sourceRect, pos2Render);
            }
            else if (pkm_game_getPuckmanAliveStatus() == PUCKMAN_ALIVE_MOVING)
            {
                sourceRect.x = (_puckmanWakaCount * PKM_PUCKMAN_WIDTH);
                sourceRect.y = (_puckmanDirection * PKM_PUCKMAN_HEIGHT);
                sourceRect.w = PKM_PUCKMAN_WIDTH;
                sourceRect.h = PKM_PUCKMAN_HEIGHT;

                error_code = SDL_RenderCopy(renderer, _puckmanAliveTexture, &sourceRect, pos2Render);

                if (nextFrame)
                { // update the sequence
                    switch (_puckmanWakaCount)
                    {
                    case PUCKMAN_FULL:
                        _puckmanWakaCount++; // update the next animation to mouth open
                        break;
                    case PUCKMAN_OPEN:
                        _puckmanWakaCount++; // update the next animation to mouth wide
                        break;
                    case PUCKMAN_WIDE:
                        _puckmanWakaCount++; // update the next animation to mouth closing
                        break;
                    case PUCKMAN_CLOSE:
                        _puckmanWakaCount = 0; // update the next animation to fully closed
                        break;
                    default:
                        break;
                    }
                }
            }
            else if ((pkm_game_getPuckmanAliveStatus() == PUCKMAN_ALIVE_STOP))
            {
                // map it to the first frame in the puckman sprite

                // TODO: get this working!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                sourceRect.x = 16;
                sourceRect.y = pkm_game_getPuckmanDirection() * PKM_MAIN_CELL_HEIGHT;
                sourceRect.w = PKM_PUCKMAN_WIDTH;
                sourceRect.h = PKM_PUCKMAN_HEIGHT;

                error_code = SDL_RenderCopy(renderer, _puckmanAliveTexture, &sourceRect, pos2Render);
            }
        }
    }

end:
    return error_code;
}

// TEMPORARY FUNCTIONS JUST TO TEST THE PASSING OF
// STATES between thegame logic and puckman graphic functions

extern void puckman_setDirection(int direction)
{
    switch (direction)
    {
    case PUCKMAN_DIRECTION_LEFT:
        puckman_setDirectionLeft();
        return;
    case PUCKMAN_DIRECTION_RIGHT:
        puckman_setDirectionRight();
        return;
    case PUCKMAN_DIRECTION_UP:
        puckman_setDirectionUp();
        return;
    case PUCKMAN_DIRECTION_DOWN:
        puckman_setDirectionDown();
        return;
    default:
        return;
    }
}

extern void puckman_setDirectionRight()
{
    _puckmanDirection = PUCKMAN_DIRECTION_RIGHT;
}

extern void puckman_setDirectionLeft()
{
    _puckmanDirection = PUCKMAN_DIRECTION_LEFT;
}

extern void puckman_setDirectionUp()
{
    _puckmanDirection = PUCKMAN_DIRECTION_UP;
}

extern void puckman_setDirectionDown()
{
    _puckmanDirection = PUCKMAN_DIRECTION_DOWN;
}