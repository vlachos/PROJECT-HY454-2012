#ifndef BUBBLEMAIN_H
#define BUBBLEMAIN_H

#include <stdio.h>
#include <windows.h>
#include "PathNames.h"
#include "utilities.h"
#include "MemoryManage.h"
#include "InputManage.h"

#include "Terrain.h"
#include "FrameRangeAnimation.h"
#include "AnimationFilmHolder.h"
#include "AnimationFilm.h"
#include "FrameRangeAnimator.h"
#include "AnimatorHolder.h"
#include "BubAnimator.h"
#include "ZenChanAnimator.h"
#include "AnimationsParser.h"
#include "CollisionChecker.h"
#include "MightaAnimator.h"
#include "BarronVonBlubaAnimator.h"

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

	extern int DrawTerrain();

	extern bool InitAllegro();
	extern void InitGameEngine();

	extern void ManageGameLoop();

	extern void Rendering();
	extern bool InputManagement();
	extern void AnimationProgress(timestamp_t timeNow);
	extern void ArtificialIntelligence();
	extern void CollisionChecking();
	extern void CommitDestructions();
	extern void FPSCalculation();
	extern void SystemLoopDispatching();
	extern void GameOver();
	
}

#endif