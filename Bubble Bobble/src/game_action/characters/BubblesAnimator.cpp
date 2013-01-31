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

#define BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_ZEN_CHAN(animator_type, bubble, enemy, args)\
	DASSERT(bubble && enemy && args);													\
	StartZenChanAtBubbleAnimator(enemy->GetX(), enemy->GetY());							\
	std::pair< BubBubbleBlastOffAnimator*, animator_type* >* pair =						\
				(std::pair< BubBubbleBlastOffAnimator*, animator_type* >*) args;		\
	DESTROY_PAIR(pair)

#define BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_MIGHTA(animator_type, bubble, enemy, args)\
	DASSERT(bubble && enemy && args);													\
	StartMightaAtBubbleAnimator(enemy->GetX(), enemy->GetY());							\
	std::pair< BubBubbleBlastOffAnimator*, animator_type* >* pair =						\
				(std::pair< BubBubbleBlastOffAnimator*, animator_type* >*) args;		\
	DESTROY_PAIR(pair)

#define KILL_BUB_BUBBLE( animator_type, bubble, bub, args )					\
	DASSERT( bubble && bub && args );										\
	animator_type * _this = (animator_type *) args;					\
	REMOVE_FROM_ACTION_ANIMATOR( _this );									\
	StartPonEffectAnimator( bubble->GetX(), bubble->GetY() );				\
	DESTROY_ANIMATOR( _this )

#define KILL_ZEN_CHAN(animator_type, bubble, zenChan, args )			\
		DASSERT( bubble && zenChan && args );							\
		animator_type * _this = (animator_type *) args;					\
		REMOVE_FROM_ACTION_ANIMATOR( _this );							\
		StartPonEffectAnimator( bubble->GetX(), bubble->GetY() );		\
		StartZenChanDieAnimator(bubble->GetX(), bubble->GetY());		\
		DESTROY_ANIMATOR( _this )	

#define KILL_MIGHTA(animator_type, bubble, mighta, args )				\
		DASSERT( bubble && mighta && args );							\
		animator_type * _this = (animator_type *) args;					\
		REMOVE_FROM_ACTION_ANIMATOR( _this );							\
		StartPonEffectAnimator( bubble->GetX(), bubble->GetY() );		\
		StartMightaDieAnimator(bubble->GetX(), bubble->GetY());			\
		DESTROY_ANIMATOR( _this )	

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

