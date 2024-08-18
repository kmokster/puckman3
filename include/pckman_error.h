/**
 * @file pckman_error.h
 * @author Kevin Mok
 * @brief A header file of all error codes and messages
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

// Error code breakdown
// YXXXXXX - Game code
// XYYXXXX - module (e.g. 01 for main, 02 for game logic)
// XXXYYXX - the function
// XXXXXYY - the error in the function

/////////////////////////////////////////////////////////////////////////////////////////
// Errors pertaining to functions in the main execution loop
// Error_code format is: 1010XXYY (XX is the function, YY is the error in the function)
/////////////////////////////////////////////////////////////////////////////////////////

#define PKM_ERROR_MAIN_INIT_SDL_INIT 1010101 // SDL error when calling SDL_Init
#define PKM_ERROR_MAIN_INIT_SDL_DISP 1010102 // SDL error when calling SDL_GetCurrentDisplayMode
#define PKM_ERROR_MAIN_INIT_SDL_CWIN 1010103 // SDL error when calling SDL_CreateWindow
#define PKM_ERROR_MAIN_INIT_SDL_REND 1010104 // SDL error when calling SDL_CreateRenderer
#define PKM_ERROR_MAIN_INIT_SDL_TEXT 1010105 // SDL error when calling SDL_CreateTexture

#define PKM_ERROR_MAIN_STARTGAME_RENCLR 1010301 // SDL error when calling SDL_RenderClear

//////////////////////////////////////////////////////////////////////////////////////////
// Errors pertaining to functions in the audio file
// Error_code format is: 1030XXYY
//////////////////////////////////////////////////////////////////////////////////////////
#define PKM_ERROR_AUDIO_INIT_MIXER 1030101
#define PKM_ERROR_AUDIO_LOAD_MUSIC 1030102 // passing the main renderer as null
#define PKM_ERROR_AUDIO_PLAY_MUSIC 1030201

//////////////////////////////////////////////////////////////////////////////////////////
// Errors pertaining to functions in the puckman file
// Error_code format is: 1040XXYY
//////////////////////////////////////////////////////////////////////////////////////////
#define PKM_ERROR_PUCKMAN_LOAD_RNULL 1040101          // passing the main renderer as null
#define PKM_ERROR_PUCKMAN_LOAD_BMPNOTFOUND 1040102    // the bmp is not found
#define PKM_ERROR_PUCKMAN_ALIVESURFACE_NOLOAD 1040103 // error loading the alive bmp 2 surface
#define PKM_ERROR_PUCKMAN_COLORKEY_ERROR 1040104      // error loading the color key
#define PKM_ERROR_PUCKMAN_ALIVESURFACE_NOTEXT 1040105 // error creating the texture from surface
#define PKM_ERROR_PUCKMAN_DEAD_BMPNOTFOUND 1040106    // puckman dying bmp not found
#define PKM_ERORR_PUCKMAN_DEADSURACE_NOLOAD 1040107   // puckman dying bmp unable to load surface
#define PKM_ERROR_PUCKMAN_DEADSURFACE_NOTEXT 1040108  // puckman dying texture unable to create
#define PKM_ERROR_PUCKMAN_ANIMATE_RENDNULL 1040201    // renderer was pass null into animate

//////////////////////////////////////////////////////////////////////////////////////////
// Errors pertaining to functions in the utility file
// Error_code format is: 191XXYY
//////////////////////////////////////////////////////////////////////////////////////////
#define PKM_ERROR_UTL_LOADTEXTCOLORKEY_RENDERERISNULL 1910201
#define PKM_ERROR_UTL_LOADTEXTCOLORKEY_FILENOTFOUND 1910202
#define PKM_ERROR_UTL_LOADTEXTCOLORKEY_UNABLE2LOADSURFACE 1910203
#define PKM_ERROR_UTL_LAODTEXTCOLORKEY_SETCOLORKEYERROR 1910204
#define PKM_ERROR_UTL_LOADTEXTCOLORKEY_UNABLE2CREATETEXTURE 1910205