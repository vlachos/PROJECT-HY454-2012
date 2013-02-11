#ifndef RIVERANIMATOR_H
#define RIVERANIMATOR_H

#include "RiverSprite.h"
#include "MovingAnimator.h"
#include "FrameRangeAnimator.h"

namespace RiverAnimatorActions{
	extern void StartRiverAnimator(int x, int y, bool goesLeft);
	extern void StartWaterBubble(void* args);
}

class RiverAnimator: public MovingAnimator, public Sprite::SpriteStopFallingListener, public Sprite::SpriteStartFallingListener {

	public:
		RiverAnimator();
		
		enum animatorType_t GetAnimatorType(void)
			{ return riverAnimator_t; }

		void RegistCollitions(RiverSprite*);

		static void OnFinishCallback(Animator*, void*);
		void OnStartFalling(Sprite*);
		void OnStopFalling(Sprite*);

		static void OnCollisionWithBub(Sprite*, Sprite*, void*);
		static void OnCollisionWithZenChan(Sprite*, Sprite*, void*);
		static void OnCollisionWithMighta(Sprite*, Sprite*, void*);
};

class WaterBubbleAnimator: public FrameRangeAnimator{
	public:
		WaterBubbleAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return waterSpecialBubble_t; }

		void RegistCollitions(Sprite*);
		static void OnCollisionWithBubFalling(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubJump(Sprite *, Sprite *, void *);
		static void OnCollisionWithInvisibleDriverWrapAround(Sprite *, Sprite *, void *);
};


#endif