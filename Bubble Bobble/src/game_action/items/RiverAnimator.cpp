#include "RiverAnimator.h"
#include "MemoryManage.h"
#include "GameActionUtilities.h"
#include "CollisionChecker.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "MovingPathAnimation.h"
#include "ZenChanAnimator.h"
#include "MightaAnimator.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"


RiverAnimator::RiverAnimator() { this->SetOnFinish(OnFinishCallback, this); }

void RiverAnimator::RegistCollitions(Sprite* spr){
	CollisionChecker::Register(spr,zenChanStandAnimator_t,zenChanJumpAnimator_t,RiverAnimator::OnCollisionWithZenChan);
	CollisionChecker::Register(spr,mightaStandAnimator_t,mightaJumpAnimator_t,RiverAnimator::OnCollisionWithMighta);
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
	DASSERT( args );
	FrameRangeAnimator* _this = (FrameRangeAnimator*) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );

	Sprite* newSprite = 
		new Sprite(_this->GetSprite()->GetX(), _this->GetSprite()->GetY(), true, AnimationFilmHolder::GetFilm("ZenChanDie"), Terrain::GetActionLayer(),false);

	MovingPathAnimation* mpa = (MovingPathAnimation*)AnimationsParser::GetAnimation("ZenChanDie");
	ZenChanDieAnimator *bda = new ZenChanDieAnimator();
	newSprite->AddStartFallingListener(bda);
	START_ANIMATOR( bda, newSprite, mpa, GetGameTime());
}

void RiverAnimator::OnCollisionWithMighta(Sprite * spr1, Sprite * spr2, void* args){
	DASSERT( args );
	FrameRangeAnimator* _this = (FrameRangeAnimator*) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );

	Sprite* newSprite = 
		new Sprite(_this->GetSprite()->GetX(), _this->GetSprite()->GetY(), true, AnimationFilmHolder::GetFilm("MightaDie"), Terrain::GetActionLayer(),false);

	MovingPathAnimation* mpa = (MovingPathAnimation*)AnimationsParser::GetAnimation("MightaDie");
	MightaDieAnimator *bda = new MightaDieAnimator();
	newSprite->AddStartFallingListener(bda);
	START_ANIMATOR( bda, newSprite, mpa, GetGameTime());
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