static std::vector<PathEntry> getPath(const int index, const std::vector<PathEntry>& constPath, unsigned int distatnce){
	std::vector<PathEntry> path;

	for(unsigned int i = index; i<constPath.size()-1 && i<index+constPath.size()/distatnce; ++i){
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
	std::vector<PathEntry> pathEntry = getPath(startIndex, mpa->GetPath(), 4);
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
	std::vector<PathEntry> pathEntry = getPath(startIndex, mpa->GetPath(), 4);
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
	std::vector<PathEntry> pathEntry = getPath(startIndex, mpa->GetPath(), 4);
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
	BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_ZEN_CHAN(ZenChanStandAnimator, bubble, enemy, args  );
}

void BubBubbleBlastOffAnimator::OnCollisionWithZenChanWalking(Sprite *bubble, Sprite *enemy, void *args){
	BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_ZEN_CHAN(ZenChanWalkingAnimator, bubble, enemy, args  );
}

void BubBubbleBlastOffAnimator::OnCollisionWithZenChanFalling(Sprite *bubble, Sprite *enemy, void *args){
	BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_ZEN_CHAN(ZenChanFallingAnimator, bubble, enemy, args  );
}

void BubBubbleBlastOffAnimator::OnCollisionWithZenChanJump(Sprite *bubble, Sprite *enemy, void *args){
	BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_ZEN_CHAN(ZenChanJumpAnimator, bubble, enemy, args  );
}

void BubBubbleBlastOffAnimator::OnCollisionWithZenChanAngryStand(Sprite *bubble, Sprite *enemy, void *args){
	BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_ZEN_CHAN(ZenChanAngryStandAnimator, bubble, enemy, args  );
}

void BubBubbleBlastOffAnimator::OnCollisionWithZenZenChanAngryWalking(Sprite *bubble, Sprite *enemy, void *args){
	BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_ZEN_CHAN(ZenChanAngryWalkingAnimator, bubble, enemy, args  );
}

void BubBubbleBlastOffAnimator::OnCollisionWithZenChanAngryFalling(Sprite *bubble, Sprite *enemy, void *args){
	BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_ZEN_CHAN(ZenChanAngryFallingAnimator, bubble, enemy, args  );
}

void BubBubbleBlastOffAnimator::OnCollisionWithZenChanAngryJump(Sprite *bubble, Sprite *enemy, void *args){
	BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_ZEN_CHAN(ZenChanAngryJumpAnimator, bubble, enemy, args  );
}

////////////////////////////////

void BubBubbleBlastOffAnimator::OnCollisionWithMightaStand(Sprite *bubble, Sprite *enemy, void *args){
	BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_MIGHTA(MightaStandAnimator, bubble, enemy, args  );
}

void BubBubbleBlastOffAnimator::OnCollisionWithMightaWalking(Sprite *bubble, Sprite *enemy, void *args){
	BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_MIGHTA(MightaWalkingAnimator, bubble, enemy, args  );
}

void BubBubbleBlastOffAnimator::OnCollisionWithMightaFalling(Sprite *bubble, Sprite *enemy, void *args){
	BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_MIGHTA(MightaFallingAnimator, bubble, enemy, args  );
}

void BubBubbleBlastOffAnimator::OnCollisionWithMightaJump(Sprite *bubble, Sprite *enemy, void *args){
	BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_MIGHTA(MightaJumpAnimator, bubble, enemy, args  );
}

void BubBubbleBlastOffAnimator::OnCollisionWithMightaAngryStand(Sprite *bubble, Sprite *enemy, void *args){
	BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_MIGHTA(MightaAngryStandAnimator, bubble, enemy, args  );
}

void BubBubbleBlastOffAnimator::OnCollisionWithMightaAngryWalking(Sprite *bubble, Sprite *enemy, void *args){
	BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_MIGHTA(MightaAngryWalkingAnimator, bubble, enemy, args  );
}

void BubBubbleBlastOffAnimator::OnCollisionWithMightaAngryFalling(Sprite *bubble, Sprite *enemy, void *args){
	BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_MIGHTA(MightaAngryFallingAnimator, bubble, enemy, args  );
}

void BubBubbleBlastOffAnimator::OnCollisionWithMightaAngryJump(Sprite *bubble, Sprite *enemy, void *args){
	BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_MIGHTA(MightaAngryJumpAnimator, bubble, enemy, args  );
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
	DASSERT( anim && anim==args);
	BubBubbleAnimator * _this = (BubBubbleAnimator*)args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );

	MovingPathAnimation *mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("Bubbles");
	int startIndex = getClosestIndexFromPath( _this->GetSprite()->GetX(),  _this->GetSprite()->GetY(), mpa->GetPath() );
	std::vector<PathEntry> pathEntry = getPath(startIndex, mpa->GetPath(), 6);
	Sprite *sprite=new Sprite(
								_this->GetSprite()->GetX(),
								_this->GetSprite()->GetY(),
								false,
								AnimationFilmHolder::GetFilm( "BubPingBubble" ), 
								Terrain::GetActionLayer(), 
								true
							);

	mpa->SetPath( pathEntry );
	BubPingBubbleAnimator* bpbamr = new BubPingBubbleAnimator();
	bpbamr->RegistCollitions(sprite);
	START_ANIMATOR(bpbamr, sprite, mpa, GetGameTime() );

	DESTROY_ANIMATOR( _this );
}

void BubBubbleAnimator::OnCollisionWithBubFalling(Sprite *bub, Sprite *bubble, void *args){
	KILL_BUB_BUBBLE( BubBubbleAnimator, bubble, bub, args );
}

