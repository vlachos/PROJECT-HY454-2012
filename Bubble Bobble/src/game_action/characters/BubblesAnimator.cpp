#include "GameActionUtilities.h"
#include "BubblesAnimator.h"
#include "AnimatorHolder.h"
#include "MemoryManage.h"
#include "CollisionChecker.h"
#include "AnimationsParser.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"

//////////////////////////////BubBubbleBlastOffAnimator

BubBubbleBlastOffAnimator::BubBubbleBlastOffAnimator(){
	this->SetOnFinish( OnFinishCallback, (void*)this );
}

void BubBubbleBlastOffAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BubBubbleBlastOffAnimator * _this = (BubBubbleBlastOffAnimator*)args;
	DASSERT( anim==_this );
	DASSERT( _this->GetAnimation() && _this->GetSprite() );
	
	REMOVE_FROM_ACTION_ANIMATOR( _this );

	MovingPathAnimation *mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("Bubbles");

	Sprite *sprite=new Sprite(
								mpa->GetPath()[0].x,
								mpa->GetPath()[0].y,
								false,
								AnimationFilmHolder::GetFilm( "BubBubble" ), 
								Terrain::GetActionLayer(), 
								true
							);
	BubBubbleAnimator *bbar=new BubBubbleAnimator();

	START_ANIMATOR(bbar, sprite, mpa, GetGameTime() );
	DESTROY_ANIMATOR( _this );
}

/////////////////////////////BubBubbleAnimator

BubBubbleAnimator::BubBubbleAnimator(){
	this->SetOnFinish( OnFinishCallback, (void*)this );
}

void BubBubbleAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BubBubbleAnimator * _this = (BubBubbleAnimator*)args;
	DASSERT( anim==_this );
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );
}