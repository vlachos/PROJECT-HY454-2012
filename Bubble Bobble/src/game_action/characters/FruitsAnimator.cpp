#include "FruitsAnimator.h"
#include "GameActionUtilities.h"
#include "AnimatorHolder.h"
#include "CollisionChecker.h"


//////////////BananaAnimator
BananaAnimator::BananaAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void BananaAnimator::RegistCollitions(Sprite* sprite){
	CollisionChecker::Register(sprite,bubStandAnimator_t,bubJumpAnimator_t, this, BananaAnimator::OnCollisionWithBub);
}

void BananaAnimator::OnCollisionWithBub(Sprite *Bub, Sprite *Fruit, void *args){std::cout<<"hndg\n";
	//DASSERT( Bub && Fruit && args);
	BananaAnimator * _this = (BananaAnimator*)args;
	//DASSERT(_this->GetSprite()==Fruit);
	REMOVE_FROM_ACTION_ANIMATOR(_this);

	DESTROY_ANIMATOR( _this );
}

void BananaAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BananaAnimator * _this = (BananaAnimator*)args;
	DASSERT( _this->GetAnimation() && _this->GetSprite() && anim==_this );
	REMOVE_FROM_ACTION_ANIMATOR(_this);
	
	DESTROY_ANIMATOR( _this );
}

//////////////OrangeAnimator
OrangeAnimator::OrangeAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void OrangeAnimator::RegistCollitions(Sprite* sprite){
	CollisionChecker::Register(sprite,bubStandAnimator_t,bubJumpAnimator_t, this, OrangeAnimator::OnCollisionWithBub);
}

void OrangeAnimator::OnCollisionWithBub(Sprite *Bub, Sprite *Fruit, void *args){
	DASSERT( Bub && Fruit && args);
	OrangeAnimator * _this = (OrangeAnimator*)args;
	DASSERT(_this->GetSprite()==Fruit);
	REMOVE_FROM_ACTION_ANIMATOR(_this);

	DESTROY_ANIMATOR( _this );
}

void OrangeAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	OrangeAnimator * _this = (OrangeAnimator*)args;
	DASSERT( _this->GetAnimation() && _this->GetSprite() && anim==_this );
	REMOVE_FROM_ACTION_ANIMATOR(_this);
	
	DESTROY_ANIMATOR( _this );
}

/////////////PeachAnimator
PeachAnimator::PeachAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void PeachAnimator::RegistCollitions(Sprite* sprite){
	CollisionChecker::Register(sprite,bubStandAnimator_t,bubJumpAnimator_t, this, PeachAnimator::OnCollisionWithBub);
}

void PeachAnimator::OnCollisionWithBub(Sprite *Bub, Sprite *Fruit, void *args){
	DASSERT( Bub && Fruit && args);
	PeachAnimator * _this = (PeachAnimator*)args;
	DASSERT(_this->GetSprite()==Fruit);
	REMOVE_FROM_ACTION_ANIMATOR(_this);

	DESTROY_ANIMATOR( _this );
}

void PeachAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	PeachAnimator * _this = (PeachAnimator*)args;
	DASSERT( _this->GetAnimation() && _this->GetSprite() && anim==_this );
	REMOVE_FROM_ACTION_ANIMATOR(_this);
	
	DESTROY_ANIMATOR( _this );
}

/////////////WaterMelonAnimator
WaterMelonAnimator::WaterMelonAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void WaterMelonAnimator::RegistCollitions(Sprite* sprite){
	CollisionChecker::Register(sprite,bubStandAnimator_t,bubJumpAnimator_t, this, WaterMelonAnimator::OnCollisionWithBub);
}

void WaterMelonAnimator::OnCollisionWithBub(Sprite *Bub, Sprite *Fruit, void *args){
	DASSERT( Bub && Fruit && args);
	WaterMelonAnimator * _this = (WaterMelonAnimator*)args;
	DASSERT(_this->GetSprite()==Fruit);
	REMOVE_FROM_ACTION_ANIMATOR(_this);

	DESTROY_ANIMATOR( _this );
}

void WaterMelonAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	WaterMelonAnimator * _this = (WaterMelonAnimator*)args;
	DASSERT( _this->GetAnimation() && _this->GetSprite() && anim==_this );
	REMOVE_FROM_ACTION_ANIMATOR(_this);
	
	DESTROY_ANIMATOR( _this );
}

////////////BlueDiamondAnimator
BlueDiamondAnimator::BlueDiamondAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void BlueDiamondAnimator::RegistCollitions(Sprite* sprite){
	CollisionChecker::Register(sprite,bubStandAnimator_t,bubJumpAnimator_t, this, BlueDiamondAnimator::OnCollisionWithBub);
}

void BlueDiamondAnimator::OnCollisionWithBub(Sprite *Bub, Sprite *Fruit, void *args){
	DASSERT( Bub && Fruit && args);
	BlueDiamondAnimator * _this = (BlueDiamondAnimator*)args;
	DASSERT(_this->GetSprite()==Fruit);
	REMOVE_FROM_ACTION_ANIMATOR(_this);

	DESTROY_ANIMATOR( _this );
}

void BlueDiamondAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BlueDiamondAnimator * _this = (BlueDiamondAnimator*)args;
	DASSERT( _this->GetAnimation() && _this->GetSprite() && anim==_this );
	REMOVE_FROM_ACTION_ANIMATOR(_this);
	
	DESTROY_ANIMATOR( _this );
}