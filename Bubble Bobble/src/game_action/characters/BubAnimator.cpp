#include "GameActionUtilities.h"
#include "BubAnimator.h"
#include "MemoryManage.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "ZenChanAnimator.h"
#include "MightaAnimator.h"
#include "RiverAnimator.h"
#include "CollisionChecker.h"
#include "BubblesAnimator.h"
#include "InvisibleSprites.h"
#include "FruitsAnimator.h"
#include "PowerUpsAnimator.h"
#include "BubbleLogic.h"

#define REGIST_FRUITS_AND_POWER_UPS( spr )																						\
	CollisionChecker::Register(spr,BananaAnimator_t,BananaAnimator_t,BananaAnimator::OnCollisionWithBub);						\
	CollisionChecker::Register(spr,OrangeAnimator_t,OrangeAnimator_t,OrangeAnimator::OnCollisionWithBub);						\
	CollisionChecker::Register(spr,PeachAnimator_t,PeachAnimator_t,PeachAnimator::OnCollisionWithBub);							\
	CollisionChecker::Register(spr,WaterMelonAnimator_t,WaterMelonAnimator_t,WaterMelonAnimator::OnCollisionWithBub);			\
	CollisionChecker::Register(spr,BlueDiamondAnimator_t,BlueDiamondAnimator_t,BlueDiamondAnimator::OnCollisionWithBub);		\
	CollisionChecker::Register(spr,RedShoesAnimator_t,RedShoesAnimator_t, RedShoesAnimator::OnCollisionWithBub);				\
	CollisionChecker::Register(spr,YellowSweetAnimator_t,YellowSweetAnimator_t, YellowSweetAnimator::OnCollisionWithBub);		\
	CollisionChecker::Register(spr,BlueSweetAnimator_t,BlueSweetAnimator_t, BlueSweetAnimator::OnCollisionWithBub);				\
	CollisionChecker::Register(spr,PurpleSweetAnimator_t,PurpleSweetAnimator_t, PurpleSweetAnimator::OnCollisionWithBub);		\
	REFRESH_KILLED_ENEMIES_COUNTER();

//////////////////////////static functions

