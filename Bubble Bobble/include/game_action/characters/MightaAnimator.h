#ifndef MIGHTAANIMATOR_H
#define MIGHTAANIMATOR_H

#include "FrameRangeAnimator.h"
#include "MovingPathAnimator.h"
#include "Sprite.h"


class MightaStandAnimator : public FrameRangeAnimator, public Sprite::SpriteStartFallingListener{
	public:
		MightaStandAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return mightaStandAnimator_t; }

		void OnStartFalling(Sprite * sprite);
		static void OnFinishCallback(Animator*, void*);
};


class MightaWalkingAnimator : public FrameRangeAnimator, public Sprite::SpriteStartFallingListener{

	public:
		MightaWalkingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return mightaWalkAnimator_t; }

		static void OnFinishCallback(Animator*, void*);
		void OnStartFalling(Sprite * sprite);
};

class MightaFallingAnimator : public FrameRangeAnimator, public Sprite::SpriteStopFallingListener{

	public:
		MightaFallingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return mightaFallingAnimator_t; }

		void OnStopFalling(Sprite * sprite);
};

class MightaJumpAnimator : public MovingPathAnimator{
};

#endif
