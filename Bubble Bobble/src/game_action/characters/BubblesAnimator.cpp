#include <math.h>
#include "GameActionUtilities.h"
#include "BubblesAnimator.h"
#include "AnimatorHolder.h"
#include "MemoryManage.h"
#include "CollisionChecker.h"
#include "AnimationsParser.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "ZenChanAnimator.h"
#include "MightaAnimator.h"

#define DESTROY_PAIR( pair )						\
	REMOVE_FROM_ACTION_ANIMATOR( pair->first );		\
	DESTROY_ANIMATOR( pair->first );				\
	REMOVE_FROM_ACTION_ANIMATOR( pair->second );	\
	DESTROY_ANIMATOR( pair->second );				\
	free(pair)

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

static std::vector<PathEntry> getPath(const int index, const std::vector<PathEntry>& constPath){
	std::vector<PathEntry> path;

	for(unsigned int i = index; i<constPath.size()-1; ++i){
		PathEntry entry;
		entry.x = constPath[i+1].x - constPath[i].x;
		entry.y = constPath[i+1].y - constPath[i].y;
		entry.delay =  constPath[i].delay;
		entry.frame = constPath[i].frame;
		path.push_back(entry);
	}
	return path;
}

//////////////////////////////BubBubbleBlastOffAnimator

BubBubbleBlastOffAnimator::BubBubbleBlastOffAnimator(){
	this->SetOnFinish( OnFinishCallback, (void*)this );
}

void BubBubbleBlastOffAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::RegisterPair( spr,  zenChanWalkAnimator_t, zenChanWalkAnimator_t, this, OnCollisionWithZenChanWalking);
	CollisionChecker::RegisterPair( spr,  zenChanStandAnimator_t, zenChanStandAnimator_t, this, OnCollisionWithZenChanStand);
	CollisionChecker::RegisterPair( spr,  zenChanFallingAnimator_t, zenChanFallingAnimator_t, this, OnCollisionWithZenChanFalling);
	CollisionChecker::RegisterPair( spr,  zenChanJumpAnimator_t, zenChanJumpAnimator_t, this, OnCollisionWithZenChanJump);
	CollisionChecker::RegisterPair( spr,  zenChanAngryStandAnimator_t, zenChanAngryStandAnimator_t, this, OnCollisionWithZenChanAngryStand);
	CollisionChecker::RegisterPair( spr,  zenChanAngryWalkAnimator_t, zenChanAngryWalkAnimator_t, this, OnCollisionWithZenZenChanAngryWalking);
	CollisionChecker::RegisterPair( spr,  zenChanAngryFallingAnimator_t, zenChanAngryFallingAnimator_t, this, OnCollisionWithZenChanAngryFalling);
	CollisionChecker::RegisterPair( spr,  zenChanAngryJumpAnimator_t, zenChanAngryJumpAnimator_t, this, OnCollisionWithZenChanAngryJump);

	CollisionChecker::RegisterPair( spr,  mightaWalkAnimator_t, mightaWalkAnimator_t, this, OnCollisionWithMightaWalking);
	CollisionChecker::RegisterPair( spr,  mightaStandAnimator_t, mightaStandAnimator_t, this, OnCollisionWithMightaStand);
	CollisionChecker::RegisterPair( spr,  mightaFallingAnimator_t, mightaFallingAnimator_t, this, OnCollisionWithMightaFalling);
	CollisionChecker::RegisterPair( spr,  mightaJumpAnimator_t, mightaJumpAnimator_t, this, OnCollisionWithMightaJump);
	CollisionChecker::RegisterPair( spr,  mightaAngryStandAnimator_t, mightaAngryStandAnimator_t, this, OnCollisionWithMightaAngryStand);
	CollisionChecker::RegisterPair( spr,  mightaAngryWalkAnimator_t, mightaAngryWalkAnimator_t, this, OnCollisionWithMightaAngryWalking);
	CollisionChecker::RegisterPair( spr,  mightaAngryFallingAnimator_t, mightaAngryFallingAnimator_t, this, OnCollisionWithMightaAngryFalling);
	CollisionChecker::RegisterPair( spr,  mightaAngryJumpAnimator_t, mightaAngryJumpAnimator_t, this, OnCollisionWithMightaAngryJump);
}

void BubBubbleBlastOffAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BubBubbleBlastOffAnimator * _this = (BubBubbleBlastOffAnimator*)args;
	DASSERT( anim==_this );
	DASSERT( _this->GetAnimation() && _this->GetSprite() );
	
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	
	MovingPathAnimation *mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("Bubbles");
	int startIndex = getClosestIndexFromPath( _this->GetSprite()->GetX(),  _this->GetSprite()->GetY(), mpa->GetPath() );
	std::vector<PathEntry> pathEntry = getPath(startIndex, mpa->GetPath());
	Sprite *sprite=new Sprite(
								mpa->GetPath()[startIndex].x,
								mpa->GetPath()[startIndex].y,
								false,
								AnimationFilmHolder::GetFilm( "BubBubble" ), 
								Terrain::GetActionLayer(), 
								true
							);
	mpa->SetPath( pathEntry );
	BubBubbleAnimator *bbar=new BubBubbleAnimator();
	bbar->RegistCollitions(sprite);

	START_ANIMATOR(bbar, sprite, mpa, GetGameTime() );
	DESTROY_ANIMATOR( _this );
}

static void StartZenChanAtBubbleAnimator(int x, int y){
	MovingPathAnimation *mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("Bubbles");
	int startIndex = getClosestIndexFromPath( x,  y, mpa->GetPath() );
	std::vector<PathEntry> pathEntry = getPath(startIndex, mpa->GetPath());
	Sprite *sprite=new Sprite(
								mpa->GetPath()[startIndex].x,
								mpa->GetPath()[startIndex].y,
								false,
								AnimationFilmHolder::GetFilm( "ZenChanInBubble" ), 
								Terrain::GetActionLayer(), 
								true
							);
	mpa->SetPath( pathEntry );
	ZenChanInBubbleAnimator* zcibanmr = new ZenChanInBubbleAnimator();
	zcibanmr->RegistCollitions(sprite);
	START_ANIMATOR(zcibanmr, sprite, mpa, GetGameTime() );
}

static void StartMightaAtBubbleAnimator(int x, int y){
	MovingPathAnimation *mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("Bubbles");
	int startIndex = getClosestIndexFromPath( x,  y, mpa->GetPath() );
	std::vector<PathEntry> pathEntry = getPath(startIndex, mpa->GetPath());
	Sprite *sprite=new Sprite(
								mpa->GetPath()[startIndex].x,
								mpa->GetPath()[startIndex].y,
								false,
								AnimationFilmHolder::GetFilm( "MightaInBubble" ), 
								Terrain::GetActionLayer(), 
								true
							);
	mpa->SetPath( pathEntry );
	MightaInBubbleAnimator* mibanmr = new MightaInBubbleAnimator();
	mibanmr->RegistCollitions(sprite);
	START_ANIMATOR(mibanmr, sprite, mpa, GetGameTime() );
}


void BubBubbleBlastOffAnimator::OnCollisionWithZenChanStand(Sprite *bubble, Sprite *enemy, void *args){
	DASSERT(bubble && enemy && args);
	StartZenChanAtBubbleAnimator(enemy->GetX(), enemy->GetY());

	std::pair< BubBubbleBlastOffAnimator*, ZenChanStandAnimator* >* pair = (std::pair< BubBubbleBlastOffAnimator*, ZenChanStandAnimator* >*) args;
	DESTROY_PAIR(pair);
}

void BubBubbleBlastOffAnimator::OnCollisionWithZenChanWalking(Sprite *bubble, Sprite *enemy, void *args){
	DASSERT(bubble && enemy && args);
	StartZenChanAtBubbleAnimator(enemy->GetX(), enemy->GetY());

	std::pair< BubBubbleBlastOffAnimator*, ZenChanWalkingAnimator* >* pair = (std::pair< BubBubbleBlastOffAnimator*, ZenChanWalkingAnimator* >*) args;
	DESTROY_PAIR(pair);
}

void BubBubbleBlastOffAnimator::OnCollisionWithZenChanFalling(Sprite *bubble, Sprite *enemy, void *args){
	DASSERT(bubble && enemy && args);
	StartZenChanAtBubbleAnimator(enemy->GetX(), enemy->GetY());

	std::pair< BubBubbleBlastOffAnimator*, ZenChanFallingAnimator* >* pair = (std::pair< BubBubbleBlastOffAnimator*, ZenChanFallingAnimator* >*) args;
	DESTROY_PAIR(pair);
}

