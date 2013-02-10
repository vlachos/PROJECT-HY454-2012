#ifndef SCROLLINGANIMATOR_H
#define SCROLLINGANIMATOR_H

#include "Animator.h"
#include "ScrollingAnimation.h"
#include "TileLayer.h"

class ScrollingAnimator : public Animator{

	private:
		ScrollingAnimation* anim;
		TileLayer* actionLayer;
		unsigned int currIndex;

	public:
		ScrollingAnimator (void);
		~ScrollingAnimator (void);

		ScrollingAnimation* GetAnimation(void);
		TileLayer* GetActionLayer(void);

		void Progress (timestamp_t currTime);
		void Start (TileLayer* aLayer, ScrollingAnimation* anim, timestamp_t t);
		void Display(Bitmap at);
};

#endif