#include "MovingAnimator.h"
#include <assert.h>

MovingAnimator :: MovingAnimator (void)
	: sprite((Sprite*) 0), anim((MovingAnimation*) 0){
		assert(sprite);
		assert(anim);
}

MovingAnimator :: ~MovingAnimator(){}

void MovingAnimator :: Progress (timestamp_t currTime){
	assert(currTime);
	assert(anim);
	assert(lastTime);

	while (currTime > lastTime && currTime - lastTime >= anim->GetDelay()){
		//sprite->Move(anim->GetDx(), anim->GetDy());
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
	assert(s);
	assert(a);
	assert(t);

	sprite = s;
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
}