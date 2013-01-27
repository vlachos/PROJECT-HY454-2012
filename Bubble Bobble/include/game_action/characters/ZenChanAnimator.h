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

#endif