/**
 * @file pckman_utils.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-08-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "pckman_utils.h"
#include "pckman_error.h"

/// @brief given a file name, checks if the file exists
/// @param filename - the full file name
/// @return true if it exists, false if not
extern bool pkm_util_isFileExists(char *filename)
{
    bool exists = false;
    FILE *file;

    file = fopen(filename, "r");

    if (file != NULL)
    {
        exists = true;
        fclose(file);
    }

    return exists;
}

/// @brief
/// @param filename - the bmp file name
/// @param renderer - the renderer created by the window
/// @param colorkey - the transparent color key
/// @param texture - returns the texture
/// @return 0 if successful, otherwise a error code (see pckman_error.h)
extern int pkm_utils_loadTextureWithColorKey(const char *filename, const SDL_Renderer *renderer, const Uint32 colorkey, SDL_Texture **texture)
{
    int error_code = 0;
    SDL_Surface *surface = NULL;

    if (renderer == NULL)
    {
        error_code = PKM_ERROR_UTL_LOADTEXTCOLORKEY_RENDERERISNULL;
        goto error;
    }

    // check if the file image exists
    if (!pkm_util_isFileExists(filename))
    {
        error_code = PKM_ERROR_UTL_LOADTEXTCOLORKEY_FILENOTFOUND;
        goto error;
    }

    surface = SDL_LoadBMP(filename); // puckman alive bmp file.

    if (surface == NULL)
    {
        error_code = PKM_ERROR_UTL_LOADTEXTCOLORKEY_UNABLE2LOADSURFACE;
        goto error;
    }

    // set the color key
    error_code = SDL_SetColorKey(surface, SDL_TRUE, colorkey);

    if (error_code != 0)
    {
        error_code = PKM_ERROR_UTL_LAODTEXTCOLORKEY_SETCOLORKEYERROR;
        goto error;
    }

    *texture = SDL_CreateTextureFromSurface(renderer, surface); // deep copy
    SDL_FreeSurface(surface);                                   // free the surface

    if (texture == NULL)
    {
        error_code = PKM_ERROR_UTL_LOADTEXTCOLORKEY_UNABLE2CREATETEXTURE;
        goto error;
    }

    // everything is successful going to end
    SDL_Log("pckman_utils loadTextureWithColorKey is successfully called");
    goto end;

error:
    return error_code;

end:
    return 0;
}
