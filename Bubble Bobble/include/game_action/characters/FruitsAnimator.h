#ifndef FRUITS_H
#define FRUITS_H

#include "MovingAnimator.h"

class BananaAnimator: public MovingAnimator{
	public:
		BananaAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return BananaAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnCollisionWithBub(Sprite *, Sprite *, void *);
		static void OnFinishCallback(Animator*, void*);
};


class OrangeAnimator: public MovingAnimator{
	public:
		OrangeAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return OrangeAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnCollisionWithBub(Sprite *, Sprite *, void *);
		static void OnFinishCallback(Animator*, void*);
};

class PeachAnimator: public MovingAnimator{
	public:
		PeachAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return PeachAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnCollisionWithBub(Sprite *, Sprite *, void *);
		static void OnFinishCallback(Animator*, void*);
};

class WaterMelonAnimator: public MovingAnimator{
	public:
		WaterMelonAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return WaterMelonAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnCollisionWithBub(Sprite *, Sprite *, void *);
		static void OnFinishCallback(Animator*, void*);
};

class BlueDiamondAnimator: public MovingAnimator{
	public:
		BlueDiamondAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return BlueDiamondAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnCollisionWithBub(Sprite *, Sprite *, void *);
		static void OnFinishCallback(Animator*, void*);
};

#endif