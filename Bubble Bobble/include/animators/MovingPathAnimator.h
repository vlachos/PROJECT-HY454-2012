#ifndef MOVINGPATHANIMATOR_H
#define MOVINGPATHANIMATOR_H

#include "utilities.h"
#include "Animator.h"
#include "MovingPathAnimation.h"
#include "Sprite.h"

class MovingPathAnimator : public Animator{
	Sprite *sprite;
	MovingPathAnimation *anim;
	int currIndex;
public:
	MovingPathAnimator (void);
	~MovingPathAnimator();

	MovingPathAnimation* GetAnimation(void)
		{ return anim; }

	Sprite* GetSprite(void)
		{ return sprite; }

	void Progress (timestamp_t currTime);
	void Start (Sprite* s, MovingPathAnimation* a, timestamp_t t);
	void Display(Bitmap at);

	int GetCurrIndex(){return currIndex;}
	void SetCurrIndex(int index) { currIndex = index; }

};

#endif