#ifndef BARONVONBLUBAANIMATOR_H
#define BARONVONBLUBAANIMATOR_H

#include "FrameRangeAnimator.h"
#include "MovingPathAnimator.h"
#include "Sprite.h"


class BaronVonBlubaStandAnimator : public FrameRangeAnimator, public Sprite::SpriteStartFallingListener{
	public:
		BaronVonBlubaStandAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return baronVonBlubaStandAnimator_t; }

		void OnStartFalling(Sprite * sprite);
		static void OnFinishCallback(Animator*, void*);
};


#endif
