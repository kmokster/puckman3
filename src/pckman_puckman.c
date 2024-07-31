#include "pckman_puckman.h"

const int _puckmanState = PUCKMAN_ALIVE;
const SDL_Texture *_puckmanAliveTexture;
const SDL_Texture *_puckmanDeadTexture;

extern int puckman_loadAsset(const SDL_Renderer *renderer)
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

extern void puckman_freeAsset()
{
    if (_puckmanAliveTexture != NULL)
        SDL_DestroyTexture(_puckmanAliveTexture);

    if (_puckmanDeadTexture != NULL)
        SDL_DestroyTexture(_puckmanDeadTexture);
}