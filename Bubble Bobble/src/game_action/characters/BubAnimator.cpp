#include "GameActionUtilities.h"
#include "BubAnimator.h"
#include "MemoryManage.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "ZenChanAnimator.h"
#include "CollisionChecker.h"
#include "BubblesAnimator.h"
#include "InvisibleSprites.h"
#include "FruitsAnimator.h"
#include "PowerUpsAnimator.h"
#include "BubbleLogic.h"

//////////////////////////static functions

static void startBubBubbleAnimator(Sprite* sprite){
	FrameRangeAnimation *frab = 
		(FrameRangeAnimation*) AnimationsParser::GetAnimation(
													sprite->GoesLeft() ? 
													"BubBubbleBlastOffLeft" : 
													"BubBubbleBlastOffRight"
													);
	Sprite *n_spriteb=new Sprite(
								sprite->GetX(),
								sprite->GetY(),
								sprite->IsGravityAddicted(),
								AnimationFilmHolder::GetFilm( "BubBubbleBlastOff" ), 
								Terrain::GetActionLayer(), 
								sprite->GoesLeft()
								);
	BubBubbleBlastOffAnimator *bbar=new BubBubbleBlastOffAnimator();
	bbar->RegistCollitions(n_spriteb);
	START_ANIMATOR( bbar, n_spriteb, frab, GetGameTime() );
}

static void StartDieAnimator(int x, int y){
	Sprite* newSprite = new Sprite(
									x, 
									y, 
									false, 
									AnimationFilmHolder::GetFilm("BubDieByEnemy"), 
									Terrain::GetActionLayer(),
									false
								  );

	MovingPathAnimation* mpa=(MovingPathAnimation*)AnimationsParser::GetAnimation("BubDieByEnemy");
	BubDieAnimator *bda=new BubDieAnimator();
	bda->RegistCollitions(newSprite);
	START_ANIMATOR( bda, newSprite, mpa, GetGameTime() );
}

void BubAnimatorActions::OnCollisionWithEnemy(Sprite *bub, Sprite *enem, void * args){
	DASSERT(args && enem && bub);
	BubStandAnimator * _this = (BubStandAnimator*)args;
	DASSERT( _this->GetAnimation() && _this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	StartDieAnimator(_this->GetSprite()->GetX(), _this->GetSprite()->GetY());
	DESTROY_ANIMATOR( _this );
}

////////////////BubStandAnimator

BubStandAnimator::BubStandAnimator(){

}

void BubStandAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr,BananaAnimator_t,BananaAnimator_t,BananaAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,OrangeAnimator_t,OrangeAnimator_t,OrangeAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,PeachAnimator_t,PeachAnimator_t,PeachAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,WaterMelonAnimator_t,WaterMelonAnimator_t,WaterMelonAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,BlueDiamondAnimator_t,BlueDiamondAnimator_t,BlueDiamondAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,RedShoesAnimator_t,PurpleSweetAnimator_t, RedShoesAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,YellowSweetAnimator_t,YellowSweetAnimator_t, YellowSweetAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,BlueSweetAnimator_t,BlueSweetAnimator_t, BlueSweetAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,PurpleSweetAnimator_t,PurpleSweetAnimator_t, PurpleSweetAnimator::OnCollisionWithBub);
}

void BubStandAnimator::OnFinishCallback(Animator* anim, void* args){

}

void BubStandAnimator::OnOpenMouth(void){
	REMOVE_FROM_ACTION_ANIMATOR( this );

	FrameRangeAnimation *fra = (FrameRangeAnimation*) AnimationsParser::GetAnimation("BubOpenMouth");
	Sprite *n_sprite=new Sprite(
								this->GetSprite()->GetX(),
								this->GetSprite()->GetY(),
								this->GetSprite()->IsGravityAddicted(),
								AnimationFilmHolder::GetFilm("BubOpenMouth"), 
								Terrain::GetActionLayer(), 
								this->GetSprite()->GoesLeft()
								);
	BubOpenMouthAnimator *bomar = new BubOpenMouthAnimator();
	n_sprite->AddStartFallingListener(bomar);
	bomar->RegistCollitions(n_sprite);
	START_ANIMATOR( bomar, n_sprite, fra, GetGameTime() );
	startBubBubbleAnimator( this->GetSprite() );
	DESTROY_ANIMATOR( this );
}

