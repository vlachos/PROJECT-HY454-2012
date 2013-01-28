#include "MovingPathAnimator.h"


MovingPathAnimator::MovingPathAnimator (void)
	:sprite((Sprite*) 0), anim((MovingPathAnimation*) 0){}
MovingPathAnimator::~MovingPathAnimator(){}

void MovingPathAnimator::Progress (timestamp_t currTime){
	DASSERT(currTime>=0);
	DASSERT(anim);
	DASSERT(lastTime<=currTime);

	while (currTime > lastTime && currTime - lastTime >= anim->GetPath()[anim->GetCurrIndex()].delay){

		if (anim->GetCurrIndex() == anim->GetPath().size())
			anim->SetCurrIndex(0);
	    else
			anim->SetCurrIndex(anim->GetCurrIndex()+1);

		sprite->Move(anim->GetPath()[anim->GetCurrIndex()].dx, anim->GetPath()[anim->GetCurrIndex()].dy);
		sprite->SetFrame(anim->GetPath()[anim->GetCurrIndex()].frame);
	    lastTime += anim->GetPath()[anim->GetCurrIndex()].delay;

	    if (anim->GetCurrIndex() == anim->GetPath().size() && !anim->GetContinuous()){
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
	sprite->SetFrame(anim->GetPath()[anim->GetCurrIndex()].frame);
}
void MovingPathAnimator::Display(Bitmap at){
	sprite->Display(at);
}
