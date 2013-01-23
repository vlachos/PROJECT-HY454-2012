#include "BubAnimator.h"
#include "MemoryManage.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"

BubWalkingAnimator::BubWalkingAnimator(void){
	//this->SetOnFinish( OnFinishCallback , 0);
}


void BubWalkingAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && !args);
	DASSERT( anim==this );
	timestamp_t timestamp = GetGameTime();
	DASSERT( timestamp>0 );
	std::cout<<"in on finish\n";
	AnimatorHolder::MarkAsSuspended(this);
	AnimatorHolder::Cancel(this);

	DASSERT( GetAnimation() );
	DASSERT( GetSprite() );

	animid_t id = GetAnimation()->GetId();

	GetAnimation()->Destroy();
	this->Destroy(); //meta

	MovingAnimation *ma = (MovingAnimation*) AnimationsParser::GetAnimation("BubStand");
	GetSprite()->SetFrame(0);

	BubStandAnimator* mar = new BubStandAnimator();
	mar->SetOnFinish(BubStandAnimator::OnFinishCallback, 0);
	mar->Start(GetSprite(), ma, timestamp);
	
	AnimatorHolder::Register(mar);
	AnimatorHolder::MarkAsRunning(mar);
}

BubStandAnimator::BubStandAnimator(){

}

void BubStandAnimator::OnFinishCallback(Animator* anim, void* args){


}