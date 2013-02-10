#include "SoundAPI.h"
#include <algorithm>

#include "MemoryManage.h"
#include <string>
#include <iostream>

#define SOUNDAPI_FILENAMESIZE 10

SoundAPI*						SoundAPI::singletonPtr;
std::string						SoundAPI::SoundsFilePath;
std::vector<ALLEGRO_SAMPLE*>	SoundAPI::sounds;

namespace SoundAPIFileName{
	const char* soundAPI_FileName[] = {
		"bubble-bobble-01-amiga-credits.WAV",
		"bubble-bobble-02-ecran-titre.WAV",
		"bubble-bobble-03-the-story-begin.WAV",
		"bubble-bobble-04-ingame-music.WAV",
		"bubble-bobble-05-boo-appears.WAV",
		"bubble-bobble-06-ingame-music-hurry-up.WAV",
		"bubble-bobble-07-all-letters-e.x.t.e.n.d.WAV",
		"bubble-bobble-08-e.x.t.e.n.d-bonus-life.WAV",
		"bubble-bobble-10-game-over.WAV",
		"bubble-bobble-11-enter-your-initials.WAV"
	};
}

SoundAPI::SoundAPI(const char * path){
	SoundsFilePath = std::string(path);
	for(int i=0; i<SOUNDAPI_FILENAMESIZE; ++i){
		ALLEGRO_SAMPLE* sound = al_load_sample( (SoundsFilePath + "\\" + SoundAPIFileName::soundAPI_FileName[i]).c_str() );
		DASSERT(sound);
		sounds.push_back(sound);
	}
	al_reserve_samples(1);
}

SoundAPI::~SoundAPI(){
	std::for_each( 
					sounds.begin(), 
					sounds.end(), 
					DeleteAttribute() 
				);
	sounds.clear();
	SoundsFilePath.clear();
}

bool SoundAPI::PlaySoundOnce(soundKinds kind){
	return al_play_sample(sounds[ (unsigned int) kind ], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}

bool SoundAPI::PlaySoundContinue(soundKinds kind){
	return al_play_sample(sounds[ (unsigned int) kind ], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);
}