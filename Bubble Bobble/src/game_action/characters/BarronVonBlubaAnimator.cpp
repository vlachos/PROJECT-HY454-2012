#include "GameActionUtilities.h"
#include "MemoryManage.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "CollisionChecker.h"
#include "BarronVonBlubaAnimator.h"
#include "BubblesAnimator.h"
#include "TickAnimation.h"
#include "TimerTickAnimator.h"

void BaronVonBlubaAnimatorActions::StartBaronVonBludaAnimator(void* args){
	MovingPathAnimation *mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("BarronVonBlubaRushRight");
	Sprite *sprite = new Sprite(
								50,
								100,
								false,						
								AnimationFilmHolder::GetFilm( "BaronVonBlubba" ), 
								Terrain::GetActionLayer(), 
								false
							);
	sprite->SetOnDrugs(true);
	BaronVonBlubaRushAnimator* bvbrar = new BaronVonBlubaRushAnimator();
	bvbrar->RegistCollitions(sprite);
	START_ANIMATOR(bvbrar, sprite, mpa, GetGameTime() );
}

void BaronVonBlubaAnimatorActions::StartHurryUpAnimator(void* args){
	Sprite* newSprite = 
		new Sprite(200, 50, false, AnimationFilmHolder::GetFilm("HurryUp"), Terrain::GetActionLayer(),true);
	newSprite->SetOnDrugs(true);
	MovingPathAnimation* mpa = (MovingPathAnimation*)AnimationsParser::GetAnimation("HurryUp");
	HurryUpAnimator* hua = new HurryUpAnimator();
	START_ANIMATOR( hua, newSprite, mpa, GetGameTime() );
}

////////////////////////HurryUpAnimator

HurryUpAnimator::HurryUpAnimator(){
	this->SetOnFinish(OnFinishCallback, this);
}

void HurryUpAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim==args );
	HurryUpAnimator* _this = (HurryUpAnimator*) anim;
	REMOVE_FROM_ACTION_ANIMATOR( _this );

	TickAnimation *ta = (TickAnimation*) AnimationsParser::GetAnimation("BarronVonBlubaStart");
	ta->SetTickAction( BaronVonBlubaAnimatorActions::StartBaronVonBludaAnimator, 0 );
	TimerTickAnimator* ttar = new TimerTickAnimator(ta);
	ttar->SetOnFinish(BubblesAnimatorActions::OnTickTimerFinishCallback, 0);
	START_TIME_ANIMATOR(ttar, GetGameTime());

	DESTROY_ANIMATOR(_this);
}

////////////////BaronVonBlubaStandAnimator
BaronVonBlubaStandAnimator::BaronVonBlubaStandAnimator(){
	this->SetOnFinish(OnFinishCallback, this);
}

void BaronVonBlubaStandAnimator::OnCollisionWithEnemy(Sprite* s1, Sprite* s2, void* args){
	DASSERT(args);
	BaronVonBlubaStandAnimator* _this = (BaronVonBlubaStandAnimator*)args;
	DESTROY_ANIMATOR(_this);
}

void BaronVonBlubaStandAnimator::OnFinishCallback(Animator* animr, void* args){}

////////////////BaronVonBlubaRushAnimator
BaronVonBlubaRushAnimator::BaronVonBlubaRushAnimator(){
	this->SetOnFinish(OnFinishCallback, this);
}

void BaronVonBlubaRushAnimator::OnCollisionWithEnemy(Sprite* s1, Sprite* s2, void* args){
	DASSERT(args);
	BaronVonBlubaRushAnimator* _this = (BaronVonBlubaRushAnimator*)args;
	DESTROY_ANIMATOR(_this);
}

void BaronVonBlubaRushAnimator::OnFinishCallback(Animator* animr, void* args){
	DASSERT( animr &&  animr == args);
	BaronVonBlubaRushAnimator* _this = (BaronVonBlubaRushAnimator*)args;
	DASSERT( _this->GetAnimation() && _this->GetSprite());

	REMOVE_FROM_ACTION_ANIMATOR( _this );
	/*
	INIT_NEW_INSTANCE_WITH_SPRITE(	FrameRangeAnimation, baronStandAnmn, "BarronVonBlubaStand",
						BaronVonBlubaStandAnimator, baronStandAnmr, _this->GetSprite() );

	baronStandAnmr->SetOnFinish(BaronVonBlubaStandAnimator::OnFinishCallback, 0);

	//collision register

	START_ANIMATOR( baronStandAnmr, _this->GetSprite(), baronStandAnmn, GetGameTime() );*/
	DESTROY_ANIMATOR(_this );
}

void BaronVonBlubaRushAnimator::RegistCollitions(Sprite* spr){

}