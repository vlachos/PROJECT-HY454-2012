#include "PowerUpsAnimator.h"
#include "GameActionUtilities.h"
#include "AnimatorHolder.h"
#include "CollisionChecker.h"
#include "BubbleLogic.h"
#include "FruitsAnimator.h"


//////////////RedShoesAnimator
RedShoesAnimator::RedShoesAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void RedShoesAnimator::RegistCollitions(Sprite* sprite){
	CollisionChecker::Register(sprite,bubStandAnimator_t,bubJumpAnimator_t, this, RedShoesAnimator::OnCollisionWithBub);
}

void RedShoesAnimator::OnCollisionWithBub(Sprite *Bub, Sprite *Fruit, void *args){
	DASSERT( Bub && Fruit && args);
	RedShoesAnimator * _this = (RedShoesAnimator*)args;
	REMOVE_FROM_ACTION_ANIMATOR(_this);
	FruitsAnimators::StartScoreLabel( _this->GetSprite()->GetX(), _this->GetSprite()->GetY(), "ScoreLabel100");
	DESTROY_ANIMATOR( _this );
	BubbleLogic::BubRedShoesAcquired();
}

void RedShoesAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	RedShoesAnimator * _this = (RedShoesAnimator*)args;
	DASSERT( _this->GetAnimation() && _this->GetSprite() && anim==_this );
	REMOVE_FROM_ACTION_ANIMATOR(_this);
	
	DESTROY_ANIMATOR( _this );
}


//////////////YellowSweetAnimator
YellowSweetAnimator::YellowSweetAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void YellowSweetAnimator::RegistCollitions(Sprite* sprite){
	CollisionChecker::Register(sprite,bubStandAnimator_t,bubJumpAnimator_t, this, YellowSweetAnimator::OnCollisionWithBub);
}

void YellowSweetAnimator::OnCollisionWithBub(Sprite *Bub, Sprite *Fruit, void *args){
	DASSERT( Bub && Fruit && args);
	YellowSweetAnimator * _this = (YellowSweetAnimator*)args;
	REMOVE_FROM_ACTION_ANIMATOR(_this);
	FruitsAnimators::StartScoreLabel( _this->GetSprite()->GetX(), _this->GetSprite()->GetY(), "ScoreLabel100");
	DESTROY_ANIMATOR( _this );
	BubbleLogic::BubYellowSwtAcquired();
}

void YellowSweetAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	YellowSweetAnimator * _this = (YellowSweetAnimator*)args;
	DASSERT( _this->GetAnimation() && _this->GetSprite() && anim==_this );
	REMOVE_FROM_ACTION_ANIMATOR(_this);
	
	DESTROY_ANIMATOR( _this );
}

/////////////BlueSweetAnimator
BlueSweetAnimator::BlueSweetAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void BlueSweetAnimator::RegistCollitions(Sprite* sprite){
	CollisionChecker::Register(sprite,bubStandAnimator_t,bubJumpAnimator_t, this, BlueSweetAnimator::OnCollisionWithBub);
}

void BlueSweetAnimator::OnCollisionWithBub(Sprite *Bub, Sprite *Fruit, void *args){
	DASSERT( Bub && Fruit && args);
	BlueSweetAnimator * _this = (BlueSweetAnimator*)args;
	REMOVE_FROM_ACTION_ANIMATOR(_this);
	FruitsAnimators::StartScoreLabel( _this->GetSprite()->GetX(), _this->GetSprite()->GetY(), "ScoreLabel100");
	DESTROY_ANIMATOR( _this );
	BubbleLogic::BubBlueSwtAcquired();
}

void BlueSweetAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BlueSweetAnimator * _this = (BlueSweetAnimator*)args;
	DASSERT( _this->GetAnimation() && _this->GetSprite() && anim==_this );
	REMOVE_FROM_ACTION_ANIMATOR(_this);
	
	DESTROY_ANIMATOR( _this );
}

/////////////PurpleSweetAnimator
PurpleSweetAnimator::PurpleSweetAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void PurpleSweetAnimator::RegistCollitions(Sprite* sprite){
	CollisionChecker::Register(sprite,bubStandAnimator_t,bubJumpAnimator_t, this, PurpleSweetAnimator::OnCollisionWithBub);
}

void PurpleSweetAnimator::OnCollisionWithBub(Sprite *Bub, Sprite *Fruit, void *args){
	DASSERT( Bub && Fruit && args);
	PurpleSweetAnimator * _this = (PurpleSweetAnimator*)args;
	REMOVE_FROM_ACTION_ANIMATOR(_this);
	FruitsAnimators::StartScoreLabel( _this->GetSprite()->GetX(), _this->GetSprite()->GetY(), "ScoreLabel100");
	DESTROY_ANIMATOR( _this );
	BubbleLogic::BubPurpleSwtAcquired();
}

void PurpleSweetAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	PurpleSweetAnimator * _this = (PurpleSweetAnimator*)args;
	DASSERT( _this->GetAnimation() && _this->GetSprite() && anim==_this );
	REMOVE_FROM_ACTION_ANIMATOR(_this);
	
	DESTROY_ANIMATOR( _this );
}