#include "BubblesAnimator.h"
#include "AnimatorHolder.h"
#include "MemoryManage.h"
#include "CollisionChecker.h"

BubBubbleAnimator::BubBubbleAnimator(){
	this->SetOnFinish( OnFinishCallback, (void*)this );
}

void BubBubbleAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BubBubbleAnimator * _this = (BubBubbleAnimator*)args;
	DASSERT( anim==_this );
	DASSERT( _this->GetAnimation() );
	DASSERT( _this->GetSprite() );

	AnimatorHolder::MarkAsSuspended(_this);
	AnimatorHolder::Cancel(_this);
	CollisionChecker::Cancel(_this->GetSprite());

	_this->GetAnimation()->Destroy();
	_this->GetSprite()->Destroy();
	_this->Destroy(); 
}