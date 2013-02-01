#include "GameActionUtilities.h"
#include "MemoryManage.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "CollisionChecker.h"
#include "BarronVonBlubaAnimator.h"

////////////////BaronVonBlubaStandAnimator
BaronVonBlubaStandAnimator::BaronVonBlubaStandAnimator(){}

void BaronVonBlubaStandAnimator::OnCollisionWithEnemy(Sprite* s1, Sprite* s2, void* args){
	DASSERT(args);
	BaronVonBlubaStandAnimator* _this = (BaronVonBlubaStandAnimator*)args;
	DESTROY_ANIMATOR(_this);
}

void BaronVonBlubaStandAnimator::OnFinishCallback(Animator* animr, void* args){}

////////////////BaronVonBlubaRushAnimator
BaronVonBlubaRushAnimator::BaronVonBlubaRushAnimator(){}

void BaronVonBlubaRushAnimator::OnCollisionWithEnemy(Sprite* s1, Sprite* s2, void* args){
	DASSERT(args);
	BaronVonBlubaRushAnimator* _this = (BaronVonBlubaRushAnimator*)args;
	DESTROY_ANIMATOR(_this);
}

void BaronVonBlubaRushAnimator::OnFinishCallback(Animator* animr, void* args){
	DASSERT( animr && args);
	BaronVonBlubaRushAnimator* _this = (BaronVonBlubaRushAnimator*)args;
	DASSERT( animr ==_this );
	DASSERT( _this->GetAnimation() && _this->GetSprite());

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, baronStandAnmn, "BarronVonBlubaStand",
						BaronVonBlubaStandAnimator, baronStandAnmr, _this->GetSprite() );

	baronStandAnmr->SetOnFinish(BaronVonBlubaStandAnimator::OnFinishCallback, 0);

	//collision register

	START_ANIMATOR( baronStandAnmr, _this->GetSprite(), baronStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR(_this );
}