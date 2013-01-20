#ifndef FRAMERANGEANIMATOR_H
#define FRAMERANGEANIMATOR_H

#include "utilities.h"
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

	FrameRangeAnimation* GetAnimation(void)
		{ return anim; }

	Sprite* GetSprite(void)
		{ return sprite; }

	void Progress (timestamp_t currTime);
	void Start (Sprite* s, FrameRangeAnimation* a, timestamp_t t);
	void Display(Bitmap at);
};

#endif