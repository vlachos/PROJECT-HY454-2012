#ifndef BARONVONBLUBAANIMATOR_H
#define BARONVONBLUBAANIMATOR_H

#include "MovingAnimator.h"
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

class BaronVonBlubaStandAnimator : public MovingAnimator{
	public:
		typedef enum _direction{
			direction_up_t,
			direction_down_t,
			direction_left_t,
			direction_rigth_t
		}direction;
		BaronVonBlubaStandAnimator(direction);

		enum animatorType_t GetAnimatorType(void)
			{ return baronVonBlubaStandAnimator_t; }
		void RegistCollitions(Sprite* spr);
		static void OnCollisionWithEnemy(Sprite *, Sprite *, void *);
		direction prevDirection;
};


class BaronVonBlubaRushAnimator : public MovingPathAnimator{
	public:
		BaronVonBlubaRushAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return baronVonBlubaRushAnimator_t; }
		void RegistCollitions(Sprite* spr);
		static void OnCollisionWithEnemy(Sprite *, Sprite *, void *);
		static void OnFinishCallback(Animator*, void*);
};


#endif
