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
#include "BubblesAnimator.h"
#include "InvisibleSprites.h"


void RiverAnimatorActions::StartWaterBubble(void* args){

	FrameRangeAnimation *fra = (FrameRangeAnimation*) AnimationsParser::GetAnimation("BubbleDown");
	Sprite *sprite=new Sprite(
								( ( rand() % 2 == 0 ) ? 323 : 160 ),
								0,
								false,
								AnimationFilmHolder::GetFilm( "WaterBubble" ), 
								Terrain::GetActionLayer(), 
								true
							);

	WaterBubbleAnimator *bbar=new WaterBubbleAnimator();
	bbar->RegistCollitions(sprite);

	START_ANIMATOR(bbar, sprite, fra, GetGameTime() );
}

void RiverAnimatorActions::StartRiverAnimator(int x, int y, bool goesLeft){
	RiverSprite* sprite7 = new RiverSprite(x,y,true,AnimationFilmHolder::GetFilm("RiverHFront"), Terrain::GetActionLayer(), true);	
	MovingAnimation* anim7 = (MovingAnimation*) AnimationsParser::GetAnimation("WaterRushLeft");
	RiverAnimator* animr7 = new RiverAnimator();
	sprite7->AddStartFallingListener( animr7 );
	sprite7->AddStopFallingListener( animr7 );
	animr7->RegistCollitions(sprite7);
	START_ANIMATOR( animr7, sprite7, anim7, GetGameTime() );
}


///////////////////////////////////////////


WaterBubbleAnimator::WaterBubbleAnimator(){

}

void WaterBubbleAnimator::RegistCollitions(Sprite* spr){
	CollisionChecker::Register(spr, bubBubbleAnimator_t, mightaInBubbleHighAngry_t, this, BubblesAnimatorActions::OnCollisionWithBubble);
	std::vector<InvisibleSprites::InvisibleDrivers> ibd = InvisibleSprites::GetInvisibleWrapAroundDrivers();
	for(unsigned int i=0; i<ibd.size(); ++i){
		CollisionChecker::Register(spr, ibd[i].sprite, this, OnCollisionWithInvisibleDriverWrapAround);
	}
	CollisionChecker::RegisterBubbleDrivers(spr, this);
}

void WaterBubbleAnimator::OnCollisionWithBubFalling(Sprite *bubble, Sprite *bub, void *args){
	WaterBubbleAnimator* _this = (WaterBubbleAnimator*) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	RiverAnimatorActions::StartRiverAnimator(bubble->GetX(), bubble->GetY(), bubble->GoesLeft());
	DESTROY_ANIMATOR( _this );
}

void WaterBubbleAnimator::OnCollisionWithBubJump(Sprite *bubble, Sprite *bub, void *args){
	WaterBubbleAnimator* _this = (WaterBubbleAnimator*) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	RiverAnimatorActions::StartRiverAnimator(bubble->GetX(), bubble->GetY(), bubble->GoesLeft());
	DESTROY_ANIMATOR( _this );
}

void WaterBubbleAnimator::OnCollisionWithInvisibleDriverWrapAround(Sprite *bubble, Sprite *drv, void *args){
	WaterBubbleAnimator* _this = (WaterBubbleAnimator*) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );
}



//////////////////////////////////////////////


RiverAnimator::RiverAnimator() { this->SetOnFinish(OnFinishCallback, this); }

void RiverAnimator::RegistCollitions(RiverSprite* rSpr){
	CollisionChecker::Register(rSpr, zenChanStandAnimator_t,zenChanJumpAnimator_t,RiverAnimator::OnCollisionWithZenChan);
	CollisionChecker::Register(rSpr, mightaStandAnimator_t,mightaJumpAnimator_t,RiverAnimator::OnCollisionWithMighta);
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