void BubBubbleBlastOffAnimator::OnCollisionWithZenChanJump(Sprite *bubble, Sprite *enemy, void *args){
	DASSERT(bubble && enemy && args);
	StartZenChanAtBubbleAnimator(enemy->GetX(), enemy->GetY());

	std::pair< BubBubbleBlastOffAnimator*, ZenChanJumpAnimator* >* pair = (std::pair< BubBubbleBlastOffAnimator*, ZenChanJumpAnimator* >*) args;
	DESTROY_PAIR(pair);
}

void BubBubbleBlastOffAnimator::OnCollisionWithZenChanAngryStand(Sprite *bubble, Sprite *enemy, void *args){
	DASSERT(bubble && enemy && args);
	StartZenChanAtBubbleAnimator(enemy->GetX(), enemy->GetY());

	std::pair< BubBubbleBlastOffAnimator*, ZenChanAngryStandAnimator* >* pair = (std::pair< BubBubbleBlastOffAnimator*, ZenChanAngryStandAnimator* >*) args;
	DESTROY_PAIR(pair);
}

void BubBubbleBlastOffAnimator::OnCollisionWithZenZenChanAngryWalking(Sprite *bubble, Sprite *enemy, void *args){
	DASSERT(bubble && enemy && args);
	StartZenChanAtBubbleAnimator(enemy->GetX(), enemy->GetY());

	std::pair< BubBubbleBlastOffAnimator*, ZenChanAngryWalkingAnimator* >* pair = (std::pair< BubBubbleBlastOffAnimator*, ZenChanAngryWalkingAnimator* >*) args;
	DESTROY_PAIR(pair);
}

void BubBubbleBlastOffAnimator::OnCollisionWithZenChanAngryFalling(Sprite *bubble, Sprite *enemy, void *args){
	DASSERT(bubble && enemy && args);
	StartZenChanAtBubbleAnimator(enemy->GetX(), enemy->GetY());

	std::pair< BubBubbleBlastOffAnimator*, ZenChanAngryFallingAnimator* >* pair = (std::pair< BubBubbleBlastOffAnimator*, ZenChanAngryFallingAnimator* >*) args;
	DESTROY_PAIR(pair);
}

void BubBubbleBlastOffAnimator::OnCollisionWithZenChanAngryJump(Sprite *bubble, Sprite *enemy, void *args){
	DASSERT(bubble && enemy && args);
	StartZenChanAtBubbleAnimator(enemy->GetX(), enemy->GetY());

	std::pair< BubBubbleBlastOffAnimator*, ZenChanAngryJumpAnimator* >* pair = (std::pair< BubBubbleBlastOffAnimator*, ZenChanAngryJumpAnimator* >*) args;
	DESTROY_PAIR(pair);
}

////////////////////////////////

void BubBubbleBlastOffAnimator::OnCollisionWithMightaStand(Sprite *bubble, Sprite *enemy, void *args){
	DASSERT(bubble && enemy && args);
	StartMightaAtBubbleAnimator(enemy->GetX(), enemy->GetY());

	std::pair< BubBubbleBlastOffAnimator*, MightaStandAnimator* >* pair = (std::pair< BubBubbleBlastOffAnimator*, MightaStandAnimator* >*) args;
	DESTROY_PAIR(pair);
}

void BubBubbleBlastOffAnimator::OnCollisionWithMightaWalking(Sprite *bubble, Sprite *enemy, void *args){
	DASSERT(bubble && enemy && args);
	StartMightaAtBubbleAnimator(enemy->GetX(), enemy->GetY());

	std::pair< BubBubbleBlastOffAnimator*, MightaWalkingAnimator* >* pair = (std::pair< BubBubbleBlastOffAnimator*, MightaWalkingAnimator* >*) args;
	DESTROY_PAIR(pair);
}

void BubBubbleBlastOffAnimator::OnCollisionWithMightaFalling(Sprite *bubble, Sprite *enemy, void *args){
	DASSERT(bubble && enemy && args);
	StartMightaAtBubbleAnimator(enemy->GetX(), enemy->GetY());

	std::pair< BubBubbleBlastOffAnimator*, MightaFallingAnimator* >* pair = (std::pair< BubBubbleBlastOffAnimator*, MightaFallingAnimator* >*) args;
	DESTROY_PAIR(pair);
}

void BubBubbleBlastOffAnimator::OnCollisionWithMightaJump(Sprite *bubble, Sprite *enemy, void *args){
	DASSERT(bubble && enemy && args);
	StartMightaAtBubbleAnimator(enemy->GetX(), enemy->GetY());

	std::pair< BubBubbleBlastOffAnimator*, MightaJumpAnimator* >* pair = (std::pair< BubBubbleBlastOffAnimator*, MightaJumpAnimator* >*) args;
	DESTROY_PAIR(pair);
}

