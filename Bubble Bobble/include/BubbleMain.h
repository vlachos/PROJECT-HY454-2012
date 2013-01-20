#ifndef BUBBLEMAIN_H
#define BUBBLEMAIN_H

#include <stdio.h>
#include <windows.h>
#include <PathNames.h>
#include "FrameRangeAnimation.h"
#include "AnimationFilmHolder.h"
#include "AnimationFilm.h"
#include "FrameRangeAnimator.h"
#include "AnimatorHolder.h"
#include "TileBitmap.h"
#include "TileLayer.h"
#include "utilities.h"
#include "EventCallbacks.h"
#include <allegro5\allegro5.h> 
#include <allegro5\allegro_native_dialog.h> 
#include <allegro5\allegro_image.h>

Display display = NULL;
Bitmap palette = NULL;
EventQueue event_queue = NULL;
Timer timer = NULL;
KeyBoardState keyState;

TileLayer *actionLayer;
AnimationFilmHolder* afh;

const float FPS = 60;
bool redraw = true;

namespace BubbleMain{

	extern int DrawTerrain();

	extern bool InitAllegro();
	extern TileLayer* InitTerrain();
	extern void InitGameEngine();

	extern void Rendering();
	extern void InputManagement();
	extern void AnimationProgress();
	extern void ArtificialIntelligence();
	extern void CollisionChecking();
	extern void CommitDestructions();
	extern void FPSCalculation();
	extern void SystemLoopDispatching();
	extern void GameOver();
	
}

#endif