#include "FrameRangeAnimator.h"
#include <assert.h>

FrameRangeAnimator :: FrameRangeAnimator (void) 
	:sprite((Sprite*) 0), anim((FrameRangeAnimation*) 0), currFrame(0xFF){
		assert(sprite);
		assert(anim);
		assert(currFrame);
}

FrameRangeAnimator :: ~FrameRangeAnimator(){}

void FrameRangeAnimator :: Progress (timestamp_t currTime){
	assert(currTime);
	assert(anim);
	assert(lastTime);
	assert(currFrame);

	while (currTime > lastTime && currTime - lastTime >= anim->GetDelay()){

	    if (currFrame == anim->GetEndFrame())
			currFrame = anim->GetStartFrame();
	    else
			++currFrame;

	    //sprite->Move(anim->GetDx(), anim->GetDy());
	    //sprite->SetFrame(currFrame);
	    lastTime += anim->GetDelay();

	    if (currFrame == anim->GetEndFrame() && !anim->GetContinuous()){
			state = ANIMATOR_FINISHED;
			NotifyStopped();
			return;
	    }
	}
}

void FrameRangeAnimator :: Start (Sprite* s, FrameRangeAnimation* a, timestamp_t t){
	assert(s);
	assert(a);
	assert(t);

	sprite = s;
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
	//sprite->SetFrame(currFrame = anim->GetStartFrame());
}