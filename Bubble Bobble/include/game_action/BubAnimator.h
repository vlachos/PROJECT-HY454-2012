#ifndef BUBANIMATOR_H
#define BUBANIMATOR_H

#include "FrameRangeAnimator.h"
#include "MovingAnimator.h"

class BubWalkingAnimator : public FrameRangeAnimator{

	public:
		BubWalkingAnimator();

		static void OnFinishCallback(Animator*, void*);
};

class BubStandAnimator : public MovingAnimator{

	public:
		BubStandAnimator();

		static void OnFinishCallback(Animator*, void*);
};



#endif