void BubBubbleBlastOffAnimator::OnCollisionWithMightaAngryStand(Sprite *bubble, Sprite *enemy, void *args){
	DASSERT(bubble && enemy && args);
	StartMightaAtBubbleAnimator(enemy->GetX(), enemy->GetY());

	std::pair< BubBubbleBlastOffAnimator*, MightaAngryStandAnimator* >* pair = (std::pair< BubBubbleBlastOffAnimator*, MightaAngryStandAnimator* >*) args;
	DESTROY_PAIR(pair);
}

void BubBubbleBlastOffAnimator::OnCollisionWithMightaAngryWalking(Sprite *bubble, Sprite *enemy, void *args){
	DASSERT(bubble && enemy && args);
	StartMightaAtBubbleAnimator(enemy->GetX(), enemy->GetY());

	std::pair< BubBubbleBlastOffAnimator*, MightaAngryWalkingAnimator* >* pair = (std::pair< BubBubbleBlastOffAnimator*, MightaAngryWalkingAnimator* >*) args;
	DESTROY_PAIR(pair);
}

void BubBubbleBlastOffAnimator::OnCollisionWithMightaAngryFalling(Sprite *bubble, Sprite *enemy, void *args){
	DASSERT(bubble && enemy && args);
	StartMightaAtBubbleAnimator(enemy->GetX(), enemy->GetY());

	std::pair< BubBubbleBlastOffAnimator*, MightaAngryFallingAnimator* >* pair = (std::pair< BubBubbleBlastOffAnimator*, MightaAngryFallingAnimator* >*) args;
	DESTROY_PAIR(pair);
}

void BubBubbleBlastOffAnimator::OnCollisionWithMightaAngryJump(Sprite *bubble, Sprite *enemy, void *args){
	DASSERT(bubble && enemy && args);
	StartMightaAtBubbleAnimator(enemy->GetX(), enemy->GetY());

	std::pair< BubBubbleBlastOffAnimator*, MightaAngryJumpAnimator* >* pair = (std::pair< BubBubbleBlastOffAnimator*, MightaAngryJumpAnimator* >*) args;
	DESTROY_PAIR(pair);
}

/////////////////////////////BubBubbleAnimator



static void StartPonEffectAnimator(int x, int y){

	MovingAnimation *mpa = (MovingAnimation*) AnimationsParser::GetAnimation("PonEffect");
	Sprite *sprite=new Sprite(
								x,
								y,
								false,
								AnimationFilmHolder::GetFilm( "PonEffect" ), 
								Terrain::GetActionLayer(), 
								true
							);
	PonEffectAnimator* pear = new PonEffectAnimator();
	pear->RegistCollitions(sprite);
	START_ANIMATOR(pear, sprite, mpa, GetGameTime() );
}

BubBubbleAnimator::BubBubbleAnimator(){
	this->SetOnFinish( OnFinishCallback, (void*)this );
}

void BubBubbleAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t, this, OnCollisionWithBubble);
}

void BubBubbleAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BubBubbleAnimator * _this = (BubBubbleAnimator*)args;
	DASSERT( anim==_this );
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );
}

void BubBubbleAnimator::OnCollisionWithBubFalling(Sprite *bub, Sprite *bubble, void *args){
	DASSERT( bubble && bub && args );
	BubBubbleAnimator * _this = (BubBubbleAnimator *) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	StartPonEffectAnimator( bubble->GetX(), bubble->GetY() );
	DESTROY_ANIMATOR( _this );
}

void BubBubbleAnimator::OnCollisionWithBubJump(Sprite *bub, Sprite *bubble, void *args){
	DASSERT( bubble && bub && args );
	BubBubbleAnimator * _this = (BubBubbleAnimator *) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	StartPonEffectAnimator( bubble->GetX(), bubble->GetY() );
	DESTROY_ANIMATOR( _this );
}

