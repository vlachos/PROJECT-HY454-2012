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

std::vector<InvisibleSprites::InvisibleDrivers> InvisibleSprites::driversForFrameRange;
std::vector<InvisibleSprites::InvisibleDrivers> InvisibleSprites::wrapAroundDrivers;
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

	box.clear();
	box.push_back( Rect(0, 0, 2, 32) );
	af = new AnimationFilm(0, box, "invisibleDriver_11");
	spr = new Sprite( 338, 380, false, af, Terrain::GetActionLayer(), true);
	animationFilmHolderLateDestraction.push_back(af);
	driversForFrameRange.push_back( InvisibleDrivers( spr, InvisibleDrivererGoDownFRA ) );

	box.clear();
	box.push_back( Rect(0, 0, 2, 32) );
	af = new AnimationFilm(0, box, "invisibleDriver_10");
	spr = new Sprite( 175, 380, false, af, Terrain::GetActionLayer(), true);
	animationFilmHolderLateDestraction.push_back(af);
	driversForFrameRange.push_back( InvisibleDrivers( spr, InvisibleDrivererGoDownFRA ) );
	
	box.clear();
	box.push_back( Rect(0, 0, 100, 30) );
	af = new AnimationFilm(0, box, "invisibleDriver_9");
	spr = new Sprite( 40, 404, false, af, Terrain::GetActionLayer(), true);
	animationFilmHolderLateDestraction.push_back(af);
	driversForFrameRange.push_back( InvisibleDrivers( spr, InvisibleDrivererGoRightFRA ) );

	box.clear();
	box.push_back( Rect(0, 0, 100, 34) );
	af = new AnimationFilm(0, box, "invisibleDriver_8");
	spr = new Sprite( 383, 409, false, af, Terrain::GetActionLayer(), true);
	animationFilmHolderLateDestraction.push_back(af);
	driversForFrameRange.push_back( InvisibleDrivers( spr, InvisibleDrivererGoLeftFRA ) );

	box.clear();
	box.push_back( Rect(0, 0, 30, 90) );
	af = new AnimationFilm(0, box, "invisibleDriver_7");
	spr = new Sprite( 453, 292, false, af, Terrain::GetActionLayer(), true);
	animationFilmHolderLateDestraction.push_back(af);
	driversForFrameRange.push_back( InvisibleDrivers( spr, InvisibleDrivererGoDownFRA ) );

	box.clear();
	box.push_back( Rect(0, 0, 377, 27) );
	af = new AnimationFilm(0, box, "invisibleDriver_6");
	spr = new Sprite( 40, 326, false, af, Terrain::GetActionLayer(), false);
	animationFilmHolderLateDestraction.push_back(af);
	driversForFrameRange.push_back( InvisibleDrivers( spr, InvisibleDrivererGoRightFRA ) );

	box.clear();
	box.push_back( Rect(0, 0, 30, 87) );
	af = new AnimationFilm(0, box, "invisibleDriver_5");
	spr = new Sprite( 40, 220, false, af, Terrain::GetActionLayer(), false);
	animationFilmHolderLateDestraction.push_back(af);
	driversForFrameRange.push_back( InvisibleDrivers( spr, InvisibleDrivererGoDownFRA ) );

	box.clear();
	box.push_back( Rect(0, 0, 366, 27) );
	af = new AnimationFilm(0, box, "invisibleDriver_4");
	spr = new Sprite( 118, 247, false, af, Terrain::GetActionLayer(), true);
	animationFilmHolderLateDestraction.push_back(af);
	driversForFrameRange.push_back( InvisibleDrivers( spr, InvisibleDrivererGoLeftFRA ) );

	box.clear();
	box.push_back( Rect(0, 0, 30, 90) );
	af = new AnimationFilm(0, box, "invisibleDriver_3");
	spr = new Sprite( 452, 137, false, af, Terrain::GetActionLayer(), true);
	animationFilmHolderLateDestraction.push_back(af);
	driversForFrameRange.push_back( InvisibleDrivers( spr, InvisibleDrivererGoDownFRA ) );

	box.clear();
	box.push_back( Rect(0, 0, 360, 24) );
	af = new AnimationFilm(0, box, "invisibleDriver_2");
	spr = new Sprite( 39, 168, false, af, Terrain::GetActionLayer(), false);
	animationFilmHolderLateDestraction.push_back(af);
	driversForFrameRange.push_back( InvisibleDrivers( spr, InvisibleDrivererGoRightFRA ) );

	box.clear();
	box.push_back( Rect(0, 0, 30, 90) );
	af = new AnimationFilm(0, box, "invisibleDriver_1");
	spr = new Sprite( 40, 57, false, af, Terrain::GetActionLayer(), false);
	animationFilmHolderLateDestraction.push_back(af);
	driversForFrameRange.push_back( InvisibleDrivers( spr, InvisibleDrivererGoDownFRA ) );

	box.clear();
	box.push_back( Rect(0, 0, 362, 24) );
	af = new AnimationFilm(0, box, "invisibleDriver_0");
	spr = new Sprite( 115, 92, false, af, Terrain::GetActionLayer(), false);
	animationFilmHolderLateDestraction.push_back(af);
	driversForFrameRange.push_back( InvisibleDrivers( spr, InvisibleDrivererGoLeftFRA ) );
	

	box.clear();
	box.push_back( Rect(0, 0, 12, 2) );
	af = new AnimationFilm(0, box, "invisibleDriver_wrapAround2");
	spr = new Sprite( 335, 450, false, af, Terrain::GetActionLayer(), true);
	animationFilmHolderLateDestraction.push_back(af);
	wrapAroundDrivers.push_back( InvisibleDrivers( spr, InvisibleDrivererWrapAround2 ) );

	box.clear();
	box.push_back( Rect(0, 0, 12, 2) );
	af = new AnimationFilm(0, box, "invisibleDriver_wrapAround1");
	spr = new Sprite( 173, 450, false, af, Terrain::GetActionLayer(), true);
	animationFilmHolderLateDestraction.push_back(af);
	wrapAroundDrivers.push_back( InvisibleDrivers( spr, InvisibleDrivererWrapAround1 ) );
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
	return driversForFrameRange;
}

std::vector<InvisibleSprites::InvisibleDrivers> InvisibleSprites::GetInvisibleWrapAroundDrivers(){
	return wrapAroundDrivers;
}