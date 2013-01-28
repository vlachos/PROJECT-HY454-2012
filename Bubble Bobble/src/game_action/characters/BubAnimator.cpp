#include "BubAnimator.h"
#include "MemoryManage.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "ZenChanAnimator.h"
#include "CollisionChecker.h"
#include "BubblesAnimator.h"

////////////////BubStandAnimator

BubStandAnimator::BubStandAnimator(){

}

void BubStandAnimator::OnFinishCallback(Animator* anim, void* args){



}

void BubStandAnimator::OnOpenMouth(void){
	AnimatorHolder::MarkAsSuspended(this);
	AnimatorHolder::Cancel(this);
	CollisionChecker::Cancel(this->GetSprite());

	timestamp_t timestamp = GetGameTime();
	DASSERT( timestamp>0 );

	FrameRangeAnimation *fra = (FrameRangeAnimation*) AnimationsParser::GetAnimation("BubOpenMouth");
	Sprite *n_sprite=new Sprite(this->GetSprite()->GetX(),this->GetSprite()->GetY(),
						this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("BubOpenMouth"), 
						Terrain::GetActionLayer(), this->GetSprite()->GoesLeft());

	BubOpenMouthAnimator *bomar = new BubOpenMouthAnimator();
	n_sprite->AddStartFallingListener(bomar);

	std::vector<Animator*> enemy = AnimatorHolder::GetAnimators(zenChanStandAnimator_t);
	for(unsigned int i=0; i<enemy.size(); ++i){
		CollisionChecker::Register(n_sprite, ( (ZenChanStandAnimator*)enemy[i] )->GetSprite(), 0, 0);
	}

	bomar->Start(n_sprite,fra,GetGameTime());
	AnimatorHolder::Register(bomar);
	AnimatorHolder::MarkAsRunning(bomar);

	FrameRangeAnimation *frab = 
		(FrameRangeAnimation*) AnimationsParser::GetAnimation(
													this->GetSprite()->GoesLeft() ? 
													"BubBubbleLeft" : 
													"BubBubbleRight"
													);
	Sprite *n_spriteb=new Sprite(
								this->GetSprite()->GetX(),
								this->GetSprite()->GetY(),
								this->GetSprite()->IsGravityAddicted(),
								AnimationFilmHolder::GetFilm( "BubBubble" ), 
								Terrain::GetActionLayer(), 
								this->GetSprite()->GoesLeft()
								);

	BubBubbleAnimator *bbar=new BubBubbleAnimator();

	bbar->Start(n_spriteb, frab, GetGameTime());
	AnimatorHolder::Register(bbar);
	AnimatorHolder::MarkAsRunning(bbar);

	this->GetSprite()->Destroy();
	this->GetAnimation()->Destroy();
	this->Destroy();
}

////////////////BubWalkingAnimator


BubWalkingAnimator::BubWalkingAnimator(void) {
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void BubWalkingAnimator::OnStartFalling(Sprite * sprite){
	
	DASSERT( sprite == this->GetSprite() );
	AnimatorHolder::MarkAsSuspended(this);

	AnimatorHolder::Cancel(this);
	CollisionChecker::Cancel(this->GetSprite());
	timestamp_t timestamp = GetGameTime();
	DASSERT( timestamp>0 );


	MovingAnimation *fra= (MovingAnimation*)AnimationsParser::GetAnimation("BubFalling");
	Sprite *n_sprite=new Sprite(this->GetSprite()->GetX(),this->GetSprite()->GetY(),
						this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("BubWalk"), 
						Terrain::GetActionLayer(), this->GetSprite()->GoesLeft());
	n_sprite->SetFrame(0);

	BubFallingAnimator *frtor=new BubFallingAnimator();
	n_sprite->AddStopFallingListener(frtor);

	this->GetSprite()->Destroy();
	this->GetAnimation()->Destroy();
	this->Destroy();

	std::vector<Animator*> enemy = AnimatorHolder::GetAnimators(zenChanStandAnimator_t);
	for(unsigned int i=0; i<enemy.size(); ++i){
		CollisionChecker::Register(n_sprite, ( (ZenChanStandAnimator*)enemy[i] )->GetSprite(), 0, 0);
	}

	frtor->Start(n_sprite,fra,GetGameTime());
	AnimatorHolder::Register(frtor);
	AnimatorHolder::MarkAsRunning(frtor);
	
}


void BubWalkingAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BubWalkingAnimator * _this = (BubWalkingAnimator*)args;
	DASSERT( anim==_this );
	timestamp_t timestamp = GetGameTime();
	DASSERT( timestamp>0 );
	DASSERT( _this->GetAnimation() );
	DASSERT( _this->GetSprite() );
	AnimatorHolder::MarkAsSuspended(_this);
	AnimatorHolder::Cancel(_this);
	CollisionChecker::Cancel(_this->GetSprite());

	animid_t id = _this->GetAnimation()->GetId();

	Sprite * newSprite = _this->GetSprite();
	newSprite->RemoveStartFallingListener(_this);
	_this->GetAnimation()->Destroy();
	_this->Destroy(); 

	MovingAnimation *ma = (MovingAnimation*) AnimationsParser::GetAnimation("BubStand");
	newSprite->SetFrame(0);

	BubStandAnimator* mar = new BubStandAnimator();
	mar->SetOnFinish(BubStandAnimator::OnFinishCallback, 0);
	mar->Start(newSprite, ma, timestamp);
	
	AnimatorHolder::Register(mar);
	AnimatorHolder::MarkAsRunning(mar);

}