void BubBubbleAnimator::OnCollisionWithBubJump(Sprite *bub, Sprite *bubble, void *args){
	KILL_BUB_BUBBLE( BubBubbleAnimator, bubble, bub, args );
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

////////////////////////////////////BubPingBubbleAnimator

BubPingBubbleAnimator::BubPingBubbleAnimator(){
	this->SetOnFinish( OnFinishCallback, this );
}

void BubPingBubbleAnimator::RegistCollitions(Sprite* spr){
	CollisionChecker::Register(spr, bubPingBubbleAnimator_t, bubPingBubbleAnimator_t, this, OnCollisionWithBubble);
}

void BubPingBubbleAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && anim==args );
	BubPingBubbleAnimator* _this = (BubPingBubbleAnimator*) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );
}

void BubPingBubbleAnimator::OnCollisionWithBubFalling(Sprite *bub, Sprite *bubble, void *args){
	KILL_BUB_BUBBLE( BubPingBubbleAnimator, bubble, bub, args );
}

void BubPingBubbleAnimator::OnCollisionWithBubJump(Sprite *bub, Sprite *bubble, void *args){
	KILL_BUB_BUBBLE( BubPingBubbleAnimator, bubble, bub, args );
}

void BubPingBubbleAnimator::OnCollisionWithBubble(Sprite *spr1, Sprite *spr2, void *args){

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
	KILL_BUB_BUBBLE( PonEffectAnimator, bubble, pon, args );
}

////////////////////////////ZenChanInBubbleAnimator

static void StartZenChanDieAnimator( int x, int y ){
	Sprite* newSprite = 
		new Sprite(x, y, false, AnimationFilmHolder::GetFilm("ZenChanDie"), Terrain::GetActionLayer(),false);

	MovingPathAnimation* mpa=(MovingPathAnimation*)AnimationsParser::GetAnimation("ZenChanDie");
	ZenChanDieAnimator *bda=new ZenChanDieAnimator();
	bda->RegistCollitions(newSprite);
	START_ANIMATOR( bda, newSprite, mpa, GetGameTime() );
}

ZenChanInBubbleAnimator::ZenChanInBubbleAnimator(){
	this->SetOnFinish(OnFinishCallback, (void*)this);
}

void ZenChanInBubbleAnimator::RegistCollitions(Sprite* spr){
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t, this, OnCollisionWithBubble);
}

void ZenChanInBubbleAnimator::OnFinishCallback(Animator*anim, void*args){
	DASSERT( anim && anim==args );
	ZenChanInBubbleAnimator* _this = (ZenChanInBubbleAnimator*) anim;

	MovingPathAnimation *mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("EnemyAgryBubble");
	Sprite *sprite=new Sprite(
								_this->GetSprite()->GetX(),
								_this->GetSprite()->GetY(),
								false,
								AnimationFilmHolder::GetFilm( "ZenChanInBubbleMediumAngry" ), 
								Terrain::GetActionLayer(), 
								true
							);
	ZenChanInBubbleMediumAngryAnimator* bpbamr = new ZenChanInBubbleMediumAngryAnimator();
	bpbamr->RegistCollitions(sprite);
	START_ANIMATOR(bpbamr, sprite, mpa, GetGameTime() );

	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );
}

void ZenChanInBubbleAnimator::OnCollisionWithBubFalling(Sprite *zenChan, Sprite *bubble, void *args){
	KILL_ZEN_CHAN(ZenChanInBubbleAnimator, bubble, zenChan, args );
}

void ZenChanInBubbleAnimator::OnCollisionWithBubJump(Sprite *zenChan, Sprite *bubble, void *args){
	KILL_ZEN_CHAN(ZenChanInBubbleAnimator, bubble, zenChan, args );
}

void ZenChanInBubbleAnimator::OnCollisionWithBubble(Sprite *spr1, Sprite *spr2, void *args){

}

////////////////////////////ZenChanInBubbleMediumAngryAnimator

ZenChanInBubbleMediumAngryAnimator::ZenChanInBubbleMediumAngryAnimator(){
	this->SetOnFinish(OnFinishCallback, (void*)this);
}

void ZenChanInBubbleMediumAngryAnimator::RegistCollitions(Sprite* spr){
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t, this, OnCollisionWithBubble);
}

