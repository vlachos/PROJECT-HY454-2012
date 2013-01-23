#ifndef BUBANIMATOR_H
#define BUBANIMATOR_H

#include "FrameRangeAnimator.h"
#include "MovingAnimator.h"

class BubStandAnimator : public MovingAnimator{

	public:
		BubStandAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return BubStandAnimator_t; }
		static void OnFinishCallback(Animator*, void*);
};

class BubWalkingAnimator : public FrameRangeAnimator{

	public:
		BubWalkingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubWalkAnimator_t; }
		static void OnFinishCallback(Animator*, void*);
};





#endif