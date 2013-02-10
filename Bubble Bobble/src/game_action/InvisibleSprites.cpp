#include <list>
#include <algorithm>
#include "InvisibleSprites.h"
#include "MemoryManage.h"
#include "Metrics.h"
#include "AnimationFilm.h"
#include "FrameRangeAnimation.h"
#include "FrameRangeAnimator.h"
#include "Terrain.h"
#include "BubblesAnimator.h"
#include "StageStartingAttributesParser.h"

std::vector<InvisibleSprites::InvisibleDrivers> InvisibleSprites::driversForFrameRange;
std::vector<InvisibleSprites::InvisibleDrivers> InvisibleSprites::wrapAroundDrivers;
std::vector<InvisibleSprites::InvisibleDrivers> InvisibleSprites::MightaBubbleBreakers;
InvisibleSprites*								InvisibleSprites::singletonPtr;

static std::list<AnimationFilm*>				animationFilmHolderLateDestraction;

namespace InvisibleSpritesDelete{

	struct DeleteAnimationFilm{
		void operator()(AnimationFilm* af){
			delete af;
		}
	};

	struct DeleteInvisibleDrivers{
		void operator()(InvisibleSprites::InvisibleDrivers af){
			af.sprite->Destroy();
		}
	};

}

static void InvisibleDrivererGoDownFRA(Sprite *obj, Sprite *driver, void *args){
	DASSERT( driver && obj && args );
	FrameRangeAnimation* anim = ((FrameRangeAnimator*) args)->GetAnimation();

	if(anim->GetDy()<=0){
		int d;
		if(anim->GetDx()>0)
			d=anim->GetDx();
		else if(anim->GetDx()<0)
			d=-anim->GetDx();
		else 
			d=-anim->GetDy();
		anim->SetDy(d);	
		anim->SetDx(0);	
	}
}

static void InvisibleDrivererGoUpFRA(Sprite *obj, Sprite *driver, void *args){
	DASSERT( driver && obj && args );
	FrameRangeAnimation* anim = ((FrameRangeAnimator*) args)->GetAnimation();

	if(anim->GetDy()>=0){
		int d;
		if(anim->GetDx()>0)
			d=-anim->GetDx();
		else if(anim->GetDx()<0)
			d=anim->GetDx();
		else 
			d=-anim->GetDy();
		anim->SetDy(d);	
		anim->SetDx(0);	
	}
}

static void InvisibleDrivererGoLeftFRA(Sprite *obj, Sprite *driver, void *args){
	DASSERT( driver && obj && args );
	FrameRangeAnimation* anim = ((FrameRangeAnimator*) args)->GetAnimation();
	if(anim->GetDx()>=0){
		int d;
		if(anim->GetDy()>0)
			d=-anim->GetDy();
		else if(anim->GetDy()<0)
			d=anim->GetDy();
		else 
			d=-anim->GetDx();
		anim->SetDx(d);	
		anim->SetDy(0);	
		obj->SetGoesLeft(true);
	}
}

static void InvisibleDrivererGoRightFRA(Sprite *obj, Sprite *driver, void *args){
	DASSERT( driver && obj && args );
	FrameRangeAnimation* anim = ((FrameRangeAnimator*) args)->GetAnimation();
	if(anim->GetDx()<=0){
		int d;
		if(anim->GetDy()>0)
			d=anim->GetDy();
		else if(anim->GetDy()<0)
			d=-anim->GetDy();
		else 
			d=-anim->GetDx();
		anim->SetDx(d);	
		anim->SetDy(0);	
		obj->SetGoesLeft(false);
	}
}

static void InvisibleDrivererWrapAround1(Sprite *obj, Sprite *driver, void *args){
	obj->SetX(160);
	obj->SetY(0);
}

static void InvisibleDrivererWrapAround2(Sprite *obj, Sprite *driver, void *args){
	obj->SetX(323);
	obj->SetY(0);
}



