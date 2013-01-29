#ifndef ZENCHANANIMATOR_H
#define ZENCHANANIMATOR_H

#include "FrameRangeAnimator.h"
#include "MovingAnimator.h"
#include "Sprite.h"


class ZenChanStandAnimator : public MovingAnimator, public Sprite::SpriteStartFallingListener{
	public:
		ZenChanStandAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanStandAnimator_t; }

		static void OnFinishCallback(Animator*, void*);
		void OnStartFalling(Sprite * sprite);
};

/*
class BubWalkingAnimator : public FrameRangeAnimator, public Sprite::SpriteStartFallingListener{

	public:
		BubWalkingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubWalkAnimator_t; }

		static void OnFinishCallback(Animator*, void*);
		static void OnCollisionWithEnemy(Sprite *, Sprite *, void *);
		void OnStartFalling(Sprite * sprite);
		void OnOpenMouth(void);
};

class BubFallingAnimator : public MovingAnimator, public Sprite::SpriteStopFallingListener{

	public:
		BubFallingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubFallingAnimator_t; }

		void OnStopFalling(Sprite * sprite);
};

class BubOpenMouthAnimator : public FrameRangeAnimator, public Sprite::SpriteStartFallingListener{
	public:
		BubOpenMouthAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubOpenMouthAnimator_t; }

		static void OnFinishCallback(Animator*, void*);
		void OnStartFalling(Sprite * sprite);
};

class BubJumpAnimator : public FrameRangeAnimator{
	public:
		BubJumpAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubJumpAnimator_t; }

		static void OnCollisionWithEnemy(Sprite *, Sprite *, void *);
		static void OnFinishCallback(Animator*, void*);


};
*/
#endif
