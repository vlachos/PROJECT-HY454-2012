#include "RiverAnimator.h"
#include "MemoryManage.h"
#include "GameActionUtilities.h"
#include "CollisionChecker.h"


RiverAnimator::RiverAnimator() { this->SetOnFinish(OnFinishCallback, this); }

void RiverAnimator::RegistCollitions(Sprite* spr){
}

void RiverAnimator::OnFinishCallback(Animator* anmr, void* args) {  }

void RiverAnimator::OnStartFalling(Sprite* spr){
	DASSERT( spr == this->GetSprite() );

	//sprite
	RiverSprite* riverSpr = (RiverSprite*) this->GetSprite();
	riverSpr->RiverStartFalling();

	//animation
	this->GetAnimation()->SetDy(this->GetAnimation()->GetDx()>0 ? 
									this->GetAnimation()->GetDx(): 
									-this->GetAnimation()->GetDx() );
	this->GetAnimation()->SetDx(0);
}

void RiverAnimator::OnStopFalling(Sprite* spr){
	DASSERT( spr == this->GetSprite() );

	//sprite
	RiverSprite* riverSpr = (RiverSprite*) this->GetSprite();
	riverSpr->RiverStopFalling();

	//animation
	this->GetAnimation()->SetDx( riverSpr->IsRiverDirectionLeft()? 
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


void RiverAnimator :: Progress (timestamp_t currTime){
	DASSERT(currTime>=0);
	DASSERT(this->GetAnimation());
	DASSERT(lastTime<=currTime);

	while (currTime > lastTime && currTime - lastTime >= this->GetAnimation()->GetDelay()){

		((RiverSprite*)this->GetSprite() )->Move(this->GetAnimation()->GetDx(), this->GetAnimation()->GetDy());

		if (!this->GetAnimation()->GetContinuous()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
			return;
		}
		else
			lastTime += this->GetAnimation()->GetDelay();
	}

}

void RiverAnimator::Display(Bitmap at){
	((RiverSprite*)this->GetSprite() )->Display(at);
}