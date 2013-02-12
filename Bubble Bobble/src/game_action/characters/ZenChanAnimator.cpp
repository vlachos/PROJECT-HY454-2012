#include "ZenChanAnimator.h"
#include "BubAnimator.h"
#include "GameActionUtilities.h"
#include "MemoryManage.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "CollisionChecker.h"
#include "FruitsAnimator.h"
#include "BubbleLogic.h"
#include "RiverAnimator.h"
#include "StageInitializer.h"

//////////////////////////////////////////////////////ZenChanAnimators//////////////////////////////////////////////

////////////////ZenChanStandAnimator
ZenChanStandAnimator::ZenChanStandAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void ZenChanStandAnimator::RegistCollitions(Sprite *spr){
	
}

void ZenChanStandAnimator::OnFinishCallback(Animator* anim, void* args){}

////////////////ZenChanWalkingAnimator
ZenChanWalkingAnimator::ZenChanWalkingAnimator(void) {
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void ZenChanWalkingAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr,bubStandAnimator_t,bubJumpAnimator_t,BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr,riverAnimator_t,riverAnimator_t, this, RiverAnimator::OnCollisionWithZenChan);
}

void ZenChanWalkingAnimator::OnStartFalling(Sprite * sprite){
	
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenFallAnmn, "ZenChanFalling",
						ZenChanFallingAnimator, zenFallAnmr, this->GetSprite() );
	

	zenFallAnmr->RegistCollitions(this->GetSprite());

	this->GetSprite()->AddStopFallingListener(zenFallAnmr);

	START_ANIMATOR( zenFallAnmr, this->GetSprite(), zenFallAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}


void ZenChanWalkingAnimator::OnFinishCallback(Animator* animr, void* args){
	DASSERT( animr && args);
	ZenChanWalkingAnimator* _this = (ZenChanWalkingAnimator*)args;
	DASSERT( animr ==_this );
	DASSERT( _this->GetAnimation() && _this->GetSprite());

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenStandAnmn, "ZenChanStand",
						ZenChanStandAnimator, zenStandAnmr, _this->GetSprite() );

	zenStandAnmr->RegistCollitions(_this->GetSprite() );

	START_ANIMATOR( zenStandAnmr, _this->GetSprite(), zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE(_this );
}


////////////////ZenChanFallingAnimator
ZenChanFallingAnimator::ZenChanFallingAnimator(){}

void ZenChanFallingAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr,bubStandAnimator_t,bubJumpAnimator_t,BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr,riverAnimator_t,riverAnimator_t, this, RiverAnimator::OnCollisionWithZenChan);
	CollisionChecker::RegisterBubbleWrapAroundDrivers(spr, this);
}

void ZenChanFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenStandAnmn, this->GetSprite()->GoesLeft()?"ZenChanWalkLeft":"ZenChanWalkRight",
						ZenChanWalkingAnimator, zenStandAnmr, this->GetSprite() );	
	
	zenStandAnmr->RegistCollitions(this->GetSprite());
	this->GetSprite()->AddStartFallingListener( zenStandAnmr );
	START_ANIMATOR( zenStandAnmr, this->GetSprite(), zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}


////////////////ZenChanJumpAnimator
ZenChanJumpAnimator::ZenChanJumpAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void ZenChanJumpAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr,bubStandAnimator_t,bubJumpAnimator_t,BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr,riverAnimator_t,riverAnimator_t, this, RiverAnimator::OnCollisionWithZenChan);
}

void ZenChanJumpAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	ZenChanJumpAnimator * _this = (ZenChanJumpAnimator*)args;
	DASSERT( anim==_this );

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	FrameRangeAnimation *fra= (FrameRangeAnimation*)AnimationsParser::GetAnimation("ZenChanFalling");
	Sprite *n_sprite = _this->GetSprite();
	n_sprite->ClearListeners();

	ZenChanFallingAnimator *frtor=new ZenChanFallingAnimator();
	n_sprite->AddStopFallingListener(frtor);

	frtor->RegistCollitions(n_sprite);

	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( _this );

}

//////////////////////////////ZenChanAngryStandAnimator
ZenChanAngryStandAnimator::ZenChanAngryStandAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void ZenChanAngryStandAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr,bubStandAnimator_t,bubJumpAnimator_t,BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr,riverAnimator_t,riverAnimator_t, this, RiverAnimator::OnCollisionWithZenChan);
}

void ZenChanAngryStandAnimator::OnFinishCallback(Animator*, void*){}


////////////////////////////ZenChanAngryWalkingAnimator
ZenChanAngryWalkingAnimator::ZenChanAngryWalkingAnimator(){
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void ZenChanAngryWalkingAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr,bubStandAnimator_t,bubJumpAnimator_t,BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr,riverAnimator_t,riverAnimator_t, this, RiverAnimator::OnCollisionWithZenChan);
}

void ZenChanAngryWalkingAnimator::OnStartFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenFallAnmn, "ZenChanAngryFalling",
						ZenChanAngryFallingAnimator, zenFallAnmr, this->GetSprite() );

	this->GetSprite()->AddStopFallingListener(zenFallAnmr);
	zenFallAnmr->RegistCollitions(this->GetSprite());

	START_ANIMATOR( zenFallAnmr, this->GetSprite(), zenFallAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}

