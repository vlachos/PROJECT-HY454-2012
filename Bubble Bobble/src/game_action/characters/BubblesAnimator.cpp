#include <math.h>
#include "GameActionUtilities.h"
#include "BubblesAnimator.h"
#include "AnimatorHolder.h"
#include "MemoryManage.h"
#include "CollisionChecker.h"
#include "AnimationsParser.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"


/////////////////////////////static functios
static int getClosestIndexFromPath(int x, int y, const std::vector<PathEntry>& path){
	double minDistance=1024;
	int index=-1;
	for(unsigned int i=0; i<path.size(); ++i){
		double distance = sqrt( pow( double(path[i].x - x), 2 ) + pow( double(path[i].y - y), 2 ) );
		if( distance < minDistance ){
			minDistance = distance;
			index=i;
		}
	}

	return index;
}

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
	int startIndex = getClosestIndexFromPath( _this->GetSprite()->GetX(),  _this->GetSprite()->GetY(), mpa->GetPath() );
	Sprite *sprite=new Sprite(
								mpa->GetPath()[startIndex].x,
								mpa->GetPath()[startIndex].y,
								false,
								AnimationFilmHolder::GetFilm( "BubBubble" ), 
								Terrain::GetActionLayer(), 
								true
							);
	BubBubbleAnimator *bbar=new BubBubbleAnimator();
	bbar->SetCurrIndex( startIndex );

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