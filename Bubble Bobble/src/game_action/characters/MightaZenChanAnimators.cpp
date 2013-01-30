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

//////////////////////////////////////////////////////ZenChanAnimators//////////////////////////////////////////////

////////////////ZenChanStandAnimator
ZenChanStandAnimator::ZenChanStandAnimator(){}

void ZenChanStandAnimator::OnFinishCallback(Animator* anim, void* args){}

void ZenChanStandAnimator::OnStartFalling(Sprite* sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenFallAnmn, "ZenChanFalling",
						ZenChanFallingAnimator, zenFallAnmr, newSprite, this->GetSprite() );

	newSprite->AddStopFallingListener(zenFallAnmr);

	START_ANIMATOR( zenFallAnmr, newSprite, zenFallAnmn, GetGameTime() );
	DESTROY_ANIMATOR( this );
}


////////////////ZenChanWalkingAnimator
ZenChanWalkingAnimator::ZenChanWalkingAnimator(void) {
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void ZenChanWalkingAnimator::OnStartFalling(Sprite * sprite){
	
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenFallAnmn, "ZenChanFalling",
						ZenChanFallingAnimator, zenFallAnmr, newSprite, this->GetSprite() );

	newSprite->AddStopFallingListener(zenFallAnmr);

	START_ANIMATOR( zenFallAnmr, newSprite, zenFallAnmn, GetGameTime() );
	DESTROY_ANIMATOR( this );
}


void ZenChanWalkingAnimator::OnFinishCallback(Animator* animr, void* args){
	DASSERT( animr && args);
	ZenChanWalkingAnimator* _this = (ZenChanWalkingAnimator*)args;
	DASSERT( animr ==_this );
	DASSERT( _this->GetAnimation() && _this->GetSprite());

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenStandAnmn, "ZenChanStand",
						ZenChanStandAnimator, zenStandAnmr, newSprite, _this->GetSprite() );
	zenStandAnmr->SetOnFinish(ZenChanStandAnimator::OnFinishCallback, 0);

	//collision register

	START_ANIMATOR( zenStandAnmr, newSprite, zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR(_this );
}


////////////////ZenChanFallingAnimator
ZenChanFallingAnimator::ZenChanFallingAnimator(){}

void ZenChanFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenStandAnmn, "ZenChanStand",
						ZenChanStandAnimator, zenStandAnmr, newSprite, this->GetSprite() );	
	//collision register

	START_ANIMATOR( zenStandAnmr, newSprite, zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR( this );
}


////////////////ZenChanJumpAnimator
ZenChanJumpAnimator::ZenChanJumpAnimator(){}

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

	//Here register

	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( _this );

}

////////////////ZenChanDieAnimator
ZenChanDieAnimator::ZenChanDieAnimator(){

}

void ZenChanDieAnimator::OnFinishCallback(Animator* anim, void* args){


}



/////////////////////////////////////////////////MigntaAnimator////////////////////////////////////////////////////

////////////////MigntaStandAnimator
MightaStandAnimator::MightaStandAnimator(){}

void MightaStandAnimator::OnFinishCallback(Animator* anim, void* args){}

void MightaStandAnimator::OnStartFalling(Sprite* sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenFallAnmn, "MightaFalling",
						ZenChanFallingAnimator, zenFallAnmr, newSprite, this->GetSprite() );

	newSprite->AddStopFallingListener(zenFallAnmr);

	START_ANIMATOR( zenFallAnmr, newSprite, zenFallAnmn, GetGameTime() );
	DESTROY_ANIMATOR( this );
}


////////////////MightaWalkingAnimator
MightaWalkingAnimator::MightaWalkingAnimator(void) {
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void MightaWalkingAnimator::OnStartFalling(Sprite * sprite){
	
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenFallAnmn, "MightaFalling",
						ZenChanFallingAnimator, zenFallAnmr, newSprite, this->GetSprite() );

	newSprite->AddStopFallingListener(zenFallAnmr);

	START_ANIMATOR( zenFallAnmr, newSprite, zenFallAnmn, GetGameTime() );
	DESTROY_ANIMATOR( this );
}


void MightaWalkingAnimator::OnFinishCallback(Animator* animr, void* args){
	DASSERT( animr && args);
	ZenChanWalkingAnimator* _this = (ZenChanWalkingAnimator*)args;
	DASSERT( animr ==_this );
	DASSERT( _this->GetAnimation() && _this->GetSprite());

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenStandAnmn, "MightaStand",
						ZenChanStandAnimator, zenStandAnmr, newSprite, _this->GetSprite() );
	zenStandAnmr->SetOnFinish(ZenChanStandAnimator::OnFinishCallback, 0);

	//collision register

	START_ANIMATOR( zenStandAnmr, newSprite, zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR(_this );
}


////////////////ZenChanFallingAnimator
MightaFallingAnimator::MightaFallingAnimator(){}

void MightaFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, zenStandAnmn, "MightaStand",
						ZenChanStandAnimator, zenStandAnmr, newSprite, this->GetSprite() );	
	//collision register

	START_ANIMATOR( zenStandAnmr, newSprite, zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR( this );
}


////////////////ZenChanJumpAnimator
MightaJumpAnimator::MightaJumpAnimator(){
	
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

	//Here register

	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( _this );


}

////////////////ZenChanDieAnimator
MightaDieAnimator::MightaDieAnimator(){

}

void MightaDieAnimator::OnFinishCallback(Animator* anim, void* args){


}

