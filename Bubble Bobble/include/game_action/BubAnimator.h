#ifndef BUBANIMATOR_H
#define BUBANIMATOR_H

#include "FrameRangeAnimator.h"
#include "MovingAnimator.h"
#include "Sprite.h"

		
class BubStandAnimator : public MovingAnimator{
	public:
		BubStandAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return BubStandAnimator_t; }

		static void OnFinishCallback(Animator*, void*);
};

class BubWalkingAnimator : public FrameRangeAnimator, public Sprite::SpriteStartFallingListener{

	public:
		BubWalkingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubWalkAnimator_t; }

		static void OnFinishCallback(Animator*, void*);
		void OnStartFalling(Sprite * sprite);
};

class BubFallingAnimator : public MovingAnimator, public Sprite::SpriteStopFallingListener{

	public:
		BubFallingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubfallingAnimator_t; }

		void OnStopFalling(Sprite * sprite);
};


#endif