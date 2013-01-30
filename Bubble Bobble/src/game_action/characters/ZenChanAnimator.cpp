#include "GameActionUtilities.h"
#include "MemoryManage.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "CollisionChecker.h"
#include "ZenChanAnimator.h"


////////////////ZenChanStandAnimator
ZenChanStandAnimator::ZenChanStandAnimator(){}

void ZenChanStandAnimator::OnFinishCallback(Animator* anim, void* args){}

void ZenChanStandAnimator::OnStartFalling(Sprite* sprite){}


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

