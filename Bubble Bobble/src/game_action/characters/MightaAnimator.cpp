#include "MightaAnimator.h"
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



////////////////////////////////////////////////MigntaAnimator////////////////////////////////////////////////////

////////////////MigntaStandAnimator
MightaStandAnimator::MightaStandAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void MightaStandAnimator::RegistCollitions(Sprite *spr){
	
}

void MightaStandAnimator::OnFinishCallback(Animator* anim, void* args){}

////////////////MightaWalkingAnimator
MightaWalkingAnimator::MightaWalkingAnimator(void) {
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void MightaWalkingAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr,bubStandAnimator_t,bubJumpAnimator_t,BubAnimatorActions::OnCollisionWithEnemy);
}

void MightaWalkingAnimator::OnStartFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenFallAnmn, "MightaFalling",
						MightaFallingAnimator, zenFallAnmr, this->GetSprite() );

	this->GetSprite()->AddStopFallingListener(zenFallAnmr);
	zenFallAnmr->RegistCollitions(this->GetSprite());

	START_ANIMATOR( zenFallAnmr, this->GetSprite(), zenFallAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}


void MightaWalkingAnimator::OnFinishCallback(Animator* animr, void* args){
	DASSERT( animr && args);
	MightaWalkingAnimator* _this = (MightaWalkingAnimator*)args;
	DASSERT( animr ==_this );
	DASSERT( _this->GetAnimation() && _this->GetSprite());

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenStandAnmn, "MightaStand",
						MightaStandAnimator, zenStandAnmr, _this->GetSprite() );

	zenStandAnmr->RegistCollitions(_this->GetSprite());

	START_ANIMATOR( zenStandAnmr, _this->GetSprite(), zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE(_this );
}


////////////////MightaFallingAnimator
MightaFallingAnimator::MightaFallingAnimator(){}

void MightaFallingAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr,bubStandAnimator_t,bubJumpAnimator_t,BubAnimatorActions::OnCollisionWithEnemy);
}

void MightaFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenStandAnmn, this->GetSprite()->GoesLeft()?"MightaWalkLeft":"MightaWalkRight",
						MightaWalkingAnimator, zenStandAnmr, this->GetSprite() );	
	zenStandAnmr->RegistCollitions(this->GetSprite());
	this->GetSprite()->AddStartFallingListener( zenStandAnmr );
	START_ANIMATOR( zenStandAnmr, this->GetSprite(), zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}


////////////////MightaJumpAnimator
MightaJumpAnimator::MightaJumpAnimator(){
	this->SetOnFinish( OnFinishCallback, (void*)this );
}

void MightaJumpAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr,bubStandAnimator_t,bubJumpAnimator_t,BubAnimatorActions::OnCollisionWithEnemy);
}

void MightaJumpAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	MightaJumpAnimator * _this = (MightaJumpAnimator*)args;
	DASSERT( anim==_this );

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	FrameRangeAnimation *fra= (FrameRangeAnimation*)AnimationsParser::GetAnimation("MightaFalling");
	Sprite *n_sprite=new Sprite(_this->GetSprite()->GetX(),_this->GetSprite()->GetY(),
		_this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm(_this->GetSprite()->GoesLeft()?"MightaWalkLeft":"MightaWalkRight"), 
						Terrain::GetActionLayer(), _this->GetSprite()->GoesLeft());

	MightaFallingAnimator *frtor=new MightaFallingAnimator();
	n_sprite->AddStopFallingListener(frtor);

	frtor->RegistCollitions(n_sprite);

	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( _this );


}

MightaThrowFireBallAnimator::MightaThrowFireBallAnimator(){
	this->SetOnFinish( OnFinishCallback, (void*)this );
}

void MightaThrowFireBallAnimator::RegistCollitions(Sprite *spr){
	
}

void MightaThrowFireBallAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	MightaThrowFireBallAnimator * _this = (MightaThrowFireBallAnimator*)args;
	DASSERT( anim==_this );

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	FrameRangeAnimation *fra= (FrameRangeAnimation*)AnimationsParser::GetAnimation(_this->GetSprite()->GoesLeft()?"MightaWalkLeft":"MightaWalkRight");
	Sprite *n_sprite=new Sprite(_this->GetSprite()->GetX(),_this->GetSprite()->GetY(),
		_this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("MightaWalk"), 
						Terrain::GetActionLayer(), _this->GetSprite()->GoesLeft());

	MightaWalkingAnimator *frtor=new MightaWalkingAnimator();
	n_sprite->AddStartFallingListener(frtor);

	frtor->RegistCollitions(n_sprite);

	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( _this );


}

/////////////////////////////////////Migta Angry Animator

////////////////MigntaAngryStandAnimator
MightaAngryStandAnimator::MightaAngryStandAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void MightaAngryStandAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr,bubStandAnimator_t,bubJumpAnimator_t,BubAnimatorActions::OnCollisionWithEnemy);
}

void MightaAngryStandAnimator::OnFinishCallback(Animator* anim, void* args){}

////////////////MightaAngryWalkingAnimator
MightaAngryWalkingAnimator::MightaAngryWalkingAnimator(void) {
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void MightaAngryWalkingAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr,bubStandAnimator_t,bubJumpAnimator_t,BubAnimatorActions::OnCollisionWithEnemy);
}

