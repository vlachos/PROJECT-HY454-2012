#include "GameActionUtilities.h"
#include "MemoryManage.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "CollisionChecker.h"
#include "MightaAnimator.h"


////////////////MightaStandAnimator

MightaStandAnimator::MightaStandAnimator(){}

void MightaStandAnimator::OnFinishCallback(Animator* anim, void* args){}

void MightaStandAnimator::OnStartFalling(Sprite* sprite){}


////////////////MightaWalkingAnimator

MightaWalkingAnimator::MightaWalkingAnimator(void) {
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void MightaWalkingAnimator::OnStartFalling(Sprite * sprite){
	
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, mightaFallAnmn, "MightaFalling",
						MightaFallingAnimator, mightaFallAnmr, newSprite, this->GetSprite() );

	newSprite->AddStopFallingListener(mightaFallAnmr);

	//collision check register
	
	START_ANIMATOR( mightaFallAnmr, newSprite, mightaFallAnmn, GetGameTime() );
	DESTROY_ANIMATOR( this );
}


void MightaWalkingAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	MightaWalkingAnimator * _this = (MightaWalkingAnimator*)args;
	DASSERT( anim==_this );
	DASSERT( _this->GetAnimation() && _this->GetSprite());

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, mightaStandAnmn, "MightaChanStand",
						MightaStandAnimator, mightaStandAnmr, newSprite, _this->GetSprite() );

	mightaStandAnmr->SetOnFinish(MightaStandAnimator::OnFinishCallback, 0);

		//collision register

	START_ANIMATOR( mightaStandAnmr, newSprite, mightaStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( _this );
}


////////////////MightaFallingAnimator

MightaFallingAnimator::MightaFallingAnimator(){}

void MightaFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, mightaStandAnmn, "MightaStand",
						MightaStandAnimator, mightaStandAnmr, newSprite, this->GetSprite() );	

		//collision register

	START_ANIMATOR( mightaStandAnmr, newSprite, mightaStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}


////////////////MightaJumpAnimator
