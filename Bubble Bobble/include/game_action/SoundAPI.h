#ifndef SOUNDAPI_H
#define SOUNDAPI_H

#include <vector>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

class SoundAPI{
	public:
		typedef enum _soundKinds{
			amigaCredits_t,
			ecranTitre_t,
			theStoryBegin_t,
			ingameMusic_t,
			booAppears_t,
			ingameMusicHurryUp_t,
			allLettersExtend_t,
			extendBonusLife_t,
			gameOver_t,
			enterYourInitials_t
		}soundKinds;
		
		static void				SingletonCreate (const char * path) 
				{ singletonPtr = new SoundAPI(path); }
		static void				SingletonDestroy (void) 
				{ delete singletonPtr; singletonPtr = 0; }
		
		static  bool PlaySoundOnce(soundKinds kind);
		static  bool PlaySoundContinue(soundKinds kind);

	private:
		static SoundAPI*					singletonPtr;
		static std::string					SoundsFilePath;
		static std::vector<ALLEGRO_SAMPLE*> sounds;

		struct DeleteAttribute{
			void operator()(ALLEGRO_SAMPLE* sample){
				al_destroy_sample(sample);
			}
		};

		SoundAPI(const char * path);
		~SoundAPI(void);
};

#endif