#ifndef BARONVONBLUBAANIMATOR_H
#define BARONVONBLUBAANIMATOR_H

#include "FrameRangeAnimator.h"
#include "MovingPathAnimator.h"
#include "Sprite.h"

namespace BaronVonBlubaAnimatorActions{
	extern void StartBaronVonBludaAnimator(void*);
	extern void StartHurryUpAnimator(void*);
}

class HurryUpAnimator : public MovingPathAnimator{
	public:
		HurryUpAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return hurryUpAnimator_t; }

		static void OnFinishCallback(Animator*, void*);
};

class BaronVonBlubaStandAnimator : public FrameRangeAnimator{
	public:
		BaronVonBlubaStandAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return baronVonBlubaStandAnimator_t; }
		static void OnCollisionWithEnemy(Sprite *, Sprite *, void *);
		static void OnFinishCallback(Animator*, void*);
};


class BaronVonBlubaRushAnimator : public MovingPathAnimator{
	public:
		BaronVonBlubaRushAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return baronVonBlubaStandAnimator_t; }
		void RegistCollitions(Sprite* spr);
		static void OnCollisionWithEnemy(Sprite *, Sprite *, void *);
		static void OnFinishCallback(Animator*, void*);
};


#endif
