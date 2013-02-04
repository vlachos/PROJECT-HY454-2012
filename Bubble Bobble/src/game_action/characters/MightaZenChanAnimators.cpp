#include "MightaAnimator.h"
#include "ZenChanAnimator.h"
#include "GameActionUtilities.h"
#include "MemoryManage.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "CollisionChecker.h"
#include "ZenChanAnimator.h"
#include "FruitsAnimator.h"

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
	
}

void ZenChanFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenStandAnmn, this->GetSprite()?"ZenChanWalkLeft":"ZenChanWalkRight",
						ZenChanStandAnimator, zenStandAnmr, this->GetSprite() );	
	
	zenStandAnmr->RegistCollitions(this->GetSprite());

	START_ANIMATOR( zenStandAnmr, this->GetSprite(), zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}


////////////////ZenChanJumpAnimator
ZenChanJumpAnimator::ZenChanJumpAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void ZenChanJumpAnimator::RegistCollitions(Sprite *spr){
	
}

void ZenChanJumpAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	ZenChanJumpAnimator * _this = (ZenChanJumpAnimator*)args;
	DASSERT( anim==_this );

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	FrameRangeAnimation *fra= (FrameRangeAnimation*)AnimationsParser::GetAnimation("ZenChanFalling");
	Sprite *n_sprite=new Sprite(_this->GetSprite()->GetX(),_this->GetSprite()->GetY(),
		_this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm(_this->GetSprite()->GoesLeft()?"ZenChanWalkLeft":"ZenChanWalkRight"), 
						Terrain::GetActionLayer(), _this->GetSprite()->GoesLeft());

	ZenChanFallingAnimator *frtor=new ZenChanFallingAnimator();
	n_sprite->AddStopFallingListener(frtor);

	frtor->RegistCollitions(n_sprite);

	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( _this );

}

//////////////////////////////ZenChanAngryStandAnimator
ZenChanAngryStandAnimator::ZenChanAngryStandAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void ZenChanAngryStandAnimator::RegistCollitions(Sprite *spr){
	
}

void ZenChanAngryStandAnimator::OnFinishCallback(Animator*, void*){}


////////////////////////////ZenChanAngryWalkingAnimator
ZenChanAngryWalkingAnimator::ZenChanAngryWalkingAnimator(){
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void ZenChanAngryWalkingAnimator::RegistCollitions(Sprite *spr){
	
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
	
}

void ZenChanAngryFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenStandAnmn, this->GetSprite()?"ZenChanAngryWalkLeft":"ZenChanAngryWalkRight",
						ZenChanAngryStandAnimator, zenStandAnmr, this->GetSprite() );	
	
	zenStandAnmr->RegistCollitions(this->GetSprite());

	START_ANIMATOR( zenStandAnmr, this->GetSprite(), zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}

///////////////////////////ZenChanAngryJumpAnimator
ZenChanAngryJumpAnimator::ZenChanAngryJumpAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void ZenChanAngryJumpAnimator::RegistCollitions(Sprite *spr){
	
}

void ZenChanAngryJumpAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	ZenChanAngryJumpAnimator * _this = (ZenChanAngryJumpAnimator*)args;
	DASSERT( anim==_this );

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	FrameRangeAnimation *fra= (FrameRangeAnimation*)AnimationsParser::GetAnimation("ZenChanAngryFalling");
	Sprite *n_sprite=new Sprite(_this->GetSprite()->GetX(),_this->GetSprite()->GetY(),
		_this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm(_this->GetSprite()->GoesLeft()?"ZenChanAngryWalkLeft":"ZenChanAngryWalkRight"), 
						Terrain::GetActionLayer(), _this->GetSprite()->GoesLeft());

	ZenChanAngryFallingAnimator *frtor=new ZenChanAngryFallingAnimator();
	n_sprite->AddStopFallingListener(frtor);

	frtor->RegistCollitions(n_sprite);

	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( _this );
}