void MightaAngryWalkingAnimator::OnStartFalling(Sprite * sprite){
	
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenFallAnmn, "MightaAngryFalling",
						MightaAngryFallingAnimator, zenFallAnmr, this->GetSprite() );

	this->GetSprite()->AddStopFallingListener(zenFallAnmr);
	zenFallAnmr->RegistCollitions(this->GetSprite());

	START_ANIMATOR( zenFallAnmr, this->GetSprite(), zenFallAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}


void MightaAngryWalkingAnimator::OnFinishCallback(Animator* animr, void* args){
	DASSERT( animr && args);
	MightaAngryWalkingAnimator* _this = (MightaAngryWalkingAnimator*)args;
	DASSERT( animr ==_this );
	DASSERT( _this->GetAnimation() && _this->GetSprite());

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenStandAnmn, "MightaAngryStand",
						MightaAngryStandAnimator, zenStandAnmr, _this->GetSprite() );

	zenStandAnmr->RegistCollitions(_this->GetSprite());

	START_ANIMATOR( zenStandAnmr, _this->GetSprite(), zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE(_this );
}


////////////////MightaAngryFallingAnimator
MightaAngryFallingAnimator::MightaAngryFallingAnimator(){}

void MightaAngryFallingAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr,bubStandAnimator_t,bubJumpAnimator_t,BubAnimatorActions::OnCollisionWithEnemy);
}

void MightaAngryFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenStandAnmn, this->GetSprite()->GoesLeft()?"MightaAngryWalkLeft":"MightaAngryWalkRight",
						MightaAngryWalkingAnimator, zenStandAnmr, this->GetSprite() );	
	
	zenStandAnmr->RegistCollitions(this->GetSprite());
	this->GetSprite()->AddStartFallingListener( zenStandAnmr );
	START_ANIMATOR( zenStandAnmr, this->GetSprite(), zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}


////////////////MightaAngryJumpAnimator
MightaAngryJumpAnimator::MightaAngryJumpAnimator(){
	this->SetOnFinish( OnFinishCallback, (void*)this );
}

void MightaAngryJumpAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr,bubStandAnimator_t,bubJumpAnimator_t,BubAnimatorActions::OnCollisionWithEnemy);
}

void MightaAngryJumpAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	MightaAngryJumpAnimator * _this = (MightaAngryJumpAnimator*)args;
	DASSERT( anim==_this );

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	FrameRangeAnimation *fra= (FrameRangeAnimation*)AnimationsParser::GetAnimation("MightaAngryFalling");
	Sprite *n_sprite=new Sprite(_this->GetSprite()->GetX(),_this->GetSprite()->GetY(),
		_this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm(_this->GetSprite()->GoesLeft()?"MightaAngryWalkLeft":"MightaAngryWalkRight"), 
						Terrain::GetActionLayer(), _this->GetSprite()->GoesLeft());

	MightaAngryFallingAnimator *frtor=new MightaAngryFallingAnimator();
	n_sprite->AddStopFallingListener(frtor);

	frtor->RegistCollitions(n_sprite);

	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( _this );


}
////////////////MightaDieAnimator
MightaDieAnimator::MightaDieAnimator(){
	this->SetOnFinish( OnFinishCallback, (void*)this );
}

void MightaDieAnimator::RegistCollitions(Sprite *spr){
}

void MightaDieAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim == args && anim );
	MightaDieAnimator* _this = (MightaDieAnimator*) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );

	FruitsAnimators::StartFruitAnimator(BubbleLogic::GetFruitType(), _this->GetSprite()->GetX(), _this->GetSprite()->GetY());
}

void MightaDieAnimator::OnStartFalling(Sprite * sprite){
	
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenFallAnmn, "MightaFalling",
						MightaDieFallingAnimator, zenFallAnmr, this->GetSprite() );

	this->GetSprite()->AddStopFallingListener(zenFallAnmr);
	START_ANIMATOR( zenFallAnmr, this->GetSprite(), zenFallAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}

/////////////////MightaAngryThrowFireballAnimator
MightaAngryThrowFireBallAnimator::MightaAngryThrowFireBallAnimator(){
	this->SetOnFinish( OnFinishCallback, (void*)this );
}

void MightaAngryThrowFireBallAnimator::RegistCollitions(Sprite *spr){
	
}

void MightaAngryThrowFireBallAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	MightaAngryThrowFireBallAnimator * _this = (MightaAngryThrowFireBallAnimator*)args;
	DASSERT( anim==_this );

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	FrameRangeAnimation *fra= (FrameRangeAnimation*)AnimationsParser::GetAnimation(_this->GetSprite()->GoesLeft()?"MightaAngryWalkLeft":"MightaAngryWalkRight");
	Sprite *n_sprite=new Sprite(_this->GetSprite()->GetX(),_this->GetSprite()->GetY(),
		_this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("MightaAngry"), 
						Terrain::GetActionLayer(), _this->GetSprite()->GoesLeft());

	MightaAngryWalkingAnimator *frtor=new MightaAngryWalkingAnimator();
	n_sprite->AddStartFallingListener(frtor);

	frtor->RegistCollitions(n_sprite);

	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( _this );


}

////////////////MightaDieFallingAnimtor

MightaDieFallingAnimator::MightaDieFallingAnimator(){}

void MightaDieFallingAnimator::RegistCollitions(Sprite *spr){
	
}

void MightaDieFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	MovingPathAnimation, zenStandAnmn, "MightaDie",
					MightaDieAnimator, zenStandAnmr, this->GetSprite() );	
	
	START_ANIMATOR( zenStandAnmr, this->GetSprite(), zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}