void BubWalkingAnimator::OnCollisionWithEnemy(Sprite *bub, Sprite *enem, void * args){
	DASSERT(args);
	BubWalkingAnimator * _this = (BubWalkingAnimator*)args;
	DASSERT( _this );
	timestamp_t timestamp = GetGameTime();
	DASSERT( timestamp>0 );
	AnimatorHolder::MarkAsSuspended(_this);
	AnimatorHolder::Cancel(_this);
	CollisionChecker::Cancel(_this->GetSprite());

	DASSERT( _this->GetAnimation() );
	DASSERT( _this->GetSprite() );

	animid_t id = _this->GetAnimation()->GetId();

	Sprite * newSprite = _this->GetSprite();
	newSprite->RemoveStartFallingListener(_this);
	_this->GetAnimation()->Destroy();
	_this->GetSprite()->Destroy();
	_this->Destroy();


}

void BubWalkingAnimator::OnOpenMouth(void){
	AnimatorHolder::MarkAsSuspended(this);
	AnimatorHolder::Cancel(this);
	CollisionChecker::Cancel(this->GetSprite());

	timestamp_t timestamp = GetGameTime();
	DASSERT( timestamp>0 );

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

	std::vector<Animator*> enemy = AnimatorHolder::GetAnimators(zenChanStandAnimator_t);
	for(unsigned int i=0; i<enemy.size(); ++i){
		CollisionChecker::Register(n_sprite, ( (ZenChanStandAnimator*)enemy[i] )->GetSprite(), 0, 0);
	}

	this->GetSprite()->Destroy();
	this->GetAnimation()->Destroy();
	this->Destroy();

	bomar->Start(n_sprite,fra,GetGameTime());
	AnimatorHolder::Register(bomar);
	AnimatorHolder::MarkAsRunning(bomar);
}

////////////////BubFallingAnimator

BubFallingAnimator::BubFallingAnimator(){
	
}

void BubFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );

	AnimatorHolder::MarkAsSuspended(this);
	AnimatorHolder::Cancel(this);
	CollisionChecker::Cancel(sprite);
	timestamp_t timestamp = GetGameTime();
	DASSERT( timestamp>0 );


	MovingAnimation *fra= (MovingAnimation*)AnimationsParser::GetAnimation("BubStand");
	Sprite *n_sprite=new Sprite(this->GetSprite()->GetX(),this->GetSprite()->GetY(),
		this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("BubWalk"), 
						Terrain::GetActionLayer(), this->GetSprite()->GoesLeft());

	BubStandAnimator *frtor=new BubStandAnimator();

	this->GetSprite()->Destroy();
	this->GetAnimation()->Destroy();
	this->Destroy();

	std::vector<Animator*> enemy = AnimatorHolder::GetAnimators(zenChanStandAnimator_t);
	for(unsigned int i=0; i<enemy.size(); ++i){
		CollisionChecker::Register(n_sprite, ( (ZenChanStandAnimator*)enemy[i] )->GetSprite(), 0, 0);
	}

	frtor->Start(n_sprite,fra,GetGameTime());
	AnimatorHolder::Register(frtor);
	AnimatorHolder::MarkAsRunning(frtor);
}

///////////////////////BubOpenMouthAnimator

BubOpenMouthAnimator::BubOpenMouthAnimator(){
	this->SetOnFinish( OnFinishCallback , (void*)this);
}


void BubOpenMouthAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BubOpenMouthAnimator * _this = (BubOpenMouthAnimator*)args;
	DASSERT( anim==_this );

	AnimatorHolder::MarkAsSuspended(_this);
	AnimatorHolder::Cancel(_this);
	CollisionChecker::Cancel(_this->GetSprite());
	timestamp_t timestamp = GetGameTime();
	DASSERT( timestamp>0 );


	MovingAnimation *fra= (MovingAnimation*)AnimationsParser::GetAnimation("BubStand");
	Sprite *n_sprite=new Sprite(_this->GetSprite()->GetX(),_this->GetSprite()->GetY(),
		_this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("BubWalk"), 
						Terrain::GetActionLayer(), _this->GetSprite()->GoesLeft());

	BubStandAnimator *frtor=new BubStandAnimator();

	_this->GetSprite()->Destroy();
	_this->GetAnimation()->Destroy();
	_this->Destroy();

	std::vector<Animator*> enemy = AnimatorHolder::GetAnimators(zenChanStandAnimator_t);
	for(unsigned int i=0; i<enemy.size(); ++i){
		CollisionChecker::Register(n_sprite, ( (ZenChanStandAnimator*)enemy[i] )->GetSprite(), 0, 0);
	}

	frtor->Start(n_sprite,fra,GetGameTime());
	AnimatorHolder::Register(frtor);
	AnimatorHolder::MarkAsRunning(frtor);
}

void BubOpenMouthAnimator::OnStartFalling(Sprite * sprite){

}

///////////////////////BubOpenMouthAnimator

BubJumpAnimator::BubJumpAnimator(){
}

void BubJumpAnimator::OnCollisionWithEnemy(Sprite *bub, Sprite *enem, void * args){
	DASSERT(args);
	BubJumpAnimator * _this = (BubJumpAnimator*)args;
	DASSERT( _this );
	timestamp_t timestamp = GetGameTime();
	DASSERT( timestamp>0 );
	AnimatorHolder::MarkAsSuspended(_this);
	AnimatorHolder::Cancel(_this);
	CollisionChecker::Cancel(_this->GetSprite());

	DASSERT( _this->GetAnimation() );
	DASSERT( _this->GetSprite() );

	animid_t id = _this->GetAnimation()->GetId();

	Sprite * newSprite = _this->GetSprite();
	_this->GetAnimation()->Destroy();
	_this->GetSprite()->Destroy();
	_this->Destroy();


}

void BubJumpAnimator::OnFinishCallback(Animator* anim, void* args){

}
