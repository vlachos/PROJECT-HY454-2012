#ifndef BUBBLEMAIN_H
#define BUBBLEMAIN_H

#include <stdio.h>
#include <windows.h>
#include "PathNames.h"
#include "utilities.h"
#include "MemoryManage.h"
#include "InputManage.h"

#include "BubbleLogic.h"

#include "Terrain.h"
#include "FrameRangeAnimation.h"
#include "AnimationFilmHolder.h"
#include "AnimationFilm.h"
#include "FrameRangeAnimator.h"
#include "AnimatorHolder.h"
#include "InvisibleSprites.h"
#include "TickAnimation.h"

#include "GameActionUtilities.h"
#include "AnimationsParser.h"
#include "CollisionChecker.h"
#include "BubAnimator.h"
#include "BubblesAnimator.h"
#include "ZenChanAnimator.h"
#include "MightaAnimator.h"
#include "BarronVonBlubaAnimator.h"
#include "TimerTickAnimator.h"

#include "ArtificialIntelligence.h"
#include "PowerUpsAnimator.h"

#include <allegro5\allegro5.h> 
#include <allegro5\allegro_native_dialog.h> 
#include <allegro5\allegro_image.h>

Display display = NULL;
Bitmap palette = NULL;
EventQueue event_queue = NULL;
Timer timer = NULL;

ALLEGRO_EVENT ev;
KeyBoardState keyState;

const float FPS = 60;
bool redraw = true;

namespace BubbleMain{

	extern int DrawTerrain(void);

	extern bool InitAllegro(void);
	extern void InitGameEngine(void);

	extern void InitSprites(void);
	extern void InitBubblun(void);
	extern void InitZenChan(void);
	extern void InitMighta(void);

	extern void ManageGameLoop(void);

	extern void Rendering(void);
	extern bool InputManagement(void);
	extern void AnimationProgress(timestamp_t timeNow);
	extern void ArtificialIntelligence(void);
	extern void CollisionChecking(void);
	extern void CommitDestructions(void);
	extern void FPSCalculation(void);
	extern void SystemLoopDispatching(void);
	extern void GameOver(void);
	
}

#endif