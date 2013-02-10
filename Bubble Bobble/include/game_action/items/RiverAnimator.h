#ifndef RIVERANIMATOR_H
#define RIVERANIMATOR_H

#include "RiverSprite.h"
#include "MovingAnimator.h"

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


#endif