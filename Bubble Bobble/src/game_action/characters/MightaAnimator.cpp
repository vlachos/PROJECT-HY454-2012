#include "GameActionUtilities.h"
#include "MemoryManage.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "CollisionChecker.h"
#include "MightaAnimator.h"


////////////////MightaStandAnimator

MightaStandAnimator::MightaStandAnimator(){
}

void MightaStandAnimator::OnFinishCallback(Animator* anim, void* args){}


void MightaStandAnimator::OnStartFalling(Sprite* sprite){}

////////////////MightaWalkingAnimator

MightaWalkingAnimator::MightaWalkingAnimator(void) {
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void MightaWalkingAnimator::OnStartFalling(Sprite * sprite){
	
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	FrameRangeAnimation *fra= (FrameRangeAnimation*)AnimationsParser::GetAnimation("MightaFalling");
	Sprite *n_sprite=new Sprite(this->GetSprite()->GetX(),this->GetSprite()->GetY(),
						this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("MightaWalk"), 
						Terrain::GetActionLayer(), this->GetSprite()->GoesLeft());
	n_sprite->SetFrame(0);

	MightaFallingAnimator *frtor = new MightaFallingAnimator();
	n_sprite->AddStopFallingListener(frtor);

	std::vector<Animator*> enemy = AnimatorHolder::GetAnimators(mightaStandAnimator_t);
	for(unsigned int i=0; i<enemy.size(); ++i){
		CollisionChecker::Register(n_sprite, ( (MightaStandAnimator*)enemy[i] )->GetSprite(), 0, 0);
	}
	
	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( this );
}


void MightaWalkingAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	MightaWalkingAnimator * _this = (MightaWalkingAnimator*)args;
	DASSERT( anim==_this );
	DASSERT( _this->GetAnimation() && _this->GetSprite());

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	animid_t id = _this->GetAnimation()->GetId();

	Sprite * newSprite = _this->GetSprite();
	newSprite->ClearListeners();

	FrameRangeAnimation *ma = (FrameRangeAnimation*) AnimationsParser::GetAnimation("MightaStand");
	newSprite->SetFrame(0);
	MightaStandAnimator* mar = new MightaStandAnimator();
	mar->SetOnFinish(MightaStandAnimator::OnFinishCallback, 0);

	START_ANIMATOR( mar, newSprite, ma, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( _this );
}


////////////////MightaFallingAnimator

MightaFallingAnimator::MightaFallingAnimator(){
}

void MightaFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	FrameRangeAnimation *fra= (FrameRangeAnimation*)AnimationsParser::GetAnimation("MightaStand");
	Sprite *n_sprite=new Sprite(this->GetSprite()->GetX(),this->GetSprite()->GetY(),
		this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("MightaWalk"), 
						Terrain::GetActionLayer(), this->GetSprite()->GoesLeft());

	MightaStandAnimator *frtor = new MightaStandAnimator();

	std::vector<Animator*> enemy = AnimatorHolder::GetAnimators(mightaStandAnimator_t);
	for(unsigned int i=0; i<enemy.size(); ++i){
		CollisionChecker::Register(n_sprite, ( (MightaStandAnimator*)enemy[i] )->GetSprite(), 0, 0);
	}

	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( this );
}


////////////////MightaJumpAnimator
