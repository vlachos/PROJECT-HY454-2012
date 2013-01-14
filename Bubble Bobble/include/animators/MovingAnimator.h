#ifndef MOVINGANIMATOR_H
#define MOVINGANIMATOR_H

#include "Animator.h"
#include "MovingAnimation.h"
#include "Sprite.h"


class MovingAnimator : public Animator{
	Sprite*	sprite;
	MovingAnimation* anim;

public:
	MovingAnimator (void);
	~MovingAnimator();
	void Progress (timestamp_t currTime);
	void Start (Sprite* s, MovingAnimation* a, timestamp_t t);
};

#endif