#include "MovingAnimator.h"
#include <assert.h>

MovingAnimator :: MovingAnimator (void)
	: sprite((Sprite*) 0), anim((MovingAnimation*) 0){
}

MovingAnimator :: ~MovingAnimator(){}

void MovingAnimator :: Progress (timestamp_t currTime){
	DASSERT(currTime>=0);
	DASSERT(anim);
	DASSERT(lastTime<currTime);

	while (currTime > lastTime && currTime - lastTime >= anim->GetDelay()){
		sprite->Move(anim->GetDx(), anim->GetDy());
		if (!anim->GetContinuous()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
			return;
		}
		else
			lastTime += anim->GetDelay();
	}
}

void MovingAnimator :: Start (Sprite* s, MovingAnimation* a, timestamp_t t){
	DASSERT(s);
	DASSERT(a);
	DASSERT(t>=0);

	sprite = s;
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
}

void MovingAnimator ::Display(Bitmap at){
	sprite->Display(at);
}