void ZenChanAngryWalkingAnimator::OnFinishCallback(Animator* animr, void* args){
	DASSERT( animr && args);
	ZenChanAngryWalkingAnimator* _this = (ZenChanAngryWalkingAnimator*)args;
	DASSERT( animr ==_this );
	DASSERT( _this->GetAnimation() && _this->GetSprite());

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenStandAnmn, "ZenChanAngryStand",
						ZenChanAngryStandAnimator, zenStandAnmr, _this->GetSprite() );

	zenStandAnmr->RegistCollitions(_this->GetSprite());

	START_ANIMATOR( zenStandAnmr, _this->GetSprite(), zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE(_this );
}


///////////////////////////ZenChanAngryFallingAnimator
ZenChanAngryFallingAnimator::ZenChanAngryFallingAnimator(){
}

void ZenChanAngryFallingAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr,bubStandAnimator_t,bubJumpAnimator_t,BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr,riverAnimator_t,riverAnimator_t, this, RiverAnimator::OnCollisionWithZenChan);
	CollisionChecker::RegisterBubbleWrapAroundDrivers(spr, this);
}

void ZenChanAngryFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenStandAnmn, this->GetSprite()->GoesLeft()?"ZenChanAngryWalkLeft":"ZenChanAngryWalkRight",
						ZenChanAngryWalkingAnimator, zenStandAnmr, this->GetSprite() );	
	
	zenStandAnmr->RegistCollitions(this->GetSprite());
	this->GetSprite()->AddStartFallingListener( zenStandAnmr );
	START_ANIMATOR( zenStandAnmr, this->GetSprite(), zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}

///////////////////////////ZenChanAngryJumpAnimator
ZenChanAngryJumpAnimator::ZenChanAngryJumpAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void ZenChanAngryJumpAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr,bubStandAnimator_t,bubJumpAnimator_t,BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr,riverAnimator_t,riverAnimator_t, this, RiverAnimator::OnCollisionWithZenChan);
}

void ZenChanAngryJumpAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	ZenChanAngryJumpAnimator * _this = (ZenChanAngryJumpAnimator*)args;
	DASSERT( anim==_this );

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	FrameRangeAnimation *fra= (FrameRangeAnimation*)AnimationsParser::GetAnimation("ZenChanAngryFalling");
	Sprite *n_sprite=new Sprite(_this->GetSprite()->GetX(),_this->GetSprite()->GetY(),
		_this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm(_this->GetSprite()->GoesLeft()?"ZenChanAngry":"ZenChanAngry"), 
						Terrain::GetActionLayer(), _this->GetSprite()->GoesLeft());

	ZenChanAngryFallingAnimator *frtor=new ZenChanAngryFallingAnimator();
	n_sprite->AddStopFallingListener(frtor);

	frtor->RegistCollitions(n_sprite);

	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( _this );
	std::cout<<"in callback\n";
}

////////////////ZenChanDieAnimator////////die for both angry and normal
ZenChanDieAnimator::ZenChanDieAnimator(){
	this->SetOnFinish( OnFinishCallback, this );
	this->SetRiverDie(false);
}

void ZenChanDieAnimator::RegistCollitions(Sprite *spr){

}

void ZenChanDieAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim == args && anim );
	ZenChanDieAnimator* _this = (ZenChanDieAnimator*) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );

	//logic
	if (!_this->GetRiverDie() )
		FruitsAnimators::StartFruitAnimator(BubbleLogic::GetFruitType(), _this->GetSprite()->GetX(), _this->GetSprite()->GetY());
	else
		FruitsAnimators::StartFruitAnimator(5, _this->GetSprite()->GetX(), _this->GetSprite()->GetY());

	SCROLL_IF_NO_ENEMIES();
}

void ZenChanDieAnimator::OnStartFalling(Sprite * sprite){
	
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );
	bool dieFrom = this->GetRiverDie();

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenFallAnmn, "ZenChanFalling",
						ZenChanDieFallingAnimator, zenFallAnmr, this->GetSprite() );
	zenFallAnmr->SetRiverDie(dieFrom);

	this->GetSprite()->AddStopFallingListener(zenFallAnmr);
	START_ANIMATOR( zenFallAnmr, this->GetSprite(), zenFallAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}

////////////////ZenChanDieFallingAnimtor

ZenChanDieFallingAnimator::ZenChanDieFallingAnimator(){}

void ZenChanDieFallingAnimator::RegistCollitions(Sprite *spr){
	
}

void ZenChanDieFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );
	bool dieFrom = this->GetRiverDie();

	INIT_NEW_INSTANCE_WITH_SPRITE(	MovingPathAnimation, zenStandAnmn, "ZenChanDie",
					ZenChanDieAnimator, zenStandAnmr, this->GetSprite() );	
	zenStandAnmr->SetRiverDie(dieFrom);
	
	START_ANIMATOR( zenStandAnmr, this->GetSprite(), zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}
