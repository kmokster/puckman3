#ifndef _PCKMAN_UTILS_H
#define _PCKMAN_UTILS_H

#include <stdbool.h>
#include <SDL.h>
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////////////////
//
// Placeholder for all utility base functions
//
///////////////////////////////////////////////////////////////////////////////////////////

extern bool pkm_util_isFileExists(char *filename);
extern int pkm_utils_loadTextureWithColorKey(const char *filename, const SDL_Renderer *renderer, const Uint32 colorkey, SDL_Texture **texture);

#endif