////////////////BubWalkingAnimator


BubWalkingAnimator::BubWalkingAnimator(void) {
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void BubWalkingAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr, bubBubbleAnimator_t, waterSpecialBubble_t, BubblesAnimatorActions::OnCollisionWithBub);
	CollisionChecker::Register(spr,BananaAnimator_t,BananaAnimator_t,BananaAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,OrangeAnimator_t,OrangeAnimator_t,OrangeAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,PeachAnimator_t,PeachAnimator_t,PeachAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,WaterMelonAnimator_t,WaterMelonAnimator_t,WaterMelonAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,BlueDiamondAnimator_t,BlueDiamondAnimator_t,BlueDiamondAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,RedShoesAnimator_t,PurpleSweetAnimator_t, RedShoesAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,YellowSweetAnimator_t,YellowSweetAnimator_t, YellowSweetAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,BlueSweetAnimator_t,BlueSweetAnimator_t, BlueSweetAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,PurpleSweetAnimator_t,PurpleSweetAnimator_t, PurpleSweetAnimator::OnCollisionWithBub);
}


void BubWalkingAnimator::OnStartFalling(Sprite * sprite){
	DASSERT( sprite && sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	MovingAnimation *fra= (MovingAnimation*)AnimationsParser::GetAnimation("BubFalling");
	Sprite *n_sprite=new Sprite(
								this->GetSprite()->GetX(),
								this->GetSprite()->GetY(),
								this->GetSprite()->IsGravityAddicted(),
								AnimationFilmHolder::GetFilm("BubWalk"), 
								Terrain::GetActionLayer(), 
								this->GetSprite()->GoesLeft()
								);
	BubFallingAnimator *frtor=new BubFallingAnimator();
	n_sprite->AddStopFallingListener(frtor);
	frtor->RegistCollitions(n_sprite);
	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( this );
}


void BubWalkingAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BubWalkingAnimator * _this = (BubWalkingAnimator*)args;
	DASSERT( _this->GetAnimation() && _this->GetSprite() && anim==_this );
	REMOVE_FROM_ACTION_ANIMATOR( _this );

	Sprite * newSprite = _this->GetSprite();
	MovingAnimation *ma = (MovingAnimation*) AnimationsParser::GetAnimation("BubStand");
	newSprite->SetFrame(0);
	BubStandAnimator* mar = new BubStandAnimator();
	mar->RegistCollitions(newSprite);
	START_ANIMATOR( mar, newSprite, ma, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( _this );
}

void BubWalkingAnimator::OnOpenMouth(void){
	REMOVE_FROM_ACTION_ANIMATOR( this );

	FrameRangeAnimation *fra = 
		(FrameRangeAnimation*) AnimationsParser::GetAnimation(
													this->GetSprite()->GoesLeft() ? 
													"BubOpenMouthWalkingLeft" : 
													"BubOpenMouthWalkingRight"
													);
	Sprite *n_sprite=new Sprite(
								this->GetSprite()->GetX(),
								this->GetSprite()->GetY(),
								this->GetSprite()->IsGravityAddicted(),
								AnimationFilmHolder::GetFilm( "BubOpenMouthWalking" ), 
								Terrain::GetActionLayer(), 
								this->GetSprite()->GoesLeft()
								);

	BubOpenMouthAnimator *bomar = new BubOpenMouthAnimator();
	n_sprite->AddStartFallingListener(bomar);
	bomar->RegistCollitions(n_sprite);

	START_ANIMATOR( bomar, n_sprite, fra, GetGameTime() );
	startBubBubbleAnimator( this->GetSprite() );
	DESTROY_ANIMATOR( this );
}

////////////////BubFallingAnimator

BubFallingAnimator::BubFallingAnimator(){
	
}

void BubFallingAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::RegisterBubbleWrapAroundDrivers(spr, this);
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t, BubBubbleAnimator::OnCollisionWithBubFalling);
	CollisionChecker::Register(spr, zenChanInBubble_t, zenChanInBubble_t, ZenChanInBubbleAnimator::OnCollisionWithBubFalling);
	CollisionChecker::Register(spr, zenChanInBubbleMediumAngry_t, zenChanInBubbleMediumAngry_t, ZenChanInBubbleMediumAngryAnimator::OnCollisionWithBubFalling);
	CollisionChecker::Register(spr, zenChanInBubbleHighAngry_t, zenChanInBubbleHighAngry_t, ZenChanInBubbleHighAngryAnimator::OnCollisionWithBubFalling);
	CollisionChecker::Register(spr, mightaInBubble_t, mightaInBubble_t, MightaInBubbleAnimator::OnCollisionWithBubFalling);
	CollisionChecker::Register(spr, mightaInBubbleMediumAngry_t, mightaInBubbleMediumAngry_t, MightaInBubbleMediumAngryAnimator::OnCollisionWithBubFalling);
	CollisionChecker::Register(spr, mightaInBubbleHighAngry_t, mightaInBubbleHighAngry_t, MightaInBubbleHighAngryAnimator::OnCollisionWithBubFalling);
	CollisionChecker::Register(spr, bubPingBubbleAnimator_t, bubPingBubbleAnimator_t, BubPingBubbleAnimator::OnCollisionWithBubFalling);
	CollisionChecker::Register(spr,BananaAnimator_t,BananaAnimator_t,BananaAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,OrangeAnimator_t,OrangeAnimator_t,OrangeAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,PeachAnimator_t,PeachAnimator_t,PeachAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,WaterMelonAnimator_t,WaterMelonAnimator_t,WaterMelonAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,BlueDiamondAnimator_t,BlueDiamondAnimator_t,BlueDiamondAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,RedShoesAnimator_t,PurpleSweetAnimator_t, RedShoesAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,YellowSweetAnimator_t,YellowSweetAnimator_t, YellowSweetAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,BlueSweetAnimator_t,BlueSweetAnimator_t, BlueSweetAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,PurpleSweetAnimator_t,PurpleSweetAnimator_t, PurpleSweetAnimator::OnCollisionWithBub);
}

void BubFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	MovingAnimation *fra= (MovingAnimation*)AnimationsParser::GetAnimation("BubStand");
	Sprite *n_sprite=new Sprite(this->GetSprite()->GetX(),this->GetSprite()->GetY(),
		this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("BubWalk"), 
						Terrain::GetActionLayer(), this->GetSprite()->GoesLeft());

	BubStandAnimator *frtor=new BubStandAnimator();
	frtor->RegistCollitions(n_sprite);
	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( this );
}

void BubFallingAnimator::OnOpenMouth(){
	REMOVE_FROM_ACTION_ANIMATOR( this );

	FrameRangeAnimation *fra = (FrameRangeAnimation*) AnimationsParser::GetAnimation("BubOpenMouthFalling");
	Sprite *n_sprite=new Sprite(
								this->GetSprite()->GetX(),
								this->GetSprite()->GetY(),
								this->GetSprite()->IsGravityAddicted(),
								AnimationFilmHolder::GetFilm("BubOpenMouth"), 
								Terrain::GetActionLayer(), 
								this->GetSprite()->GoesLeft()
								);
	BubOpenMouthFallingAnimator *bomfar = new BubOpenMouthFallingAnimator();
	n_sprite->AddStopFallingListener( bomfar );
	bomfar->RegistCollitions(n_sprite);
	START_ANIMATOR( bomfar, n_sprite, fra, GetGameTime() );
	startBubBubbleAnimator( n_sprite );
	DESTROY_ANIMATOR( this );
}

///////////////////////BubOpenMouthAnimator

BubOpenMouthAnimator::BubOpenMouthAnimator(){
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void BubOpenMouthAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr, bubBubbleAnimator_t, waterSpecialBubble_t, BubblesAnimatorActions::OnCollisionWithBub);
	CollisionChecker::Register(spr,BananaAnimator_t,BananaAnimator_t,BananaAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,OrangeAnimator_t,OrangeAnimator_t,OrangeAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,PeachAnimator_t,PeachAnimator_t,PeachAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,WaterMelonAnimator_t,WaterMelonAnimator_t,WaterMelonAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,BlueDiamondAnimator_t,BlueDiamondAnimator_t,BlueDiamondAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,RedShoesAnimator_t,PurpleSweetAnimator_t, RedShoesAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,YellowSweetAnimator_t,YellowSweetAnimator_t, YellowSweetAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,BlueSweetAnimator_t,BlueSweetAnimator_t, BlueSweetAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,PurpleSweetAnimator_t,PurpleSweetAnimator_t, PurpleSweetAnimator::OnCollisionWithBub);
}

void BubOpenMouthAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args && args==anim);
	BubOpenMouthAnimator * _this = (BubOpenMouthAnimator*)args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );

	MovingAnimation *fra= (MovingAnimation*)AnimationsParser::GetAnimation("BubStand");
	Sprite *n_sprite = new Sprite(
									_this->GetSprite()->GetX(),
									_this->GetSprite()->GetY(),
									_this->GetSprite()->IsGravityAddicted(),
									AnimationFilmHolder::GetFilm("BubWalk"), 
									Terrain::GetActionLayer(), 
									_this->GetSprite()->GoesLeft()
								);
	BubStandAnimator *frtor=new BubStandAnimator();
	frtor->RegistCollitions(n_sprite);
	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( _this );
}

void BubOpenMouthAnimator::OnStartFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	MovingAnimation *fra= (MovingAnimation*)AnimationsParser::GetAnimation("BubFalling");
	Sprite *n_sprite = new Sprite(
									this->GetSprite()->GetX(),
									this->GetSprite()->GetY(),
									this->GetSprite()->IsGravityAddicted(),
									AnimationFilmHolder::GetFilm("BubWalk"), 
									Terrain::GetActionLayer(), 
									this->GetSprite()->GoesLeft()
								);
	BubFallingAnimator *frtor=new BubFallingAnimator();
	frtor->RegistCollitions(n_sprite);
	n_sprite->AddStopFallingListener(frtor);
	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( this );
}


///////////////////////BubOpenMouthFallingAnimator

BubOpenMouthFallingAnimator::BubOpenMouthFallingAnimator(){
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void BubOpenMouthFallingAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::RegisterBubbleWrapAroundDrivers(spr, this);
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t, BubBubbleAnimator::OnCollisionWithBubFalling);
	CollisionChecker::Register(spr, zenChanInBubble_t, zenChanInBubble_t, ZenChanInBubbleAnimator::OnCollisionWithBubFalling);
	CollisionChecker::Register(spr, zenChanInBubbleMediumAngry_t, zenChanInBubbleMediumAngry_t, ZenChanInBubbleMediumAngryAnimator::OnCollisionWithBubFalling);
	CollisionChecker::Register(spr, zenChanInBubbleHighAngry_t, zenChanInBubbleHighAngry_t, ZenChanInBubbleHighAngryAnimator::OnCollisionWithBubFalling);
	CollisionChecker::Register(spr, mightaInBubble_t, mightaInBubble_t, MightaInBubbleAnimator::OnCollisionWithBubFalling);
	CollisionChecker::Register(spr, mightaInBubbleMediumAngry_t, mightaInBubbleMediumAngry_t, MightaInBubbleMediumAngryAnimator::OnCollisionWithBubFalling);
	CollisionChecker::Register(spr, mightaInBubbleHighAngry_t, mightaInBubbleHighAngry_t, MightaInBubbleHighAngryAnimator::OnCollisionWithBubFalling);
	CollisionChecker::Register(spr, bubPingBubbleAnimator_t, bubPingBubbleAnimator_t, BubPingBubbleAnimator::OnCollisionWithBubFalling);
	CollisionChecker::Register(spr,BananaAnimator_t,BananaAnimator_t,BananaAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,OrangeAnimator_t,OrangeAnimator_t,OrangeAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,PeachAnimator_t,PeachAnimator_t,PeachAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,WaterMelonAnimator_t,WaterMelonAnimator_t,WaterMelonAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,BlueDiamondAnimator_t,BlueDiamondAnimator_t,BlueDiamondAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,RedShoesAnimator_t,PurpleSweetAnimator_t, RedShoesAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,YellowSweetAnimator_t,YellowSweetAnimator_t, YellowSweetAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,BlueSweetAnimator_t,BlueSweetAnimator_t, BlueSweetAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,PurpleSweetAnimator_t,PurpleSweetAnimator_t, PurpleSweetAnimator::OnCollisionWithBub);
}

void BubOpenMouthFallingAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args && anim == args );
	BubOpenMouthFallingAnimator* _this = (BubOpenMouthFallingAnimator*) anim;
	REMOVE_FROM_ACTION_ANIMATOR( _this );

	MovingAnimation *fra= (MovingAnimation*)AnimationsParser::GetAnimation("BubFalling");
	Sprite *n_sprite=new Sprite(
								_this->GetSprite()->GetX(),
								_this->GetSprite()->GetY(),
								_this->GetSprite()->IsGravityAddicted(),
								AnimationFilmHolder::GetFilm("BubWalk"), 
								Terrain::GetActionLayer(), 
								_this->GetSprite()->GoesLeft()
								);
	BubFallingAnimator *frtor=new BubFallingAnimator();
	n_sprite->AddStopFallingListener(frtor);
	frtor->RegistCollitions(n_sprite);
	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( _this );
}

void BubOpenMouthFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	MovingAnimation *fra= (MovingAnimation*)AnimationsParser::GetAnimation("BubStand");
	Sprite *n_sprite=new Sprite(this->GetSprite()->GetX(),this->GetSprite()->GetY(),
		this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("BubWalk"), 
						Terrain::GetActionLayer(), this->GetSprite()->GoesLeft());

	BubStandAnimator *frtor=new BubStandAnimator();
	frtor->RegistCollitions(n_sprite);
	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( this );
}


///////////////////////BubJumpAnimator

BubJumpAnimator::BubJumpAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
}

void BubJumpAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t, BubBubbleAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, zenChanInBubble_t, zenChanInBubble_t, ZenChanInBubbleAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, zenChanInBubbleMediumAngry_t, zenChanInBubbleMediumAngry_t, ZenChanInBubbleMediumAngryAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, zenChanInBubbleHighAngry_t, zenChanInBubbleHighAngry_t, ZenChanInBubbleHighAngryAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, mightaInBubble_t, mightaInBubble_t, MightaInBubbleAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, bubPingBubbleAnimator_t, bubPingBubbleAnimator_t, BubPingBubbleAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr,BananaAnimator_t,BananaAnimator_t,BananaAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,OrangeAnimator_t,OrangeAnimator_t,OrangeAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,PeachAnimator_t,PeachAnimator_t,PeachAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,WaterMelonAnimator_t,WaterMelonAnimator_t,WaterMelonAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,BlueDiamondAnimator_t,BlueDiamondAnimator_t,BlueDiamondAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,RedShoesAnimator_t,PurpleSweetAnimator_t, RedShoesAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,YellowSweetAnimator_t,YellowSweetAnimator_t, YellowSweetAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,BlueSweetAnimator_t,BlueSweetAnimator_t, BlueSweetAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,PurpleSweetAnimator_t,PurpleSweetAnimator_t, PurpleSweetAnimator::OnCollisionWithBub);
}

void BubJumpAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args && anim==args);
	BubJumpAnimator * _this = (BubJumpAnimator*)args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );

	MovingAnimation *fra = (MovingAnimation*)AnimationsParser::GetAnimation("BubFalling");
	Sprite *n_sprite = new Sprite(
									_this->GetSprite()->GetX(),
									_this->GetSprite()->GetY(),
									_this->GetSprite()->IsGravityAddicted(),
									AnimationFilmHolder::GetFilm("BubWalk"), 
									Terrain::GetActionLayer(), 
									_this->GetSprite()->GoesLeft()
								);
	BubFallingAnimator *frtor=new BubFallingAnimator();
	n_sprite->AddStopFallingListener(frtor);
	frtor->RegistCollitions(n_sprite);
	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( _this );
}

void BubJumpAnimator::OnOpenMouth(){

	REMOVE_FROM_ACTION_ANIMATOR( this );

	MovingPathAnimation *fra = (MovingPathAnimation*) AnimationsParser::GetAnimation("BubOpenMouthJump");
	Sprite *n_sprite=new Sprite(
								this->GetSprite()->GetX(),
								this->GetSprite()->GetY(),
								this->GetSprite()->IsGravityAddicted(),
								AnimationFilmHolder::GetFilm("BubOpenMouth"), 
								Terrain::GetActionLayer(), 
								this->GetSprite()->GoesLeft()
								);
	BubJumpOpenMouthAnimator *bomfar = new BubJumpOpenMouthAnimator(this->GetAnimation(), this->GetCurrIndex());
	bomfar->RegistCollitions(n_sprite);
	START_ANIMATOR( bomfar, n_sprite, fra, GetGameTime() );
	startBubBubbleAnimator( n_sprite );
	this->GetSprite()->Destroy();
	this->Destroy();
}

///////////////////////BubJumpOpenMouthAnimator

