#ifndef RIVERANIMATOR_H
#define RIVERANIMATOR_H

#include "MovingAnimator.h"

class RiverAnimator: public MovingAnimator {

	public:
		RiverAnimator();
		
		enum animatorType_t GetAnimatorType(void)
			{ return riverAnimator_t; }

		void RegistCollitions(Sprite*);

		static void OnFinishCallback(Animator*, void*);
		static void OnStartFallingCallback(Animator*, void*);
		static void OnStopFallingCallback(Animator*, void*);

		static void OnCollisionWithBub(Sprite *, Sprite *, void *);

		static void OnCollisionWithZenChan(Sprite *, Sprite *, void *);

		static void OnCollisionWithMighta(Sprite *, Sprite *, void *);
};


#endif