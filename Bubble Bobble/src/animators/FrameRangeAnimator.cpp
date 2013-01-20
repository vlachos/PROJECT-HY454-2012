#include "FrameRangeAnimator.h"
#include <assert.h>
#include "MemoryManage.h"

FrameRangeAnimator :: FrameRangeAnimator (void) 
	:sprite((Sprite*) 0), anim((FrameRangeAnimation*) 0), currFrame(0xFF){
}

FrameRangeAnimator :: ~FrameRangeAnimator(){}

void FrameRangeAnimator :: Progress (timestamp_t currTime){
	DASSERT(currTime>=0);
	DASSERT(anim);
	DASSERT(lastTime<currTime);

	while (currTime > lastTime && currTime - lastTime >= anim->GetDelay()){

	    if (currFrame == anim->GetEndFrame())
			currFrame = anim->GetStartFrame();
	    else
			++currFrame;

	    sprite->Move(anim->GetDx(), anim->GetDy());
	    sprite->SetFrame(currFrame);
	    lastTime += anim->GetDelay();

	    if (currFrame == anim->GetEndFrame() && !anim->GetContinuous()){
			state = ANIMATOR_FINISHED;
			NotifyStopped();
			return;
	    }
	}
}

void FrameRangeAnimator :: Start (Sprite* s, FrameRangeAnimation* a, timestamp_t t){
	DASSERT(s);
	DASSERT(a);
	DASSERT(t>=0);

	sprite = s;
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
	sprite->SetFrame(currFrame = anim->GetStartFrame());
}

void FrameRangeAnimator::Display(Bitmap at){
	sprite->Display(at);
}