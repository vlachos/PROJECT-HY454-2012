#ifndef STARTSCREENANIMATOR_H
#define STARTSCREENANIMATOR_H

#include "FrameRangeAnimator.h"
#include "MovingAnimator.h"

#define START_SCREEN_SELECTOR_START_GAME 210
#define START_SCREEN_SELECTOR_OPTIONS 230
#define START_SCREEN_SELECTOR_EXIT 250
#define START_SCREEN_SELECTOR_OFFSET 20

namespace StartScreenAnimatorActions{
	extern void CleanUpStartScreen();
	extern void StartStartScreen();
	extern void StartGame();
}

class StartScreenStaticAnimator : public MovingAnimator{
	public:
		StartScreenStaticAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return startScreenStaticAnimator_t; }
};

class StartScreenSelectorAnimator : public FrameRangeAnimator{
	public:
		StartScreenSelectorAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return startScreenSelectorAnimator_t; }

		void GoUp();
		void GoDown();
		bool PressEnter();
};

#endif