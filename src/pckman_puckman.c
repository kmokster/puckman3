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
#include <stdio.h>

#include "pckman_game.h"
#include "pckman_puckman.h"
#include "pckman_state.h"
#include "pckman_error.h"
#include "pckman_utils.h"

const SDL_Texture *_puckmanAliveTexture;
const SDL_Texture *_puckmanDeadTexture;

// arrays to store the points to the top most corner of each frame
SDL_Point _puckmanAlivePoints[PKM_PUCKMAN_WAKA_SPRITE_X_FRAME][PKM_PUCKMAN_WAKA_SPRITE_Y_FRAME]; // 4 x 4 array to store the top left co-ordinate of sprite
SDL_Point _puckmanDeadPoints[PKM_PUCKMAN_DIE_SPRITE_X_FRAME];

// TODO: to remove the following since we are now taking all the states from the game structure
int _puckmanHealthState = PUCKMAN_ALIVE;
int _puckmanAliveState = PUCKMAN_ALIVE_START;
int _puckmanDirection = PUCKMAN_DIRECTION_NONE;
bool _puckmanDirectionIsChanged = false;

int _puckmanWakaCount = 0;
int _puckmanDeadCount = 0;

/// @brief Load the x and y co-ordinates in SDL_Point
/// structure to the top left of each animation frame
void puckman_load_texturePoints()
{
    // load the points that points to each frame for the waka sprite
    for (int y = 0; y < PKM_PUCKMAN_WAKA_SPRITE_X_FRAME; y++)
    {
        for (int x = 0; x < PKM_PUCKMAN_WAKA_SPRITE_Y_FRAME; x++)
        {
            SDL_Point alivePoint;
            alivePoint.x = x * PKM_PUCKMAN_WIDTH;
            alivePoint.y = y * PKM_PUCKMAN_HEIGHT;
            _puckmanAlivePoints[x][y] = alivePoint;
        }
    }

    // load the points that points to each frame for the dying sprite
    for (int x = 0; x < PKM_PUCKMAN_DIE_SPRITE_X_FRAME; x++)
    {
        SDL_Point deadPoint;
        deadPoint.x = x;
        deadPoint.y = 0; // this is zero but we do this anyway
        _puckmanDeadPoints[x] = deadPoint;
    }
}

/// @brief this function loads the puckman sprite
/// @param renderer
/// @return 0 if no error or non-zero for error
extern int puckman_load_sprite(const SDL_Renderer *renderer)
{
    int error_code = 0;
    SDL_Surface *pmanAliveSurface = NULL; // pointer to the puckman alive sprite
    SDL_Surface *pmanDeadSurface = NULL;  // pointer to the puckman dead sprite

    // load the puckman waka animation sprite
    error_code = pkm_utils_loadTextureWithColorKey(PKM_PUCKMAN_WAKA_BMP,
                                                   renderer,
                                                   PKM_PUCKMAN_TRANSPARENT_COLOR,
                                                   &_puckmanAliveTexture);
    if (error_code != 0)
    {
        goto error;
    }

    // now load the puckman dying animation sprite
    error_code = pkm_utils_loadTextureWithColorKey(PKM_PUCKMAN_DIE_BMP,
                                                   renderer,
                                                   PKM_PUCKMAN_TRANSPARENT_COLOR,
                                                   &_puckmanDeadTexture);

    if (error_code != 0)
    {
        goto error;
    }

    // TODO: pre-calculate the SDL_Points to each animation frame and
    // store them in a array
    puckman_load_texturePoints();

    goto end;

error:
    SDL_Log("puckman::loadsprite ERROR: %d", error_code);
    return error_code;

end:
    return error_code;
}

/// @brief Call this function to free the texture held
extern void puckman_free_sprite()
{
    if (_puckmanAliveTexture != NULL)
    {
        SDL_DestroyTexture(_puckmanAliveTexture);
        _puckmanAliveTexture = NULL;
    }

    if (_puckmanDeadTexture != NULL)
    {
        SDL_DestroyTexture(_puckmanDeadTexture);
        _puckmanDeadTexture = NULL;
    }
}

extern int puckman_alive_animate(const SDL_Renderer *renderer, bool wakaNextFrame)
{
    int error_code = 0;
    SDL_Rect sourceRect = {0,
                           0,
                           0,
                           0};

    SDL_Rect destinationRect = {
        pkm_game_getPuckmanLocation().x,
        pkm_game_getPuckmanLocation().y,
        PKM_MAIN_CHAR_WIDTH,
        PKM_MAIN_CHAR_HEIGHT};

    if (renderer == NULL)
    {
        error_code = PKM_ERROR_PUCKMAN_ANIMATE_RENDNULL;
        goto end;
    }

    // render the current state of puckman to the pos2Render

    // TODO: check the current state of Puckman (Alive or Dead?)
    // when puckman is alive and is moving
    if (pkm_game_getPuckmanHealthStatus() == PUCKMAN_ALIVE)
    {
        if (pkm_game_getPuckmanAliveStatus() == PUCKMAN_ALIVE_START) // the game has just started
        {
            // map it to the first frame in the puckman sprite
            sourceRect.x = _puckmanAlivePoints[0][0].x;
            sourceRect.y = _puckmanAlivePoints[0][0].y;
            sourceRect.w = PKM_PUCKMAN_WIDTH;
            sourceRect.h = PKM_PUCKMAN_HEIGHT;

            error_code = SDL_RenderCopy(renderer, _puckmanAliveTexture, &sourceRect, &destinationRect);
        }
        else if (pkm_game_getPuckmanAliveStatus() == PUCKMAN_ALIVE_MOVING)
        {
            sourceRect.x = (_puckmanWakaCount * PKM_PUCKMAN_WIDTH);
            sourceRect.y = (pkm_game_getPuckmanDirection() * PKM_PUCKMAN_HEIGHT);
            sourceRect.w = PKM_PUCKMAN_WIDTH;
            sourceRect.h = PKM_PUCKMAN_HEIGHT;

            error_code = SDL_RenderCopy(renderer, _puckmanAliveTexture, &sourceRect, &destinationRect);

            if (wakaNextFrame)
            { // update the sequence
                switch (_puckmanWakaCount)
                {
                case PUCKMAN_WAKA_FULL:
                    _puckmanWakaCount++; // update the next animation to mouth open
                    break;
                case PUCKMAN_WAKA_OPEN:
                    _puckmanWakaCount++; // update the next animation to mouth wide
                    break;
                case PUCKMAN_WAKA_WIDE:
                    _puckmanWakaCount++; // update the next animation to mouth closing
                    break;
                case PUCKMAN_WAKA_CLOSING:
                    _puckmanWakaCount = 0; // update the next animation to fully closed
                    break;
                default:
                    break;
                }
            }
        }
        else if ((pkm_game_getPuckmanAliveStatus() == PUCKMAN_ALIVE_STOP))
        {
            sourceRect.x = _puckmanAlivePoints[PUCKMAN_WAKA_OPEN][pkm_game_getPuckmanDirection()].x;
            sourceRect.y = _puckmanAlivePoints[PUCKMAN_WAKA_OPEN][pkm_game_getPuckmanDirection()].y;
            sourceRect.w = PKM_PUCKMAN_WIDTH;
            sourceRect.h = PKM_PUCKMAN_HEIGHT;
            error_code = SDL_RenderCopy(renderer, _puckmanAliveTexture, &sourceRect, &destinationRect);
        }
    }

    if (error_code == 0)
    {
        goto end;
    }

error:
    return error_code;

end:
    return 0;
}