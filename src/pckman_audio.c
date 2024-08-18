
#include <SDL_audio.h>
#include <SDL_mixer.h>
#include <SDL.h>
#include "pckman_utils.h"
#include "pckman_error.h"
#include "pckman_audio.h"

Mix_Music *_bgSirenMusic = NULL;

extern int pkm_audio_init()
{
    int error_code = 0;

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        error_code = PKM_ERROR_AUDIO_INIT_MIXER;
        goto error;
    }
    goto end;

error:
    SDL_Log("PKM_AUDIO_INIT crashing here!!");
    return error_code;

end:
    return 0;
}

extern int pkm_audio_load()
{
    int error_code = 0;

    _bgSirenMusic = Mix_LoadMUS(PKM_AUDIO_SIREN0_WAV);
    if (_bgSirenMusic == NULL)
    {
        error_code = PKM_ERROR_AUDIO_LOAD_MUSIC;
        goto error;
    }

    goto end;

error:
    SDL_Log("PKM_AUDIO_LOAD crashing here!!");
    return error_code;

end:
    return 0;
}

extern int pkm_audio_playBackgroundMusic()
{
    int error_code = 0;

    if (Mix_PlayMusic(_bgSirenMusic, -1) != 0)
    {
        error_code = PKM_ERROR_AUDIO_PLAY_MUSIC;
        SDL_Log("PKM_AUDIO_PLAYBGMUSIC crashing here!!");
    }

    return error_code;
}

extern int pkm_audio_haltBackgroundMusic()
{
    int error_code = 0;

    Mix_HaltMusic();

    return error_code;
}

extern void pkm_audio_unload()
{
    if (_bgSirenMusic != NULL)
    {
        Mix_FreeMusic(_bgSirenMusic);
        _bgSirenMusic = NULL;
    }
}
