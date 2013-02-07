#include "RiverAnimator.h"
#include "MemoryManage.h"
#include "GameActionUtilities.h"
#include "CollisionChecker.h"


RiverAnimator::RiverAnimator() { this->SetOnFinish(OnFinishCallback, this); }

void RiverAnimator::RegistCollitions(Sprite* spr){
}

void RiverAnimator::OnFinishCallback(Animator* anmr, void* args){
}

void RiverAnimator::OnStartFalling(Sprite* spr){
	DASSERT( spr == this->GetSprite() );

	this->GetAnimation()->SetDy(this->GetAnimation()->GetDx()>0 ? 
									this->GetAnimation()->GetDx(): 
									-this->GetAnimation()->GetDx() );
	this->GetAnimation()->SetDx(0);
}

void RiverAnimator::OnStopFalling(Sprite* spr){
	DASSERT( spr == this->GetSprite() );

	RiverSprite* rvrSpr = (RiverSprite*) this->GetSprite();

	this->GetAnimation()->SetDx( rvrSpr->IsRiverDirectionLeft()? 
									-this->GetAnimation()->GetDy(): 
									this->GetAnimation()->GetDy() );
	this->GetAnimation()->SetDy(0);

}


void RiverAnimator::OnCollisionWithBub(Sprite * spr1, Sprite * spr2, void* args){
}

void RiverAnimator::OnCollisionWithZenChan(Sprite * spr1, Sprite * spr2, void* args){
}

void RiverAnimator::OnCollisionWithMighta(Sprite * spr1, Sprite * spr2, void* args){
}
