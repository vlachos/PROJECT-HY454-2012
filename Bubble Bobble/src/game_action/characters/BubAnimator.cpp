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

//////////////////////////static functions

static void startBubBubbleAnimator(Sprite* sprite){
	FrameRangeAnimation *frab = 
		(FrameRangeAnimation*) AnimationsParser::GetAnimation(
													sprite->GoesLeft() ? 
													"BubBubbleLeft" : 
													"BubBubbleRight"
													);
	Sprite *n_spriteb=new Sprite(
								sprite->GetX(),
								sprite->GetY(),
								sprite->IsGravityAddicted(),
								AnimationFilmHolder::GetFilm( "BubBubbleBlastOff" ), 
								Terrain::GetActionLayer(), 
								sprite->GoesLeft()
								);
	//std::cout << "display: " << sprite->GetX() << ", " << sprite->GetY() << ", " <<sprite->GetFrameBox().GetWidth() << ", " << sprite->GetFrameBox().GetHeigth() << "\n";
	BubBubbleBlastOffAnimator *bbar=new BubBubbleBlastOffAnimator();
	bbar->RegistCollitions(bbar, n_spriteb);
	START_ANIMATOR( bbar, n_spriteb, frab, GetGameTime() );
}


////////////////BubStandAnimator

BubStandAnimator::BubStandAnimator(){

}

void BubStandAnimator::RegistCollitions(Animator *anim, Sprite *spr){
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, 0, 0);
}

void BubStandAnimator::OnFinishCallback(Animator* anim, void* args){



}

void BubStandAnimator::OnOpenMouth(void){
	REMOVE_FROM_ACTION_ANIMATOR( this );

	FrameRangeAnimation *fra = (FrameRangeAnimation*) AnimationsParser::GetAnimation("BubOpenMouth");
	Sprite *n_sprite=new Sprite(this->GetSprite()->GetX(),this->GetSprite()->GetY(),
						this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("BubOpenMouth"), 
						Terrain::GetActionLayer(), this->GetSprite()->GoesLeft());

	BubOpenMouthAnimator *bomar = new BubOpenMouthAnimator();
	n_sprite->AddStartFallingListener(bomar);
	bomar->RegistCollitions(bomar, n_sprite);
	START_ANIMATOR( bomar, n_sprite, fra, GetGameTime() );

	startBubBubbleAnimator( this->GetSprite() );

	DESTROY_ANIMATOR( this );
}

////////////////BubWalkingAnimator


BubWalkingAnimator::BubWalkingAnimator(void) {
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void BubWalkingAnimator::RegistCollitions(Animator *anim, Sprite *spr){
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, 0, 0);
}


void BubWalkingAnimator::OnStartFalling(Sprite * sprite){
	
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	MovingAnimation *fra= (MovingAnimation*)AnimationsParser::GetAnimation("BubFalling");

	Sprite *n_sprite=new Sprite(this->GetSprite()->GetX(),this->GetSprite()->GetY(),
						this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("BubWalk"), 
						Terrain::GetActionLayer(), this->GetSprite()->GoesLeft());

	BubFallingAnimator *frtor=new BubFallingAnimator();
	n_sprite->AddStopFallingListener(frtor);
	frtor->RegistCollitions(frtor, n_sprite);
	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( this );
}


void BubWalkingAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BubWalkingAnimator * _this = (BubWalkingAnimator*)args;
	DASSERT( anim==_this );
	DASSERT( _this->GetAnimation() && _this->GetSprite());

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	Sprite * newSprite = _this->GetSprite();


	MovingAnimation *ma = (MovingAnimation*) AnimationsParser::GetAnimation("BubStand");
	newSprite->SetFrame(0);
	BubStandAnimator* mar = new BubStandAnimator();
	mar->RegistCollitions(mar, newSprite);
	START_ANIMATOR( mar, newSprite, ma, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( _this );
}

void BubWalkingAnimator::OnCollisionWithEnemy(Sprite *bub, Sprite *enem, void * args){
	DASSERT(args);
	BubWalkingAnimator * _this = (BubWalkingAnimator*)args;

	timestamp_t timestamp = GetGameTime();
	DASSERT( timestamp>0 );

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	DASSERT( _this->GetAnimation() && _this->GetSprite() );
	DASSERT(_this->GetSprite()==bub);
	Sprite* newSprite = 
		new Sprite(bub->GetX(),bub->GetY(),
		false,AnimationFilmHolder::GetFilm("BubDieByEnemy"),
		Terrain::GetActionLayer(),false);

	MovingPathAnimation* mpa=(MovingPathAnimation*)AnimationsParser::GetAnimation("BubDieByEnemy");
	BubDieAnimator *bda=new BubDieAnimator();
	bda->RegistCollitions(bda, newSprite);
	START_ANIMATOR( bda, newSprite, mpa, GetGameTime() );
	DESTROY_ANIMATOR( _this );
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
	bomar->RegistCollitions(bomar, n_sprite);

	START_ANIMATOR( bomar, n_sprite, fra, GetGameTime() );
	startBubBubbleAnimator( this->GetSprite() );
	DESTROY_ANIMATOR( this );
}

////////////////BubFallingAnimator

BubFallingAnimator::BubFallingAnimator(){
	
}

void BubFallingAnimator::RegistCollitions(Animator *anim, Sprite *spr){
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, 0, 0);
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t, 0, BubBubbleAnimator::OnCollisionWithBubFalling, true);
}

void BubFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	MovingAnimation *fra= (MovingAnimation*)AnimationsParser::GetAnimation("BubStand");
	Sprite *n_sprite=new Sprite(this->GetSprite()->GetX(),this->GetSprite()->GetY(),
		this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("BubWalk"), 
						Terrain::GetActionLayer(), this->GetSprite()->GoesLeft());

	BubStandAnimator *frtor=new BubStandAnimator();
	frtor->RegistCollitions(frtor, n_sprite);
	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( this );
}

void BubFallingAnimator::OnCollisionWithEnemy(Sprite *bub, Sprite *enem, void * args){
	DASSERT(args);
	BubFallingAnimator * _this = (BubFallingAnimator*)args;

	timestamp_t timestamp = GetGameTime();
	DASSERT( timestamp>0 );

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	DASSERT( _this->GetAnimation() && _this->GetSprite() );
	DASSERT(_this->GetSprite()==bub);
	Sprite* newSprite = 
		new Sprite(bub->GetX(),bub->GetY(),
		false,AnimationFilmHolder::GetFilm("BubDieByEnemy"),
		Terrain::GetActionLayer(),false);

	MovingPathAnimation* mpa=(MovingPathAnimation*)AnimationsParser::GetAnimation("BubDieByEnemy");
	
	BubDieAnimator *bda=new BubDieAnimator();
	bda->RegistCollitions(bda, newSprite);

	START_ANIMATOR( bda, newSprite, mpa, GetGameTime() );
	DESTROY_ANIMATOR( _this );
}

///////////////////////BubOpenMouthAnimator

BubOpenMouthAnimator::BubOpenMouthAnimator(){
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void BubOpenMouthAnimator::RegistCollitions(Animator *anim, Sprite *spr){
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, 0, 0);
}

void BubOpenMouthAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BubOpenMouthAnimator * _this = (BubOpenMouthAnimator*)args;
	DASSERT( anim==_this );

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	MovingAnimation *fra= (MovingAnimation*)AnimationsParser::GetAnimation("BubStand");
	Sprite *n_sprite=new Sprite(_this->GetSprite()->GetX(),_this->GetSprite()->GetY(),
		_this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("BubWalk"), 
						Terrain::GetActionLayer(), _this->GetSprite()->GoesLeft());

	BubStandAnimator *frtor=new BubStandAnimator();
	frtor->RegistCollitions(frtor, n_sprite);

	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( _this );
}

void BubOpenMouthAnimator::OnStartFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	MovingAnimation *fra= (MovingAnimation*)AnimationsParser::GetAnimation("BubFalling");
	Sprite *n_sprite=new Sprite(this->GetSprite()->GetX(),this->GetSprite()->GetY(),
						this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("BubWalk"), 
						Terrain::GetActionLayer(), this->GetSprite()->GoesLeft());
	n_sprite->SetFrame(0);

	BubFallingAnimator *frtor=new BubFallingAnimator();
	frtor->RegistCollitions(frtor, n_sprite);
	n_sprite->AddStopFallingListener(frtor);

	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( this );
}

///////////////////////BubJumpAnimator

BubJumpAnimator::BubJumpAnimator(){
}

void BubJumpAnimator::RegistCollitions(Animator *anim, Sprite *spr){
	CollisionChecker::Register(spr, zenChanStandAnimator_t, baronVonBlubaStandAnimator_t, anim, BubJumpAnimator::OnCollisionWithEnemy);
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t, 0, BubBubbleAnimator::OnCollisionWithBubJump, true);
}

void BubJumpAnimator::OnCollisionWithEnemy(Sprite *bub, Sprite *enem, void * args){
	DASSERT(args);
	BubJumpAnimator * _this = (BubJumpAnimator*)args;

	timestamp_t timestamp = GetGameTime();
	DASSERT( timestamp>0 );

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	DASSERT( _this->GetAnimation() && _this->GetSprite() );
	DASSERT(_this->GetSprite()==bub);
	Sprite* newSprite = 
		new Sprite(bub->GetX(),bub->GetY(),
		false,AnimationFilmHolder::GetFilm("BubDieByEnemy"),
		Terrain::GetActionLayer(),false);

	MovingPathAnimation* mpa=(MovingPathAnimation*)AnimationsParser::GetAnimation("BubDieByEnemy");
	BubDieAnimator *bda=new BubDieAnimator();
	bda->RegistCollitions(bda, newSprite);

	START_ANIMATOR( bda, newSprite, mpa, GetGameTime() );
	DESTROY_ANIMATOR( _this );
}


void BubJumpAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BubJumpAnimator * _this = (BubJumpAnimator*)args;
	DASSERT( anim==_this );

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	MovingAnimation *fra= (MovingAnimation*)AnimationsParser::GetAnimation("BubFalling");
	Sprite *n_sprite=new Sprite(_this->GetSprite()->GetX(),_this->GetSprite()->GetY(),
		_this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("BubWalk"), 
						Terrain::GetActionLayer(), _this->GetSprite()->GoesLeft());
	n_sprite->SetFrame(0);
	BubFallingAnimator *frtor=new BubFallingAnimator();
	n_sprite->AddStopFallingListener(frtor);
	frtor->RegistCollitions(frtor, n_sprite);
	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( _this );
}

/////////////////////////BubDieAnimator

BubDieAnimator::BubDieAnimator(){
	this->SetOnFinish(OnFinishCallback, (void*)this);
}

void BubDieAnimator::RegistCollitions(Animator *anim, Sprite *spr){
}

void BubDieAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BubDieAnimator * _this = (BubDieAnimator*)args;
	DASSERT( anim==_this );

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	DASSERT( _this->GetAnimation() && _this->GetSprite() );

	animid_t id = _this->GetAnimation()->GetId();

	DESTROY_ANIMATOR( _this );

}