void BubBubbleAnimator::OnCollisionWithBubble(Sprite *spr1, Sprite *spr2, void *args){
	/*
	DASSERT( args );
	BubBubbleAnimator* mmar = (BubBubbleAnimator*)args;
	MovingPathAnimation* mma = mmar->GetAnimation();
	std::vector<PathEntry> path = mma->GetPath();
	if(spr1->GetX()>spr2->GetX()){
		//spr1->Move( 1, 0 );
		PathEntry entry( -15, 0, 0, 400);
		path.insert( path.begin() + mmar->GetCurrIndex(), entry );
		PathEntry entry2( 15, 0, 0, 400);
		path.insert( path.begin() + mmar->GetCurrIndex(), entry2 );

	}else{
		//spr1->Move( -1, 0 );
		PathEntry entry( 15, 0, 0, 400);
		path.insert( path.begin() + mmar->GetCurrIndex(), entry );
		PathEntry entry2( -15, 0, 0, 400);
		path.insert( path.begin() + mmar->GetCurrIndex(), entry2 );
	}
	mma->SetPath( path );
	/*
	if(spr1->GetY()>spr2->GetY()){
		spr1->Move( 0, 1 );
	}else{
		spr1->Move( 0, -1 );
	}*/
	
}

/////////////////////////PonEffectAnimator

PonEffectAnimator::PonEffectAnimator(){
	this->SetOnFinish( OnFinishCallback, (void*)this );
}

void PonEffectAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t,PonEffectAnimator::OnCollisionWithBubble);
}

void PonEffectAnimator::OnFinishCallback(Animator* anim, void* args){
	PonEffectAnimator* _this = (PonEffectAnimator*) anim;

	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );
}

void PonEffectAnimator::OnCollisionWithBubble(Sprite * pon, Sprite *bubble, void *args){
	DASSERT( bubble && pon && args );
	BubBubbleAnimator * _this = (BubBubbleAnimator *) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	StartPonEffectAnimator( bubble->GetX(), bubble->GetY() );
	DESTROY_ANIMATOR( _this );
}

////////////////////////////ZenChanInBubbleAnimator

ZenChanInBubbleAnimator::ZenChanInBubbleAnimator(){
	this->SetOnFinish(OnFinishCallback, (void*)this);
}

void ZenChanInBubbleAnimator::RegistCollitions(Sprite* spr){
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t, this, OnCollisionWithBubble);
}

void ZenChanInBubbleAnimator::OnFinishCallback(Animator*anim, void*args){
	DASSERT( anim && anim==args );
	ZenChanInBubbleAnimator* _this = (ZenChanInBubbleAnimator*) anim;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );
}

void ZenChanInBubbleAnimator::OnCollisionWithBubFalling(Sprite *bub, Sprite *bubble, void *args){
	DASSERT( bubble && bub && args );
	ZenChanInBubbleAnimator * _this = (ZenChanInBubbleAnimator *) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	StartPonEffectAnimator( bubble->GetX(), bubble->GetY() );
	DESTROY_ANIMATOR( _this );
}

void ZenChanInBubbleAnimator::OnCollisionWithBubJump(Sprite *bub, Sprite *bubble, void *args){
	DASSERT( bubble && bub && args );
	ZenChanInBubbleAnimator * _this = (ZenChanInBubbleAnimator *) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	StartPonEffectAnimator( bubble->GetX(), bubble->GetY() );
	DESTROY_ANIMATOR( _this );
}

void ZenChanInBubbleAnimator::OnCollisionWithBubble(Sprite *spr1, Sprite *spr2, void *args){

}

//////////////////////MightaInBubbleAnimator

MightaInBubbleAnimator::MightaInBubbleAnimator(){
	this->SetOnFinish(OnFinishCallback, (void*)this);
}

void MightaInBubbleAnimator::RegistCollitions(Sprite* spr){


}

void MightaInBubbleAnimator::OnFinishCallback(Animator*anim, void*args){
	DASSERT( anim && anim==args );
	MightaInBubbleAnimator* _this = (MightaInBubbleAnimator*) anim;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );
}

void MightaInBubbleAnimator::OnCollisionWithBubFalling(Sprite *bub, Sprite *bubble, void *args){
	DASSERT( bubble && bub && args );
	MightaInBubbleAnimator * _this = (MightaInBubbleAnimator *) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	StartPonEffectAnimator( bubble->GetX(), bubble->GetY() );
	DESTROY_ANIMATOR( _this );
}

void MightaInBubbleAnimator::OnCollisionWithBubJump(Sprite *bub, Sprite *bubble, void *args){
	DASSERT( bubble && bub && args );
	MightaInBubbleAnimator * _this = (MightaInBubbleAnimator *) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	StartPonEffectAnimator( bubble->GetX(), bubble->GetY() );
	DESTROY_ANIMATOR( _this );
}

void MightaInBubbleAnimator::OnCollisionWithBubble(Sprite *spr1, Sprite *spr2, void *args){

}