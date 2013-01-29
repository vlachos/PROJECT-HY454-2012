#include "MovingPathAnimator.h"


MovingPathAnimator::MovingPathAnimator (void)
	:sprite((Sprite*) 0), anim((MovingPathAnimation*) 0), currIndex(0){}

MovingPathAnimator::~MovingPathAnimator(){}

void MovingPathAnimator::Progress (timestamp_t currTime){
	DASSERT(currTime>=0);
	DASSERT(anim);
	DASSERT(lastTime<=currTime);

	while (currTime > lastTime && currTime - lastTime >= anim->GetPath()[currIndex].delay){
		
		sprite->Move(	
						anim->GetPath()[currIndex].x - sprite->GetX(), 
						anim->GetPath()[currIndex].y - sprite->GetY()
					);

		sprite->SetFrame(anim->GetPath()[currIndex].frame);
	    lastTime += anim->GetPath()[currIndex].delay;

		if (currIndex == anim->GetPath().size())
			currIndex = 0;
	    else
			++currIndex;

	    if (currIndex == anim->GetPath().size() && !anim->GetContinuous()){
			state = ANIMATOR_FINISHED;
			NotifyStopped();
			return;
	    }

	}

}
void MovingPathAnimator::Start (Sprite* s, MovingPathAnimation* a, timestamp_t t){
	DASSERT(s);
	DASSERT(a);
	DASSERT(t>=0);

	sprite = s;
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
	sprite->SetFrame(anim->GetPath()[currIndex].frame);
}
void MovingPathAnimator::Display(Bitmap at){
	sprite->Display(at);
}
