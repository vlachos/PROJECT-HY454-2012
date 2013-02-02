#ifndef BUBBLESANIMATOR_H
#define BUBBLESANIMATOR_H

#include "MovingAnimator.h"
#include "FrameRangeAnimator.h"
#include "MovingPathAnimator.h"

class BubBubbleBlastOffAnimator: public FrameRangeAnimator{
	public:
		BubBubbleBlastOffAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubBubbleBlastOffAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);

		static void OnCollisionWithZenChanStand(Sprite *, Sprite *, void *);
		static void OnCollisionWithZenChanWalking(Sprite *, Sprite *, void *);
		static void OnCollisionWithZenChanFalling(Sprite *, Sprite *, void *);
		static void OnCollisionWithZenChanJump(Sprite *, Sprite *, void *);
		static void OnCollisionWithZenChanAngryStand(Sprite *, Sprite *, void *);
		static void OnCollisionWithZenZenChanAngryWalking(Sprite *, Sprite *, void *);
		static void OnCollisionWithZenChanAngryFalling(Sprite *, Sprite *, void *);
		static void OnCollisionWithZenChanAngryJump(Sprite *, Sprite *, void *);

		static void OnCollisionWithMightaStand(Sprite *, Sprite *, void *);
		static void OnCollisionWithMightaWalking(Sprite *, Sprite *, void *);
		static void OnCollisionWithMightaFalling(Sprite *, Sprite *, void *);
		static void OnCollisionWithMightaJump(Sprite *, Sprite *, void *);
		static void OnCollisionWithMightaAngryStand(Sprite *, Sprite *, void *);
		static void OnCollisionWithMightaAngryWalking(Sprite *, Sprite *, void *);
		static void OnCollisionWithMightaAngryFalling(Sprite *, Sprite *, void *);
		static void OnCollisionWithMightaAngryJump(Sprite *, Sprite *, void *);
};

class BubBubbleAnimator: public FrameRangeAnimator{
	public:
		BubBubbleAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubBubbleAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnCollisionWithBubFalling(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubJump(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubble(Sprite *, Sprite *, void *);

		static void OnCollisionWithInvisibleDriverGoDown(Sprite *, Sprite *, void *);

		static void OnFinishCallback(Animator*, void*);
};

class BubPingBubbleAnimator: public MovingPathAnimator{
	public:
		BubPingBubbleAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubBubbleAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnCollisionWithBubFalling(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubJump(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubble(Sprite *, Sprite *, void *);
		static void OnFinishCallback(Animator*, void*);
};

class PonEffectAnimator: public MovingAnimator{
	public:
		PonEffectAnimator();
		
		enum animatorType_t GetAnimatorType(void)
			{ return ponEffectAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnCollisionWithBubble(Sprite *, Sprite *, void *);
		static void OnFinishCallback(Animator*, void*);
};

class ZenChanInBubbleAnimator : public MovingPathAnimator{
	public:
		ZenChanInBubbleAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanInBubble_t; }

		static void OnFinishCallback(Animator*, void*);
		void RegistCollitions(Sprite*);
		static void OnCollisionWithBubFalling(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubJump(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubble(Sprite *, Sprite *, void *);
};

class ZenChanInBubbleMediumAngryAnimator : public MovingPathAnimator{
	public:
		ZenChanInBubbleMediumAngryAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanInBubbleMediumAngry_t; }

		static void OnFinishCallback(Animator*, void*);
		void RegistCollitions(Sprite*);
		static void OnCollisionWithBubFalling(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubJump(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubble(Sprite *, Sprite *, void *);
};

class ZenChanInBubbleHighAngryAnimator : public MovingPathAnimator{
	public:
		ZenChanInBubbleHighAngryAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanInBubbleHighAngry_t; }

		static void OnFinishCallback(Animator*, void*);
		void RegistCollitions(Sprite*);
		static void OnCollisionWithBubFalling(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubJump(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubble(Sprite *, Sprite *, void *);
};

class MightaInBubbleAnimator : public MovingPathAnimator{
	public:
		MightaInBubbleAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return mightaInBubble_t; }

		static void OnFinishCallback(Animator*, void*);
		void RegistCollitions(Sprite*);
		static void OnCollisionWithBubFalling(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubJump(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubble(Sprite *, Sprite *, void *);
};

class MightaInBubbleMediumAngryAnimator : public MovingPathAnimator{
	public:
		MightaInBubbleMediumAngryAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return mightaInBubbleMediumAngry_t; }

		static void OnFinishCallback(Animator*, void*);
		void RegistCollitions(Sprite*);
		static void OnCollisionWithBubFalling(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubJump(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubble(Sprite *, Sprite *, void *);
};

class MightaInBubbleHighAngryAnimator : public MovingPathAnimator{
	public:
		MightaInBubbleHighAngryAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return mightaInBubbleHighAngry_t; }

		static void OnFinishCallback(Animator*, void*);
		void RegistCollitions(Sprite*);
		static void OnCollisionWithBubFalling(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubJump(Sprite *, Sprite *, void *);
		static void OnCollisionWithBubble(Sprite *, Sprite *, void *);
};

#endif