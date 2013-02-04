#ifndef POWERUPSANIMATOR_H
#define POWERUPSANIMATOR_H

#include "MovingAnimator.h"

class RedShoesAnimator: public MovingAnimator{
	public:
		RedShoesAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return RedShoesAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnCollisionWithBub(Sprite *, Sprite *, void *);
		static void OnFinishCallback(Animator*, void*);
};


class YellowSweetAnimator: public MovingAnimator{
	public:
		YellowSweetAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return YellowSweetAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnCollisionWithBub(Sprite *, Sprite *, void *);
		static void OnFinishCallback(Animator*, void*);
};

class BlueSweetAnimator: public MovingAnimator{
	public:
		BlueSweetAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return BlueSweetAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnCollisionWithBub(Sprite *, Sprite *, void *);
		static void OnFinishCallback(Animator*, void*);
};

class PurpleSweetAnimator: public MovingAnimator{
	public:
		PurpleSweetAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return PurpleSweetAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnCollisionWithBub(Sprite *, Sprite *, void *);
		static void OnFinishCallback(Animator*, void*);
};


#endif