#include "BubAnimator.h"
#include "MemoryManage.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"

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
	DASSERT( sprite = this->GetSprite() );

	AnimatorHolder::MarkAsSuspended(this);
	AnimatorHolder::Cancel(this);

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

	DASSERT( _this->GetAnimation() );
	DASSERT( _this->GetSprite() );

	animid_t id = _this->GetAnimation()->GetId();

	_this->GetAnimation()->Destroy();
	_this->Destroy(); //meta

	MovingAnimation *ma = (MovingAnimation*) AnimationsParser::GetAnimation("BubStand");
	_this->GetSprite()->SetFrame(0);

	BubStandAnimator* mar = new BubStandAnimator();
	mar->SetOnFinish(BubStandAnimator::OnFinishCallback, 0);
	mar->Start(_this->GetSprite(), ma, timestamp);
	
	AnimatorHolder::Register(mar);
	AnimatorHolder::MarkAsRunning(mar);
}


////////////////BubFallingAnimator

BubFallingAnimator::BubFallingAnimator(){

}

void BubFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite = this->GetSprite() );

	AnimatorHolder::MarkAsSuspended(this);
	AnimatorHolder::Cancel(this);

	timestamp_t timestamp = GetGameTime();
	DASSERT( timestamp>0 );


	FrameRangeAnimation *fra= (FrameRangeAnimation*)AnimationsParser::GetAnimation("Bubwalkright");
	Sprite *n_sprite=new Sprite(this->GetSprite()->GetX(),this->GetSprite()->GetY(),
						this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("Bubwalk"), 
						Terrain::GetActionLayer(), false);

	BubWalkingAnimator *frtor=new BubWalkingAnimator();

	n_sprite->AddStartFallingListener(frtor);

	this->GetSprite()->Destroy();
	this->GetAnimation()->Destroy();
	this->Destroy();

	frtor->Start(n_sprite,fra,GetGameTime());
	AnimatorHolder::Register(frtor);
	AnimatorHolder::MarkAsRunning(frtor);
}
