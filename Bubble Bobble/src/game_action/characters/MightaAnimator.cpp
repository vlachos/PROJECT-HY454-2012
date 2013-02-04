#include "MightaAnimator.h"
#include "GameActionUtilities.h"
#include "MemoryManage.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "CollisionChecker.h"
#include "FruitsAnimator.h"
#include "BubbleLogic.h"

typedef void (*FruitSelector_t)(void* Animator);

static void CreateBananaAnimator(void* Animator){
	MightaDieAnimator* _this = (MightaDieAnimator*) Animator;

	MovingAnimation* mva=(MovingAnimation*)AnimationsParser::GetAnimation("Banana");
	Sprite *n_sprite=new Sprite(_this->GetSprite()->GetX(),_this->GetSprite()->GetY(),
		true,AnimationFilmHolder::GetFilm("Banana"), Terrain::GetActionLayer(), _this->GetSprite()->GoesLeft());
	
	BananaAnimator *ban=new BananaAnimator();
	ban->RegistCollitions(n_sprite);
	
	START_ANIMATOR( ban, n_sprite, mva, GetGameTime());
}

static void CreateOrangeAnimator(void* Animator){
	MightaDieAnimator* _this = (MightaDieAnimator*) Animator;

	MovingAnimation* mva=(MovingAnimation*)AnimationsParser::GetAnimation("Orange");
	Sprite *n_sprite=new Sprite(_this->GetSprite()->GetX(),_this->GetSprite()->GetY(),
		true,AnimationFilmHolder::GetFilm("Orange"), Terrain::GetActionLayer(), _this->GetSprite()->GoesLeft());
	
	OrangeAnimator *ban=new OrangeAnimator();
	ban->RegistCollitions(n_sprite);
	
	START_ANIMATOR( ban, n_sprite, mva, GetGameTime());
}

static void CreatePeachAnimator(void* Animator){
	MightaDieAnimator* _this = (MightaDieAnimator*) Animator;

	MovingAnimation* mva=(MovingAnimation*)AnimationsParser::GetAnimation("Peach");
	Sprite *n_sprite=new Sprite(_this->GetSprite()->GetX(),_this->GetSprite()->GetY(),
		true,AnimationFilmHolder::GetFilm("Peach"), Terrain::GetActionLayer(), _this->GetSprite()->GoesLeft());
	
	PeachAnimator *ban=new PeachAnimator();
	ban->RegistCollitions(n_sprite);
	
	START_ANIMATOR( ban, n_sprite, mva, GetGameTime());
}

static void CreateWaterMelonAnimator(void* Animator){
	MightaDieAnimator* _this = (MightaDieAnimator*) Animator;

	MovingAnimation* mva=(MovingAnimation*)AnimationsParser::GetAnimation("WaterMelon");
	Sprite *n_sprite=new Sprite(_this->GetSprite()->GetX(),_this->GetSprite()->GetY(),
		true,AnimationFilmHolder::GetFilm("WaterMelon"), Terrain::GetActionLayer(), _this->GetSprite()->GoesLeft());
	
	WaterMelonAnimator *ban=new WaterMelonAnimator();
	ban->RegistCollitions(n_sprite);
	
	START_ANIMATOR( ban, n_sprite, mva, GetGameTime());
}

static FruitSelector_t fruitSelector[]={
	0,
	CreateBananaAnimator,
	CreateOrangeAnimator,
	CreatePeachAnimator,
	CreateWaterMelonAnimator
};

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

	//ston asso 8elei na mpoun posoi psofisan
	fruitSelector[BubbleLogic::GetFruitType(1)](_this);
	
}