void ZenChanInBubbleMediumAngryAnimator::OnFinishCallback(Animator*anim, void*args){
	DASSERT( anim && anim==args );
	ZenChanInBubbleMediumAngryAnimator* _this = (ZenChanInBubbleMediumAngryAnimator*) anim;

	MovingPathAnimation *mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("EnemyAgryBubble");
	Sprite *sprite=new Sprite(
								_this->GetSprite()->GetX(),
								_this->GetSprite()->GetY(),
								false,
								AnimationFilmHolder::GetFilm( "ZenChanInBubbleHighAngry" ), 
								Terrain::GetActionLayer(), 
								true
							);
	ZenChanInBubbleHighAngryAnimator* bpbamr = new ZenChanInBubbleHighAngryAnimator();
	bpbamr->RegistCollitions(sprite);
	START_ANIMATOR(bpbamr, sprite, mpa, GetGameTime() );


	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );
}						

void ZenChanInBubbleMediumAngryAnimator::OnCollisionWithBubFalling(Sprite *zenChan, Sprite *bubble, void *args){
	KILL_ZEN_CHAN(ZenChanInBubbleMediumAngryAnimator, bubble, zenChan, args );
}

void ZenChanInBubbleMediumAngryAnimator::OnCollisionWithBubJump(Sprite *zenChan, Sprite *bubble, void *args){
	KILL_ZEN_CHAN(ZenChanInBubbleMediumAngryAnimator, bubble, zenChan, args );
}

void ZenChanInBubbleMediumAngryAnimator::OnCollisionWithBubble(Sprite *spr1, Sprite *spr2, void *args){

}

////////////////////////////ZenChanInBubbleHighAngryAnimator

ZenChanInBubbleHighAngryAnimator::ZenChanInBubbleHighAngryAnimator(){
	this->SetOnFinish(OnFinishCallback, (void*)this);
}

void ZenChanInBubbleHighAngryAnimator::RegistCollitions(Sprite* spr){
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t, this, OnCollisionWithBubble);
}

void ZenChanInBubbleHighAngryAnimator::OnFinishCallback(Animator*anim, void*args){
	DASSERT( anim && anim==args );
	ZenChanInBubbleHighAngryAnimator* _this = (ZenChanInBubbleHighAngryAnimator*) anim;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );
}

void ZenChanInBubbleHighAngryAnimator::OnCollisionWithBubFalling(Sprite *zenChan, Sprite *bubble, void *args){
	KILL_ZEN_CHAN(ZenChanInBubbleHighAngryAnimator, bubble, zenChan, args );

}

void ZenChanInBubbleHighAngryAnimator::OnCollisionWithBubJump(Sprite *zenChan, Sprite *bubble, void *args){
	KILL_ZEN_CHAN(ZenChanInBubbleHighAngryAnimator, bubble, zenChan, args );
}

void ZenChanInBubbleHighAngryAnimator::OnCollisionWithBubble(Sprite *spr1, Sprite *spr2, void *args){

}

//////////////////////MightaInBubbleAnimator

static void StartMightaDieAnimator( int x, int y ){
	Sprite* newSprite = 
		new Sprite(x, y, false, AnimationFilmHolder::GetFilm("MightaDie"), Terrain::GetActionLayer(),false);

	MovingPathAnimation* mpa=(MovingPathAnimation*)AnimationsParser::GetAnimation("MightaDie");
	ZenChanDieAnimator *bda=new ZenChanDieAnimator();
	bda->RegistCollitions(newSprite);
	START_ANIMATOR( bda, newSprite, mpa, GetGameTime() );
}

MightaInBubbleAnimator::MightaInBubbleAnimator(){
	this->SetOnFinish(OnFinishCallback, (void*)this);
}

void MightaInBubbleAnimator::RegistCollitions(Sprite* spr){


}

