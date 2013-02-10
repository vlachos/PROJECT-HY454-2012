#ifndef SOUNDAPI_H
#define SOUNDAPI_H

#include <vector>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

class SoundAPI{
	public:
		typedef enum _soundKinds{
			soundKind_amigaCredits_t,
			soundKind_ecranTitre_t,
			soundKind_theStoryBegin_t,
			soundKind_ingameMusic_t,
			soundKind_booAppears_t,
			soundKind_ingameMusicHurryUp_t,
			soundKind_allLettersExtend_t,
			soundKind_extendBonusLife_t,
			soundKind_gameOver_t,
			soundKind_enterYourInitials_t
		}soundKinds;
		
		static void				SingletonCreate (const char * path) 
				{ singletonPtr = new SoundAPI(path); }
		static void				SingletonDestroy (void) 
				{ delete singletonPtr; singletonPtr = 0; }
		
		static  bool PlaySoundOnce(soundKinds kind, bool stopPrev);
		static  bool PlaySoundContinue(soundKinds kind, bool stopPrev);

	private:
		static SoundAPI*					singletonPtr;
		static std::string					SoundsFilePath;
		static std::vector<ALLEGRO_SAMPLE*> sounds;
		static ALLEGRO_SAMPLE_ID			spl_id;

		struct DeleteAttribute{
			void operator()(ALLEGRO_SAMPLE* sample){
				al_destroy_sample(sample);
			}
		};

		SoundAPI(const char * path);
		~SoundAPI(void);
};

#endif