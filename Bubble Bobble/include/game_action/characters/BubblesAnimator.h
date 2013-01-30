#ifndef BUBBLESANIMATOR_H
#define BUBBLESANIMATOR_H

#include "FrameRangeAnimator.h"
#include "MovingPathAnimator.h"

class BubBubbleBlastOffAnimator: public FrameRangeAnimator{
	public:
		BubBubbleBlastOffAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubBubbleBlastOffAnimator_t; }

		static void OnFinishCallback(Animator*, void*);
};

class BubBubbleAnimator: public MovingPathAnimator{
	public:
		BubBubbleAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubBubbleAnimator_t; }

		static void OnCollisionWithBubFalling(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubJump(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubble(Sprite *, Sprite *, void *);
		static void OnFinishCallback(Animator*, void*);
};

#endif