InvisibleSprites::InvisibleSprites(){
	AnimationFilm* af;
	Sprite* spr;
	std::vector<Rect> box;

	char index=0;
	std::list<StageStartingAttributesParser::StartingPosition_t> startingPos = StageStartingAttributesParser::GetInvisibleSpritesPos(1);
	for(std::list<StageStartingAttributesParser::StartingPosition_t>::const_iterator ci=startingPos.begin(); ci!=startingPos.end(); ++ci, ++index){
		box.clear();
		box.push_back( Rect(0, 0, ci->w, ci->h) );
		af = new AnimationFilm(0, box, (std::string("invisibleDriver_") + index).c_str() );
		spr = new Sprite( ci->x, ci->y, false, af, Terrain::GetActionLayer(), true);
		animationFilmHolderLateDestraction.push_back(af);
		std::cout<< ci->w<<"\n";
		switch(ci->d){
			case StageStartingAttributesParser::directionDrive_Down: driversForFrameRange.push_back( InvisibleDrivers( spr, InvisibleDrivererGoDownFRA ) );
																	break;
			case StageStartingAttributesParser::directionDrive_Up: driversForFrameRange.push_back( InvisibleDrivers( spr, InvisibleDrivererGoUpFRA ) );
																	break;
			case StageStartingAttributesParser::directionDrive_Right: driversForFrameRange.push_back( InvisibleDrivers( spr, InvisibleDrivererGoRightFRA ) );
																	break;
			case StageStartingAttributesParser::directionDrive_Left: driversForFrameRange.push_back( InvisibleDrivers( spr, InvisibleDrivererGoLeftFRA ) );
																	break;
			default: DASSERT(false);
		}
	}

	box.clear();
	box.push_back( Rect(0, 0,42, 2) );
	af = new AnimationFilm(0, box, "invisibleDriver_wrapAround2");
	spr = new Sprite( 320, 450, false, af, Terrain::GetActionLayer(), true);
	animationFilmHolderLateDestraction.push_back(af);
	wrapAroundDrivers.push_back( InvisibleDrivers( spr, InvisibleDrivererWrapAround2 ) );

	box.clear();
	box.push_back( Rect(0, 0, 42, 2) );
	af = new AnimationFilm(0, box, "invisibleDriver_wrapAround1");
	spr = new Sprite( 158, 450, false, af, Terrain::GetActionLayer(), true);
	animationFilmHolderLateDestraction.push_back(af);
	wrapAroundDrivers.push_back( InvisibleDrivers( spr, InvisibleDrivererWrapAround1 ) );

	box.clear();
	box.push_back( Rect(0, 0, 20, 450) );
	af = new AnimationFilm(0, box, "invisibleDriver_mightaBubbleBreaker1");
	spr = new Sprite( 0, 0, false, af, Terrain::GetActionLayer(), true);
	animationFilmHolderLateDestraction.push_back(af);
	MightaBubbleBreakers.push_back( InvisibleDrivers( spr, 0 ) );

	box.clear();
	box.push_back( Rect(0, 0, 20, 450) );
	af = new AnimationFilm(0, box, "invisibleDriver_mightaBubbleBreaker2");
	spr = new Sprite( 490, 0, false, af, Terrain::GetActionLayer(), true);
	animationFilmHolderLateDestraction.push_back(af);
	MightaBubbleBreakers.push_back( InvisibleDrivers( spr, 0 ) );
}

InvisibleSprites::~InvisibleSprites(){
	std::for_each(
					animationFilmHolderLateDestraction.begin(),
					animationFilmHolderLateDestraction.end(),
					InvisibleSpritesDelete::DeleteAnimationFilm()
				);
	animationFilmHolderLateDestraction.clear();

	std::for_each(
					driversForFrameRange.begin(),
					driversForFrameRange.end(),
					InvisibleSpritesDelete::DeleteInvisibleDrivers()
				);
	driversForFrameRange.clear();

	std::for_each(
					wrapAroundDrivers.begin(),
					wrapAroundDrivers.end(),
					InvisibleSpritesDelete::DeleteInvisibleDrivers()
				);
	wrapAroundDrivers.clear();
}

std::vector<InvisibleSprites::InvisibleDrivers> InvisibleSprites::GetInvisibleBubbleDriversForFrameRange(){
	DASSERT(!driversForFrameRange.empty());
	return driversForFrameRange;
}

std::vector<InvisibleSprites::InvisibleDrivers> InvisibleSprites::GetInvisibleWrapAroundDrivers(){
	DASSERT(!wrapAroundDrivers.empty());
	return wrapAroundDrivers;
}

std::vector<InvisibleSprites::InvisibleDrivers> InvisibleSprites::GetInvisibleMightaBubbleBreakers(){
	DASSERT(!MightaBubbleBreakers.empty());
	return MightaBubbleBreakers;
}