#ifndef _PCKMAN_AUDIO_H
#define _PCKMAN_AUDIO_H

#define PKM_AUDIO_CREDIT_WAV "./res/audio/credit.wav"
#define PKM_AUDIO_SIREN0_WAV "./res/audio/siren0.wav"

extern int pkm_audio_init();
extern int pkm_audio_load();
extern int pkm_audio_playBackgroundMusic();
extern int pkm_audio_haltBackgroundMusic();
extern void pkm_audio_unload();

#endif