////////////////ZenChanDieAnimator////////die for both angry and normal
ZenChanDieAnimator::ZenChanDieAnimator(){
	this->SetOnFinish( OnFinishCallback, this );
}

void ZenChanDieAnimator::RegistCollitions(Sprite *spr){

}

void ZenChanDieAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim == args && anim );
	ZenChanDieAnimator* _this = (ZenChanDieAnimator*) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );

	MovingAnimation* mva=(MovingAnimation*)AnimationsParser::GetAnimation("Orange");
	Sprite *n_sprite=new Sprite(_this->GetSprite()->GetX(),_this->GetSprite()->GetY(),
		_this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("Orange"), 
						Terrain::GetActionLayer(), _this->GetSprite()->GoesLeft());
	OrangeAnimator *ban=new OrangeAnimator();

	ban->RegistCollitions(n_sprite);

	START_ANIMATOR( ban, n_sprite, mva, GetGameTime() );

}



/////////////////////////////////////////////////MigntaAnimator////////////////////////////////////////////////////

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
						ZenChanStandAnimator, zenStandAnmr, _this->GetSprite() );

	zenStandAnmr->RegistCollitions(_this->GetSprite());

	START_ANIMATOR( zenStandAnmr, _this->GetSprite(), zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE(_this );
}


////////////////MightaFallingAnimator
MightaFallingAnimator::MightaFallingAnimator(){}

void MightaFallingAnimator::RegistCollitions(Sprite *spr){
	
}

void MightaFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenStandAnmn, this->GetSprite()?"MightaWalkLeft":"MightaWalkRight",
						MightaStandAnimator, zenStandAnmr, this->GetSprite() );	
	zenStandAnmr->RegistCollitions(this->GetSprite());

	START_ANIMATOR( zenStandAnmr, this->GetSprite(), zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}


////////////////MightaJumpAnimator
MightaJumpAnimator::MightaJumpAnimator(){
	this->SetOnFinish( OnFinishCallback, (void*)this );
}

void MightaJumpAnimator::RegistCollitions(Sprite *spr){
	
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

/////////////////////////////////////Migta Angry Animator

////////////////MigntaAngryStandAnimator
MightaAngryStandAnimator::MightaAngryStandAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void MightaAngryStandAnimator::RegistCollitions(Sprite *spr){
	
}

void MightaAngryStandAnimator::OnFinishCallback(Animator* anim, void* args){}

////////////////MightaWalkingAnimator
MightaAngryWalkingAnimator::MightaAngryWalkingAnimator(void) {
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void MightaAngryWalkingAnimator::RegistCollitions(Sprite *spr){
	
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


////////////////MightaFallingAnimator
MightaAngryFallingAnimator::MightaAngryFallingAnimator(){}

void MightaAngryFallingAnimator::RegistCollitions(Sprite *spr){
	
}

void MightaAngryFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenStandAnmn, this->GetSprite()?"MightaAngryWalkLeft":"MightaAngryWalkRight",
						MightaAngryStandAnimator, zenStandAnmr, this->GetSprite() );	
	
	zenStandAnmr->RegistCollitions(this->GetSprite());

	START_ANIMATOR( zenStandAnmr, this->GetSprite(), zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}


////////////////MightaJumpAnimator
MightaAngryJumpAnimator::MightaAngryJumpAnimator(){
	this->SetOnFinish( OnFinishCallback, (void*)this );
}

void MightaAngryJumpAnimator::RegistCollitions(Sprite *spr){
	
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

	MovingAnimation* mva=(MovingAnimation*)AnimationsParser::GetAnimation("Peach");
	Sprite *n_sprite=new Sprite(_this->GetSprite()->GetX(),_this->GetSprite()->GetY(),
		_this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("Peach"), 
						Terrain::GetActionLayer(), _this->GetSprite()->GoesLeft());
	PeachAnimator *ban=new PeachAnimator();

	ban->RegistCollitions(n_sprite);

	START_ANIMATOR( ban, n_sprite, mva, GetGameTime() );
}