BubJumpOpenMouthAnimator::BubJumpOpenMouthAnimator(MovingPathAnimation* _jumpAnimation, int _index){
	this->SetOnFinish(OnFinishCallback,(void*)this);
	jumpAnimation = _jumpAnimation;
	index = _index;
}

void BubJumpOpenMouthAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t, BubBubbleAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, zenChanInBubble_t, zenChanInBubble_t, ZenChanInBubbleAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, zenChanInBubbleMediumAngry_t, zenChanInBubbleMediumAngry_t, ZenChanInBubbleMediumAngryAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, zenChanInBubbleHighAngry_t, zenChanInBubbleHighAngry_t, ZenChanInBubbleHighAngryAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, mightaInBubble_t, mightaInBubble_t, MightaInBubbleAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, bubPingBubbleAnimator_t, bubPingBubbleAnimator_t, BubPingBubbleAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr,BananaAnimator_t,BananaAnimator_t,BananaAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,OrangeAnimator_t,OrangeAnimator_t,OrangeAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,PeachAnimator_t,PeachAnimator_t,PeachAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,WaterMelonAnimator_t,WaterMelonAnimator_t,WaterMelonAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,BlueDiamondAnimator_t,BlueDiamondAnimator_t,BlueDiamondAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,RedShoesAnimator_t,PurpleSweetAnimator_t, RedShoesAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,YellowSweetAnimator_t,YellowSweetAnimator_t, YellowSweetAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,BlueSweetAnimator_t,BlueSweetAnimator_t, BlueSweetAnimator::OnCollisionWithBub);
	CollisionChecker::Register(spr,PurpleSweetAnimator_t,PurpleSweetAnimator_t, PurpleSweetAnimator::OnCollisionWithBub);
}

void BubJumpOpenMouthAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args && anim==args);
	BubJumpOpenMouthAnimator * _this = (BubJumpOpenMouthAnimator*)args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );


	int index = _this->GetIndex();
	index+=_this->GetAnimation()->GetPath().size();
	if( _this->GetJumpAnimation()->GetPath().size() <= index ){
		MovingAnimation *fra = (MovingAnimation*)AnimationsParser::GetAnimation("BubFalling");
		Sprite *n_sprite = new Sprite(
										_this->GetSprite()->GetX(),
										_this->GetSprite()->GetY(),
										_this->GetSprite()->IsGravityAddicted(),
										AnimationFilmHolder::GetFilm("BubWalk"), 
										Terrain::GetActionLayer(), 
										_this->GetSprite()->GoesLeft()
									);
		BubFallingAnimator *frtor=new BubFallingAnimator();
		n_sprite->AddStopFallingListener(frtor);
		frtor->RegistCollitions(n_sprite);
		START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
		_this->GetJumpAnimation()->Destroy();
	}else{

		Sprite *n_sprite = new Sprite(
										_this->GetSprite()->GetX(),
										_this->GetSprite()->GetY(),
										_this->GetSprite()->IsGravityAddicted(),
										AnimationFilmHolder::GetFilm("BubWalk"), 
										Terrain::GetActionLayer(), 
										_this->GetSprite()->GoesLeft()
									);
		BubJumpAnimator* mar = new BubJumpAnimator();
		START_ANIMATOR( mar, n_sprite, _this->GetJumpAnimation(), GetGameTime() );
		mar->SetCurrIndex(index);
	}

	DESTROY_ANIMATOR( _this );
}

MovingPathAnimation* BubJumpOpenMouthAnimator::GetJumpAnimation(){
	return jumpAnimation;
}

int	BubJumpOpenMouthAnimator::GetIndex(){
	return index;
}

/////////////////////////BubDieAnimator

BubDieAnimator::BubDieAnimator(){
	this->SetOnFinish(OnFinishCallback, (void*)this);
}

void BubDieAnimator::RegistCollitions(Sprite *spr){
}

void BubDieAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args && anim==args);
	BubDieAnimator * _this = (BubDieAnimator*)args;
	DASSERT( _this->GetAnimation() && _this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );

	BubbleLogic::SetBubScore(BubbleLogic::GetBubProfile()->GetScore() / 2 );
	BubbleLogic::GetBubProfile()->SetYellowSwt(false);
	BubbleLogic::GetBubProfile()->SetBlueSwt(false);
	BubbleLogic::GetBubProfile()->SetPurpleSwt(false);
	BubbleLogic::GetBubProfile()->SetRedShoes(false);
}
