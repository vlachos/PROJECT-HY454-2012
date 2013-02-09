#ifndef OPTIONSSCRRENANIMATOR_H
#define OPTIONSSCREENANIMATOR_H

#include "FrameRangeAnimator.h"
#include "MovingAnimator.h"

namespace OptionsScreenAnimatorActions{
	extern void CleanUpOptionsScreen();
	extern void StartOptionsScreen();
}

class OptionsScreenStaticAnimator : public MovingAnimator{
	public:
		OptionsScreenStaticAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return optionsScreenStaticAnimator_t; }
};

class OptionsScreenSelectorAnimator : public FrameRangeAnimator{
	public:
		OptionsScreenSelectorAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return optionsScreenSelectorAnimator_t; }

		void GoUp();
		void GoDown();
		bool PressEnter();
};

#endif