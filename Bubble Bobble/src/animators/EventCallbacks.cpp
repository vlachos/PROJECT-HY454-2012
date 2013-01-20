#include "EventCallbacks.h"
#include <iostream>

extern unsigned int GetGameTime (void);

void  EventCallbacks::BubbleWalkStop(Animator* animator, void* args){

	DASSERT( animator && !args);
	timestamp_t timestamp = GetGameTime();
	DASSERT( timestamp>0 );

	AnimatorHolder::MarkAsSuspended(animator);
	AnimatorHolder::Cancel(animator);

	FrameRangeAnimator * anim = (FrameRangeAnimator *) animator;

	Animation* danim = anim->GetAnimation();
	DASSERT( danim );
	Sprite* sprite = anim->GetSprite();
	DASSERT( sprite );

	animid_t id = danim->GetId();

	delete danim;
	delete anim;

	MovingAnimation *ma = new MovingAnimation(0,0,100,true,id);
	sprite->SetFrame(0);

	MovingAnimator* mar = new MovingAnimator();
	mar->Start(sprite, ma, timestamp);

	AnimatorHolder::Register(mar);
	AnimatorHolder::MarkAsRunning(mar);
	
}