static void startBubBubbleAnimator(Sprite* sprite){

	std::vector<Animator*> bubbles = AnimatorHolder::GetAnimators(bubBubbleAnimator_t);
	if(bubbles.size()>20){
		BubBubbleAnimator * _this = (BubBubbleAnimator *) bubbles.front();	
		REMOVE_FROM_ACTION_ANIMATOR( _this );	
		BubblesAnimatorActions::OnTickTimerFinishCallback(_this->getBubBubbleTimer(), 0);													
		DESTROY_ANIMATOR( _this );	
	}

	FrameRangeAnimation *frab = 
		(FrameRangeAnimation*) AnimationsParser::GetAnimation(
									BubbleLogic::GetBubProfile()->GetBubbleBlastAnimation(sprite->GoesLeft() )
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
									true, 
									AnimationFilmHolder::GetFilm("BubDieByEnemy"), 
									Terrain::GetActionLayer(),
									false
								  );

	MovingPathAnimation* mpa=(MovingPathAnimation*)AnimationsParser::GetAnimation("BubDieByEnemy");
	BubDieAnimator *bda=new BubDieAnimator();
	newSprite->AddStartFallingListener(bda);
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

////////////////BubInBubbleAnimator

BubInBubbleAnimator::BubInBubbleAnimator(){
	this->SetOnFinish(OnFinishCallback, (void*)this);
}

void BubInBubbleAnimator::OnFinishCallback(Animator* anmr, void* args){
	DASSERT( anmr && anmr==args );
	BubInBubbleAnimator* _this = (BubInBubbleAnimator*) anmr;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );

	Sprite* sprite = new Sprite(BubbleLogic::GetBubProfile()->GetStartX(),BubbleLogic::GetBubProfile()->GetStartY(),
								BubbleLogic::GetBubProfile()->GetStartGravity(),AnimationFilmHolder::GetFilm("BubWalk"),
								Terrain::GetActionLayer(), BubbleLogic::GetBubProfile()->GetStartDirection());	
	MovingAnimation* anim = (MovingAnimation*) AnimationsParser::GetAnimation("BubStand");															
	BubStandAnimator* animr = new BubStandAnimator();
	animr->RegistCollitions(sprite);

	Sprite* sprite2 = new Sprite(200, 79,true,AnimationFilmHolder::GetFilm("MightaWalk"), Terrain::GetActionLayer(), true);	
	FrameRangeAnimation* anim2 = (FrameRangeAnimation*) AnimationsParser::GetAnimation("MightaWalkLeft");															
	MightaWalkingAnimator* animr2 = new MightaWalkingAnimator();
	sprite2->AddStartFallingListener(animr2);
	animr2->RegistCollitions(sprite2);
	
	Sprite* sprite3 = new Sprite(300,79,true,AnimationFilmHolder::GetFilm("ZenChanWalk"), Terrain::GetActionLayer(), true);	
	FrameRangeAnimation* anim3 = (FrameRangeAnimation*) AnimationsParser::GetAnimation("ZenChanWalkLeft");															
	ZenChanWalkingAnimator* animr3 = new ZenChanWalkingAnimator();
	sprite3->AddStartFallingListener(animr3);
	animr3->RegistCollitions(sprite3);
	
	Sprite* sprite4 = new Sprite(BubbleLogic::GetPowerUpPosXY().first,BubbleLogic::GetPowerUpPosXY().second,true,AnimationFilmHolder::GetFilm("PurpleSweet"), Terrain::GetActionLayer(), true);	
	FrameRangeAnimation* anim4 = (FrameRangeAnimation*) AnimationsParser::GetAnimation("PurpleSweet");															
	PurpleSweetAnimator* animr4 = new PurpleSweetAnimator();
	animr4->RegistCollitions(sprite4);
	
	Sprite* sprite5 = new Sprite(BubbleLogic::GetPowerUpPosXY().first,BubbleLogic::GetPowerUpPosXY().second,true,AnimationFilmHolder::GetFilm("BlueSweet"), Terrain::GetActionLayer(), true);	
	FrameRangeAnimation* anim5 = (FrameRangeAnimation*) AnimationsParser::GetAnimation("BlueSweet");															
	BlueSweetAnimator* animr5 = new BlueSweetAnimator();
	animr5->RegistCollitions(sprite5);



	START_ANIMATOR( animr, sprite, anim, GetGameTime() );
	START_ANIMATOR( animr2, sprite2, anim2, GetGameTime() );
	START_ANIMATOR( animr3, sprite3, anim3, GetGameTime() );
	START_ANIMATOR( animr4, sprite4, anim4, GetGameTime() );
	START_ANIMATOR( animr5, sprite5, anim5, GetGameTime() );
	

	RiverSprite* sprite7 = new RiverSprite(400,50,true,AnimationFilmHolder::GetFilm("RiverHFront"), Terrain::GetActionLayer(), true);	
	MovingAnimation* anim7 = (MovingAnimation*) AnimationsParser::GetAnimation("WaterRushLeft");
	RiverAnimator* animr7 = new RiverAnimator();
	sprite7->AddStartFallingListener( animr7 );
	sprite7->AddStopFallingListener( animr7 );
	animr7->RegistCollitions(sprite7);


	START_ANIMATOR( animr7, sprite7, anim7, GetGameTime() );
}

////////////////BubStandAnimator

BubStandAnimator::BubStandAnimator(){

}

void BubStandAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr, mightaMovingFireBallAnimator_t, mightaMovingFireBallAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	REGIST_FRUITS_AND_POWER_UPS( spr );
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
	CollisionChecker::Register(spr, mightaMovingFireBallAnimator_t, mightaMovingFireBallAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr, bubBubbleAnimator_t, waterSpecialBubble_t, BubblesAnimatorActions::OnCollisionWithBub);
	REGIST_FRUITS_AND_POWER_UPS( spr );
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
							BubbleLogic::GetBubProfile()->GetBubOpenMouthWalkAnimation(this->GetSprite()->GoesLeft())
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
	CollisionChecker::Register(spr, mightaMovingFireBallAnimator_t, mightaMovingFireBallAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
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

	REGIST_FRUITS_AND_POWER_UPS( spr );
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
	CollisionChecker::Register(spr, mightaMovingFireBallAnimator_t, mightaMovingFireBallAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr, bubBubbleAnimator_t, waterSpecialBubble_t, BubblesAnimatorActions::OnCollisionWithBub);
	REGIST_FRUITS_AND_POWER_UPS( spr );
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
	CollisionChecker::Register(spr, mightaMovingFireBallAnimator_t, mightaMovingFireBallAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
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

	REGIST_FRUITS_AND_POWER_UPS( spr );
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

	//logic
	REFRESH_KILLED_ENEMIES_COUNTER();
}


///////////////////////BubJumpAnimator

BubJumpAnimator::BubJumpAnimator(){
	this->SetOnFinish(OnFinishCallback,(void*)this);
	//logic
	BubbleLogic::GetBubProfile()->IncrTimesJumped();
}

void BubJumpAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr, mightaMovingFireBallAnimator_t, mightaMovingFireBallAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t, BubBubbleAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, zenChanInBubble_t, zenChanInBubble_t, ZenChanInBubbleAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, zenChanInBubbleMediumAngry_t, zenChanInBubbleMediumAngry_t, ZenChanInBubbleMediumAngryAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, zenChanInBubbleHighAngry_t, zenChanInBubbleHighAngry_t, ZenChanInBubbleHighAngryAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, mightaInBubble_t, mightaInBubble_t, MightaInBubbleAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, mightaInBubbleMediumAngry_t, mightaInBubbleMediumAngry_t, MightaInBubbleMediumAngryAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, mightaInBubbleHighAngry_t, mightaInBubbleHighAngry_t, MightaInBubbleHighAngryAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, bubPingBubbleAnimator_t, bubPingBubbleAnimator_t, BubPingBubbleAnimator::OnCollisionWithBubJump);

	REGIST_FRUITS_AND_POWER_UPS( spr );
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
	CollisionChecker::Register(spr, mightaMovingFireBallAnimator_t, mightaMovingFireBallAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, this, BubAnimatorActions::OnCollisionWithEnemy);
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t, BubBubbleAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, zenChanInBubble_t, zenChanInBubble_t, ZenChanInBubbleAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, zenChanInBubbleMediumAngry_t, zenChanInBubbleMediumAngry_t, ZenChanInBubbleMediumAngryAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, zenChanInBubbleHighAngry_t, zenChanInBubbleHighAngry_t, ZenChanInBubbleHighAngryAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, mightaInBubble_t, mightaInBubble_t, MightaInBubbleAnimator::OnCollisionWithBubJump);
	CollisionChecker::Register(spr, bubPingBubbleAnimator_t, bubPingBubbleAnimator_t, BubPingBubbleAnimator::OnCollisionWithBubJump);
	REGIST_FRUITS_AND_POWER_UPS( spr );
}

void BubJumpOpenMouthAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args && anim==args);
	BubJumpOpenMouthAnimator * _this = (BubJumpOpenMouthAnimator*)args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );


	int index = _this->GetIndex();
	index+=_this->GetAnimation()->GetPath().size();
	if( ((int) _this->GetJumpAnimation()->GetPath().size()) <= index ){
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

	MovingAnimation *fra= (MovingAnimation*)AnimationsParser::GetAnimation("BubStand");
	Sprite *n_sprite=new Sprite(BubbleLogic::GetBubProfile()->GetStartX(), 
								BubbleLogic::GetBubProfile()->GetStartY(),
								BubbleLogic::GetBubProfile()->GetStartGravity(),
								AnimationFilmHolder::GetFilm("BubWalk"), 
								Terrain::GetActionLayer(),
								BubbleLogic::GetBubProfile()->GetStartDirection());

	BubStandAnimator *frtor=new BubStandAnimator();
	frtor->RegistCollitions(n_sprite);
	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );

	DESTROY_ANIMATOR( _this );

	////// refresh bub profile
	BubbleLogic::SetBubScore(BubbleLogic::GetBubProfile()->GetScore() / 2 );
	BubbleLogic::GetBubProfile()->SetYellowSwt(false);
	BubbleLogic::GetBubProfile()->SetBlueSwt(false);
	BubbleLogic::GetBubProfile()->SetPurpleSwt(false);
	BubbleLogic::GetBubProfile()->SetRedShoes(false);
}

void BubDieAnimator::OnStartFalling(Sprite * sprite){
	
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	MovingAnimation, zenFallAnmn, "BubFalling",
						BubDieFallingAnimator, zenFallAnmr, this->GetSprite() );

	this->GetSprite()->AddStopFallingListener(zenFallAnmr);
	START_ANIMATOR( zenFallAnmr, this->GetSprite(), zenFallAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}

////////////////BubDieFallingAnimtor

BubDieFallingAnimator::BubDieFallingAnimator(){}

void BubDieFallingAnimator::RegistCollitions(Sprite *spr){
	
}

void BubDieFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	INIT_NEW_INSTANCE_WITH_SPRITE(	MovingPathAnimation, zenStandAnmn, "BubDieByEnemy",
					BubDieAnimator, zenStandAnmr, this->GetSprite() );	
	
	START_ANIMATOR( zenStandAnmr, this->GetSprite(), zenStandAnmn, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( this );
}
