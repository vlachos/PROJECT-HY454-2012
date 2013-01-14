#ifndef FRAMERANGEANIMATOR_H
#define FRAMERANGEANIMATOR_H

#include "Animator.h"
#include "FrameRangeAnimation.h"
#include "Sprite.h"

class FrameRangeAnimator : public Animator{
	Sprite*	sprite;
	FrameRangeAnimation* anim;
	frame_t	currFrame;

public:
	FrameRangeAnimator (void);
	~FrameRangeAnimator();
	void Progress (timestamp_t currTime);
	void Start (Sprite* s, FrameRangeAnimation* a, timestamp_t t);
};

#endif