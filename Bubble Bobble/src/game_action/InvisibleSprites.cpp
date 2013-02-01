#include "InvisibleSprites.h"
#include "MemoryManage.h"
#include "Metrics.h"
#include "AnimationFilm.h"
#include "FrameRangeAnimation.h"
#include "Terrain.h"
#include "BubblesAnimator.h"

static std::vector<InvisibleSprites::InvisibleDrivers> drivers;
static std::vector<InvisibleSprites::InvisibleDrivers> wrapAroundDrivers;

static void InvisibleDrivererGoDown(Sprite *obj, Sprite *driver, void *args){
	std::cout<<"down\n";
	DASSERT( driver && obj && args );
	FrameRangeAnimation* anim = ((BubBubbleAnimator*) args)->GetAnimation();

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

static void InvisibleDrivererGoLeft(Sprite *obj, Sprite *driver, void *args){
	std::cout<<"left\n";
	DASSERT( driver && obj && args );
	FrameRangeAnimation* anim = ((BubBubbleAnimator*) args)->GetAnimation();
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

static void InvisibleDrivererGoRight(Sprite *obj, Sprite *driver, void *args){
	DASSERT( driver && obj && args );
	FrameRangeAnimation* anim = ((BubBubbleAnimator*) args)->GetAnimation();
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
	std::cout<<"wrap\n";
	obj->SetX(160);
	obj->SetY(5);
	InvisibleDrivererGoDown( driver, obj, args );
}

void InvisibleSprites::CreateInvisibleDrivers(){
	AnimationFilm* af;
	Sprite* spr;
	std::vector<Rect> box;
	
	box.clear();
	box.push_back( Rect(0, 0, 362, 44) );
	af = new AnimationFilm(0, box, "invisibleDriver_0");
	spr = new Sprite( 115, 72, false, af, Terrain::GetActionLayer(), false);
	drivers.push_back( InvisibleDrivers( spr, InvisibleDrivererGoLeft ) );

	box.clear();
	box.push_back( Rect(0, 0, 42, 95) );
	af = new AnimationFilm(0, box, "invisibleDriver_1");
	spr = new Sprite( 30, 54, false, af, Terrain::GetActionLayer(), false);
	drivers.push_back( InvisibleDrivers( spr, InvisibleDrivererGoDown ) );
	
	box.clear();
	box.push_back( Rect(0, 0, 370, 44) );
	af = new AnimationFilm(0, box, "invisibleDriver_2");
	spr = new Sprite( 30, 152, false, af, Terrain::GetActionLayer(), false);
	drivers.push_back( InvisibleDrivers( spr, InvisibleDrivererGoRight ) );
	
	box.clear();
	box.push_back( Rect(0, 0, 61, 95) );
	af = new AnimationFilm(0, box, "invisibleDriver_3");
	spr = new Sprite( 420, 137, false, af, Terrain::GetActionLayer(), true);
	drivers.push_back( InvisibleDrivers( spr, InvisibleDrivererGoDown ) );
	
	box.clear();
	box.push_back( Rect(0, 0, 362, 44) );
	af = new AnimationFilm(0, box, "invisibleDriver_4");
	spr = new Sprite( 118, 237, false, af, Terrain::GetActionLayer(), true);
	drivers.push_back( InvisibleDrivers( spr, InvisibleDrivererGoLeft ) );
	
	box.clear();
	box.push_back( Rect(0, 0, 42, 95) );
	af = new AnimationFilm(0, box, "invisibleDriver_5");
	spr = new Sprite( 30, 217, false, af, Terrain::GetActionLayer(), false);
	drivers.push_back( InvisibleDrivers( spr, InvisibleDrivererGoDown ) );

	box.clear();
	box.push_back( Rect(0, 0, 370, 44) );
	af = new AnimationFilm(0, box, "invisibleDriver_6");
	spr = new Sprite( 30, 317, false, af, Terrain::GetActionLayer(), false);
	drivers.push_back( InvisibleDrivers( spr, InvisibleDrivererGoRight ) );

	box.clear();
	box.push_back( Rect(0, 0, 50, 95) );
	af = new AnimationFilm(0, box, "invisibleDriver_7");
	spr = new Sprite( 430, 292, false, af, Terrain::GetActionLayer(), true);
	drivers.push_back( InvisibleDrivers( spr, InvisibleDrivererGoDown ) );

	box.clear();
	box.push_back( Rect(0, 0, 130, 45) );
	af = new AnimationFilm(0, box, "invisibleDriver_8");
	spr = new Sprite( 360, 397, false, af, Terrain::GetActionLayer(), true);
	drivers.push_back( InvisibleDrivers( spr, InvisibleDrivererGoLeft ) );

	box.clear();
	box.push_back( Rect(0, 0, 120, 55) );
	af = new AnimationFilm(0, box, "invisibleDriver_9");
	spr = new Sprite( 30, 382, false, af, Terrain::GetActionLayer(), true);
	drivers.push_back( InvisibleDrivers( spr, InvisibleDrivererGoRight ) );

	box.clear();
	box.push_back( Rect(0, 0, 10, 20) );
	af = new AnimationFilm(0, box, "invisibleDriver_10");
	spr = new Sprite( 155, 382, false, af, Terrain::GetActionLayer(), true);
	drivers.push_back( InvisibleDrivers( spr, InvisibleDrivererGoDown ) );

	box.clear();
	box.push_back( Rect(0, 0, 10, 20) );
	af = new AnimationFilm(0, box, "invisibleDriver_11");
	spr = new Sprite( 315, 382, false, af, Terrain::GetActionLayer(), true);
	drivers.push_back( InvisibleDrivers( spr, InvisibleDrivererGoDown ) );

	box.clear();
	box.push_back( Rect(0, 0, 10, 40) );
	af = new AnimationFilm(0, box, "invisibleDriver_wrapAround1");
	spr = new Sprite( 315, 407, false, af, Terrain::GetActionLayer(), true);
	wrapAroundDrivers.push_back( InvisibleDrivers( spr, InvisibleDrivererWrapAround1 ) );

	box.clear();
	box.push_back( Rect(0, 0, 10, 40) );
	af = new AnimationFilm(0, box, "invisibleDriver_wrapAround1");
	spr = new Sprite( 155, 407, false, af, Terrain::GetActionLayer(), true);
	wrapAroundDrivers.push_back( InvisibleDrivers( spr, InvisibleDrivererWrapAround1 ) );
}

void InvisibleSprites::DestroyInvisibleDrivers(){
	
}

std::vector<InvisibleSprites::InvisibleDrivers> InvisibleSprites::GetInvisibleBubbleDrivers(){
	return drivers;
}

std::vector<InvisibleSprites::InvisibleDrivers> InvisibleSprites::GetInvisibleWrapAroundDrivers(){
	return wrapAroundDrivers;
}