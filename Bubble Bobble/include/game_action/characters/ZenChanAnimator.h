#ifndef ZENCHANANIMATOR_H
#define ZENCHANANIMATOR_H

#include "MovingAnimator.h"
#include "FrameRangeAnimator.h"
#include "MovingPathAnimator.h"
#include "Sprite.h"


class ZenChanStandAnimator : public FrameRangeAnimator, public Sprite::SpriteStartFallingListener{
	public:
		ZenChanStandAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanStandAnimator_t; }

		void OnStartFalling(Sprite * sprite);
		static void OnFinishCallback(Animator*, void*);
};


class ZenChanWalkingAnimator : public FrameRangeAnimator, public Sprite::SpriteStartFallingListener{

	public:
		ZenChanWalkingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanWalkAnimator_t; }

		static void OnFinishCallback(Animator*, void*);
		void OnStartFalling(Sprite * sprite);
};

class ZenChanFallingAnimator : public FrameRangeAnimator, public Sprite::SpriteStopFallingListener{

	public:
		ZenChanFallingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanFallingAnimator_t; }

		void OnStopFalling(Sprite * sprite);
};

class ZenChanJumpAnimator : public MovingPathAnimator{
};

#endif
