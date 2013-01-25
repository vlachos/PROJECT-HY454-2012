#include "BubAnimator.h"
#include "MemoryManage.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "ZenChanAnimator.h"

////////////////BubStandAnimator

BubStandAnimator::BubStandAnimator(){

}

void BubStandAnimator::OnFinishCallback(Animator* anim, void* args){



}

////////////////BubWalkingAnimator


BubWalkingAnimator::BubWalkingAnimator(void) {
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void BubWalkingAnimator::OnStartFalling(Sprite * sprite){
	
	DASSERT( sprite == this->GetSprite() );
	std::cout << "start\n";
	AnimatorHolder::MarkAsSuspended(this);
	std::cout << "end\n";
	AnimatorHolder::Cancel(this);
	CollisionChecker::Cancel(this->GetSprite());
	timestamp_t timestamp = GetGameTime();
	DASSERT( timestamp>0 );


	MovingAnimation *fra= (MovingAnimation*)AnimationsParser::GetAnimation("BubFalling");
	Sprite *n_sprite=new Sprite(this->GetSprite()->GetX(),this->GetSprite()->GetY(),
						this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("Bubwalk"), 
						Terrain::GetActionLayer(), this->GetSprite()->GoesLeft());
	n_sprite->SetFrame(6);

	BubFallingAnimator *frtor=new BubFallingAnimator();
	n_sprite->AddStopFallingListener(frtor);

	this->GetSprite()->Destroy();
	this->GetAnimation()->Destroy();
	this->Destroy();

	std::vector<Animator*> enemy = AnimatorHolder::GetAnimators(zenChanStandAnimator_t);
	for(int i=0; i<enemy.size(); ++i){
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
	AnimatorHolder::MarkAsSuspended(_this);
	AnimatorHolder::Cancel(_this);

	CollisionChecker::Cancel(_this->GetSprite());

	DASSERT( _this->GetAnimation() );
	DASSERT( _this->GetSprite() );

	animid_t id = _this->GetAnimation()->GetId();

	Sprite * newSprite = _this->GetSprite();
	newSprite->RemoveStartFallingListener(_this);
	_this->GetAnimation()->Destroy();
	_this->Destroy(); //meta

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
		this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("Bubwalk"), 
						Terrain::GetActionLayer(), this->GetSprite()->GoesLeft());

	BubStandAnimator *frtor=new BubStandAnimator();

	this->GetSprite()->Destroy();
	this->GetAnimation()->Destroy();
	this->Destroy();

	std::vector<Animator*> enemy = AnimatorHolder::GetAnimators(zenChanStandAnimator_t);
	for(int i=0; i<enemy.size(); ++i){
		CollisionChecker::Register(n_sprite, ( (ZenChanStandAnimator*)enemy[i] )->GetSprite(), 0, 0);
	}

	frtor->Start(n_sprite,fra,GetGameTime());
	AnimatorHolder::Register(frtor);
	AnimatorHolder::MarkAsRunning(frtor);
}
