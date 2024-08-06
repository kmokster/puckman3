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

#include "pckman_puckman.h"
#include "pckman_state.h"

const SDL_Texture *_puckmanAliveTexture;
const SDL_Texture *_puckmanDeadTexture;

// int _puckmanState = PUCKMAN_ALIVE;
int _puckmanWakaCount = 0;
int _puckmanDeadCount = 0;
int _puckmanDirection = PUCKMAN_RIGHT;
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

extern int puckman_alive_animate(const SDL_Renderer *renderer, const SDL_Rect *pos2Render)
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

        // for now we just render the first sprite sequence alive puckman
        sourceRect.x = (_puckmanWakaCount * PKM_PUCKMAN_WIDTH);
        sourceRect.y = (_puckmanDirection * PKM_PUCKMAN_HEIGHT);
        sourceRect.w = PKM_PUCKMAN_WIDTH;
        sourceRect.h = PKM_PUCKMAN_HEIGHT;

        error_code = SDL_RenderCopy(renderer, _puckmanAliveTexture, &sourceRect, pos2Render);

        // update the sequence
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

end:
    return error_code;
}

extern void puckman_setDirectionRight()
{
    _puckmanDirection = PUCKMAN_RIGHT;
}

extern void puckman_setDirectionLeft()
{
    _puckmanDirection = PUCKMAN_LEFT;
}

extern void puckman_setDirectionUp()
{
    _puckmanDirection = PUCKMAN_UP;
}

extern void puckman_setDirectionDown()
{
    _puckmanDirection = PUCKMAN_DOWN;
}