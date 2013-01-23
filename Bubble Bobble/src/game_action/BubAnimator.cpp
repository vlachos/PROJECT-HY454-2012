#include "BubAnimator.h"
#include "MemoryManage.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"

BubWalkingAnimator::BubWalkingAnimator(void) {
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void BubWalkingAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BubWalkingAnimator * _this = (BubWalkingAnimator*)args;
	DASSERT( anim==_this );
	timestamp_t timestamp = GetGameTime();
	DASSERT( timestamp>0 );
	AnimatorHolder::MarkAsSuspended(_this);
	AnimatorHolder::Cancel(_this);

	DASSERT( _this->GetAnimation() );
	DASSERT( _this->GetSprite() );

	animid_t id = _this->GetAnimation()->GetId();

	_this->GetAnimation()->Destroy();
	_this->Destroy(); //meta

	MovingAnimation *ma = (MovingAnimation*) AnimationsParser::GetAnimation("BubStand");
	_this->GetSprite()->SetFrame(0);

	BubStandAnimator* mar = new BubStandAnimator();
	mar->SetOnFinish(BubStandAnimator::OnFinishCallback, 0);
	mar->Start(_this->GetSprite(), ma, timestamp);
	
	AnimatorHolder::Register(mar);
	AnimatorHolder::MarkAsRunning(mar);
}

BubStandAnimator::BubStandAnimator(){

}

void BubStandAnimator::OnFinishCallback(Animator* anim, void* args){


}