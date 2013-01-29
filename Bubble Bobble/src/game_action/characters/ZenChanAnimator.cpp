#include "GameActionUtilities.h"
#include "MemoryManage.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "CollisionChecker.h"
#include "ZenChanAnimator.h"


////////////////ZenChanStandAnimator

ZenChanStandAnimator::ZenChanStandAnimator(){}

void ZenChanStandAnimator::OnFinishCallback(Animator* anim, void* args){}

void ZenChanStandAnimator::OnStartFalling(Sprite* sprite){}


////////////////ZenChanWalkingAnimator

ZenChanWalkingAnimator::ZenChanWalkingAnimator(void) {
	this->SetOnFinish( OnFinishCallback , (void*)this);
}

void ZenChanWalkingAnimator::OnStartFalling(Sprite * sprite){
	
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	FrameRangeAnimation *fra= (FrameRangeAnimation*)AnimationsParser::GetAnimation("ZenChanFalling");
	Sprite *n_sprite=new Sprite(this->GetSprite()->GetX(),this->GetSprite()->GetY(),
						this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("ZenChanWalk"), 
						Terrain::GetActionLayer(), this->GetSprite()->GoesLeft());

	ZenChanFallingAnimator *frtor = new ZenChanFallingAnimator();
	n_sprite->AddStopFallingListener(frtor);

	std::vector<Animator*> enemy = AnimatorHolder::GetAnimators(zenChanStandAnimator_t);
	for(unsigned int i=0; i<enemy.size(); ++i){
		CollisionChecker::Register(n_sprite, ( (ZenChanStandAnimator*)enemy[i] )->GetSprite(), 0, 0);
	}
	
	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( this );
}


void ZenChanWalkingAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	ZenChanWalkingAnimator * _this = (ZenChanWalkingAnimator*)args;
	DASSERT( anim==_this );
	DASSERT( _this->GetAnimation() && _this->GetSprite());

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	animid_t id = _this->GetAnimation()->GetId();

	Sprite * newSprite = _this->GetSprite();
	newSprite->ClearListeners();

	FrameRangeAnimation *ma = (FrameRangeAnimation*) AnimationsParser::GetAnimation("ZenChanStand");
	newSprite->SetFrame(0);
	ZenChanStandAnimator* mar = new ZenChanStandAnimator();
	mar->SetOnFinish(ZenChanStandAnimator::OnFinishCallback, 0);

	START_ANIMATOR( mar, newSprite, ma, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( _this );
}


////////////////ZenChanFallingAnimator

ZenChanFallingAnimator::ZenChanFallingAnimator(){}

void ZenChanFallingAnimator::OnStopFalling(Sprite * sprite){
	DASSERT( sprite == this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( this );

	FrameRangeAnimation *fra= (FrameRangeAnimation*)AnimationsParser::GetAnimation("ZenChanStand");
	Sprite *n_sprite=new Sprite(this->GetSprite()->GetX(),this->GetSprite()->GetY(),
		this->GetSprite()->IsGravityAddicted(),AnimationFilmHolder::GetFilm("ZenChanWalk"), 
						Terrain::GetActionLayer(), this->GetSprite()->GoesLeft());

	ZenChanStandAnimator *frtor = new ZenChanStandAnimator();

	std::vector<Animator*> enemy = AnimatorHolder::GetAnimators(zenChanStandAnimator_t);
	for(unsigned int i=0; i<enemy.size(); ++i){
		CollisionChecker::Register(n_sprite, ( (ZenChanStandAnimator*)enemy[i] )->GetSprite(), 0, 0);
	}

	START_ANIMATOR( frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( this );
}


////////////////ZenChanJumpAnimator
