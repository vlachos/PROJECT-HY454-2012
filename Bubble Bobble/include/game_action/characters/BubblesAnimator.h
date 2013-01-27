#ifndef BUBBLESANIMATOR_H
#define BUBBLESANIMATOR_H

#include "FrameRangeAnimator.h"

class BubBubbleAnimator: public FrameRangeAnimator{
	public:
		BubBubbleAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubBubbleAnimator_t; }

		static void OnFinishCallback(Animator*, void*);
};

#endif