void MightaInBubbleAnimator::OnFinishCallback(Animator*anim, void*args){
	DASSERT( anim && anim==args );
	MightaInBubbleAnimator* _this = (MightaInBubbleAnimator*) anim;
	MovingPathAnimation *mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("EnemyAgryBubble");
	Sprite *sprite=new Sprite(
								_this->GetSprite()->GetX(),
								_this->GetSprite()->GetY(),
								false,						  
								AnimationFilmHolder::GetFilm( "MightaInBubbleMediumAngry" ), 
								Terrain::GetActionLayer(), 
								true
							);
	MightaInBubbleMediumAngryAnimator* bpbamr = new MightaInBubbleMediumAngryAnimator();
	bpbamr->RegistCollitions(sprite);
	START_ANIMATOR(bpbamr, sprite, mpa, GetGameTime() );

	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );
}

void MightaInBubbleAnimator::OnCollisionWithBubFalling(Sprite *mighta, Sprite *bubble, void *args){
	KILL_MIGHTA(MightaInBubbleAnimator, bubble, mighta, args );
}

void MightaInBubbleAnimator::OnCollisionWithBubJump(Sprite *mighta, Sprite *bubble, void *args){
	KILL_MIGHTA(MightaInBubbleAnimator, bubble, mighta, args );
}

void MightaInBubbleAnimator::OnCollisionWithBubble(Sprite *spr1, Sprite *spr2, void *args){

}


/////////////////////////////////MightaInBubbleMediumAngryAnimator

MightaInBubbleMediumAngryAnimator::MightaInBubbleMediumAngryAnimator(){
	this->SetOnFinish(OnFinishCallback, (void*)this);
}

void MightaInBubbleMediumAngryAnimator::RegistCollitions(Sprite* spr){


}

void MightaInBubbleMediumAngryAnimator::OnFinishCallback(Animator*anim, void*args){

	DASSERT( anim && anim==args );
	MightaInBubbleMediumAngryAnimator* _this = (MightaInBubbleMediumAngryAnimator*) anim;

	MovingPathAnimation *mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("EnemyAgryBubble");
	Sprite *sprite=new Sprite(
								_this->GetSprite()->GetX(),
								_this->GetSprite()->GetY(),
								false,						
								AnimationFilmHolder::GetFilm( "MightaInBubbleHighAngry" ), 
								Terrain::GetActionLayer(), 
								true
							);
	MightaInBubbleHighAngryAnimator* bpbamr = new MightaInBubbleHighAngryAnimator();
	bpbamr->RegistCollitions(sprite);
	START_ANIMATOR(bpbamr, sprite, mpa, GetGameTime() );

	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );
}

void MightaInBubbleMediumAngryAnimator::OnCollisionWithBubFalling(Sprite *mighta, Sprite *bubble, void *args){
	KILL_MIGHTA(MightaInBubbleMediumAngryAnimator, bubble, mighta, args );
}

void MightaInBubbleMediumAngryAnimator::OnCollisionWithBubJump(Sprite *mighta, Sprite *bubble, void *args){
	KILL_MIGHTA(MightaInBubbleMediumAngryAnimator, bubble, mighta, args );
}

void MightaInBubbleMediumAngryAnimator::OnCollisionWithBubble(Sprite *spr1, Sprite *spr2, void *args){

}

/////////////////////////////////MightaInBubbleHighAngryAnimator

MightaInBubbleHighAngryAnimator::MightaInBubbleHighAngryAnimator(){
	this->SetOnFinish(OnFinishCallback, (void*)this);
}

void MightaInBubbleHighAngryAnimator::RegistCollitions(Sprite* spr){

}

void MightaInBubbleHighAngryAnimator::OnFinishCallback(Animator*anim, void*args){

	DASSERT( anim && anim==args );
	MightaInBubbleHighAngryAnimator* _this = (MightaInBubbleHighAngryAnimator*) anim;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );
}

void MightaInBubbleHighAngryAnimator::OnCollisionWithBubFalling(Sprite *mighta, Sprite *bubble, void *args){
	KILL_MIGHTA(MightaInBubbleHighAngryAnimator, bubble, mighta, args );
}

void MightaInBubbleHighAngryAnimator::OnCollisionWithBubJump(Sprite *mighta, Sprite *bubble, void *args){
	KILL_MIGHTA(MightaInBubbleHighAngryAnimator, bubble, mighta, args );
}

void MightaInBubbleHighAngryAnimator::OnCollisionWithBubble(Sprite *spr1, Sprite *spr2, void *args){

}