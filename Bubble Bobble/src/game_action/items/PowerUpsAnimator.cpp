#include "PowerUpsAnimator.h"
#include "GameActionUtilities.h"
#include "AnimatorHolder.h"
#include "CollisionChecker.h"
#include "BubbleLogic.h"
#include "FruitsAnimator.h"
#include "AnimationsParser.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"

void powerUpsAnimatorStart::startRedShoesAnimator(){
	Sprite* sprite = new Sprite(															
									BubbleLogic::GetPowerUpPosXY().first,					
									BubbleLogic::GetPowerUpPosXY().second,					
									true,													
									AnimationFilmHolder::GetFilm( "RedShoes" ),					
									Terrain::GetActionLayer(),								
									true													
								);															
	MovingAnimation* anim = (MovingAnimation*) AnimationsParser::GetAnimation( "RedShoes" );		
	RedShoesAnimator* type = new RedShoesAnimator();
	type->RegistCollitions(sprite);															
	START_ANIMATOR( type, sprite, anim, GetGameTime() )	;	
}

void powerUpsAnimatorStart::startYellowSweetAnimator(){
	Sprite* sprite = new Sprite(															
									BubbleLogic::GetPowerUpPosXY().first,					
									BubbleLogic::GetPowerUpPosXY().second,					
									true,													
									AnimationFilmHolder::GetFilm( "YellowSweet" ),					
									Terrain::GetActionLayer(),								
									true													
								);															
	MovingAnimation* anim = (MovingAnimation*) AnimationsParser::GetAnimation( "YellowSweet" );		
	RedShoesAnimator* type = new RedShoesAnimator();
	type->RegistCollitions(sprite);															
	START_ANIMATOR( type, sprite, anim, GetGameTime() )	;	
}

void powerUpsAnimatorStart::startBlueSweetAnimator(){
	Sprite* sprite = new Sprite(															
									BubbleLogic::GetPowerUpPosXY().first,					
									BubbleLogic::GetPowerUpPosXY().second,					
									true,													
									AnimationFilmHolder::GetFilm( "BlueSweet" ),					
									Terrain::GetActionLayer(),								
									true													
								);															
	MovingAnimation* anim = (MovingAnimation*) AnimationsParser::GetAnimation( "BlueSweet" );		
	BlueSweetAnimator* type = new BlueSweetAnimator();
	type->RegistCollitions(sprite);															
	START_ANIMATOR( type, sprite, anim, GetGameTime() )	;	
}

void powerUpsAnimatorStart::startPurpleSweetAnimator(){
	Sprite* sprite = new Sprite(															
									BubbleLogic::GetPowerUpPosXY().first,					
									BubbleLogic::GetPowerUpPosXY().second,					
									true,													
									AnimationFilmHolder::GetFilm( "PurpleSweet" ),					
									Terrain::GetActionLayer(),								
									true													
								);															
	MovingAnimation* anim = (MovingAnimation*) AnimationsParser::GetAnimation( "PurpleSweet" );		
	PurpleSweetAnimator* type = new PurpleSweetAnimator();
	type->RegistCollitions(sprite);															
	START_ANIMATOR( type, sprite, anim, GetGameTime() )	;	
}


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
	FruitsAnimators::StartScoreLabel( _this->GetSprite()->GetX(), _this->GetSprite()->GetY(), 100);
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
	std::cout << "AEJNFAELFNAEFNAEF:NAF:NF:EMNFA:EFMNE:MN:FMNA:MNE:F\n";

	YellowSweetAnimator * _this = (YellowSweetAnimator*)args;
	REMOVE_FROM_ACTION_ANIMATOR(_this);
	FruitsAnimators::StartScoreLabel( _this->GetSprite()->GetX(), _this->GetSprite()->GetY(), 100);
	DESTROY_ANIMATOR( _this );
	BubbleLogic::BubYellowSwtAcquired();
	BubbleLogic::GetBubProfile()->SetYellowSwt(true);
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
	FruitsAnimators::StartScoreLabel( _this->GetSprite()->GetX(), _this->GetSprite()->GetY(), 100);
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
	FruitsAnimators::StartScoreLabel( _this->GetSprite()->GetX(), _this->GetSprite()->GetY(), 100);
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