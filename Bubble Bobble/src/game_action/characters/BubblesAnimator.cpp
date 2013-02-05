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
#include "BubbleLogic.h"


#define DESTROY_PAIR( pair )						\
	REMOVE_FROM_ACTION_ANIMATOR( pair->first );		\
	DESTROY_ANIMATOR( pair->first );				\
	REMOVE_FROM_ACTION_ANIMATOR( pair->second );	\
	DESTROY_ANIMATOR( pair->second );				\
	free(pair)

#define BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_ZEN_CHAN(animator_type, bubble, enemy, args)\
	DASSERT(bubble && enemy && args);													\
	StartZenChanAtBubbleAnimator(enemy->GetX(), enemy->GetY(), enemy->GoesLeft());		\
	std::pair< BubBubbleBlastOffAnimator*, animator_type* >* pair =						\
				(std::pair< BubBubbleBlastOffAnimator*, animator_type* >*) args;		\
	DESTROY_PAIR(pair)

#define BUB_BUBBLE_BLAST_OFF_COLLITION_WITH_MIGHTA(animator_type, bubble, enemy, args)	\
	DASSERT(bubble && enemy && args);													\
	StartMightaAtBubbleAnimator(enemy->GetX(), enemy->GetY(), enemy->GoesLeft());		\
	std::pair< BubBubbleBlastOffAnimator*, animator_type* >* pair =						\
				(std::pair< BubBubbleBlastOffAnimator*, animator_type* >*) args;		\
	DESTROY_PAIR(pair)

#define KILL_BUB_BUBBLE( animator_type, bubble, bub, args )					\
	DASSERT( bubble && bub && args );										\
	animator_type * _this = (animator_type *) args;							\
	OnTickTimerFinishCallback(_this->getBubBubbleTimer(), 0);				\
	REMOVE_FROM_ACTION_ANIMATOR( _this );									\
	StartPonEffectAnimator( bubble->GetX(), bubble->GetY() );				\
	DESTROY_ANIMATOR( _this );												\
	BubbleLogic::BubPonEmptyBubble()

#define KILL_ZEN_CHAN(animator_type, bubble, zenChan, args )			\
		DASSERT( bubble && zenChan && args );							\
		animator_type * _this = (animator_type *) args;					\
		OnTickTimerFinishCallback(_this->getBubBubbleTimer(), 0);		\
		REMOVE_FROM_ACTION_ANIMATOR( _this );							\
		StartPonEffectAnimator( bubble->GetX(), bubble->GetY() );		\
		StartZenChanDieAnimator(bubble->GetX(), bubble->GetY());		\
		DESTROY_ANIMATOR( _this );										\
		BubbleLogic::BubPonZenChanBubble()

#define KILL_ZEN_CHAN_ANGRY(animator_type, bubble, zenChan, args )		\
		DASSERT( bubble && zenChan && args );							\
		animator_type * _this = (animator_type *) args;					\
		REMOVE_FROM_ACTION_ANIMATOR( _this );							\
		StartPonEffectAnimator( bubble->GetX(), bubble->GetY() );		\
		StartZenChanDieAnimator(bubble->GetX(), bubble->GetY());		\
		DESTROY_ANIMATOR( _this );										\
		BubbleLogic::BubPonZenChanBubble()

#define KILL_MIGHTA(animator_type, bubble, mighta, args )				\
		DASSERT( bubble && mighta && args );							\
		animator_type * _this = (animator_type *) args;					\
		OnTickTimerFinishCallback(_this->getBubBubbleTimer(), 0);		\
		REMOVE_FROM_ACTION_ANIMATOR( _this );							\
		StartPonEffectAnimator( bubble->GetX(), bubble->GetY() );		\
		StartMightaDieAnimator(bubble->GetX(), bubble->GetY());			\
		DESTROY_ANIMATOR( _this );										\
		BubbleLogic::BubPonMightaBubble()

#define KILL_MIGHTA_ANGRY(animator_type, bubble, mighta, args )			\
		DASSERT( bubble && mighta && args );							\
		animator_type * _this = (animator_type *) args;					\
		REMOVE_FROM_ACTION_ANIMATOR( _this );							\
		StartPonEffectAnimator( bubble->GetX(), bubble->GetY() );		\
		StartMightaDieAnimator(bubble->GetX(), bubble->GetY());			\
		DESTROY_ANIMATOR( _this );										\
		BubbleLogic::BubPonMightaBubble()

static void OnTickTimerFinishCallback(Animator* animr, void* args){
	DASSERT( animr && !args );
	TimerTickAnimator* ttar = (TimerTickAnimator*) animr;
	AnimatorHolder::MarkAsSuspended( ttar );	
	AnimatorHolder::Cancel( ttar );			
	DESTROY_ANIMATOR_WITHOUT_SPRITE( ttar );
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
	
	FrameRangeAnimation *fra = (FrameRangeAnimation*) AnimationsParser::GetAnimation(_this->GetSprite()->GoesLeft()?"BubbleLeft":"BubbleRight");
	Sprite *sprite=new Sprite(
								_this->GetSprite()->GetX(),
								_this->GetSprite()->GetY(),
								false,
								AnimationFilmHolder::GetFilm( "BubBubble" ), 
								Terrain::GetActionLayer(), 
								_this->GetSprite()->GoesLeft()
							);

	TickAnimation *ta = (TickAnimation*) AnimationsParser::GetAnimation("BubBubbleExpired");
	TimerTickAnimator* ttar = new TimerTickAnimator(ta);
	ttar->SetOnFinish(OnTickTimerFinishCallback, 0);

	BubBubbleAnimator *bbar=new BubBubbleAnimator(ttar);
	bbar->RegistCollitions(sprite);
	ta->SetTickAction( BubBubbleAnimator::OnBubbleExpiredTime, bbar );

	START_ANIMATOR(bbar, sprite, fra, GetGameTime() );
	ttar->Start(GetGameTime());
	AnimatorHolder::Register( ttar );				
	AnimatorHolder::MarkAsRunning( ttar );
	DESTROY_ANIMATOR( _this );
	
}

static void StartZenChanAtBubbleAnimator(int x, int y, bool goesLeft){
	FrameRangeAnimation *fra = (FrameRangeAnimation*) AnimationsParser::GetAnimation(goesLeft?"BubbleLeft":"BubbleRight");
	Sprite *sprite=new Sprite(
								x,
								y,
								false,
								AnimationFilmHolder::GetFilm( "ZenChanInBubble" ), 
								Terrain::GetActionLayer(), 
								true
							);
	TickAnimation *ta = (TickAnimation*) AnimationsParser::GetAnimation("BubBubbleExpired");
	TimerTickAnimator* ttar = new TimerTickAnimator(ta);
	ttar->SetOnFinish(OnTickTimerFinishCallback, 0);

	ZenChanInBubbleAnimator* zcibanmr = new ZenChanInBubbleAnimator(ttar);
	zcibanmr->RegistCollitions(sprite);
	ta->SetTickAction( ZenChanInBubbleAnimator::OnBubbleExpiredTime, zcibanmr );
	START_ANIMATOR(zcibanmr, sprite, fra, GetGameTime() );
	ttar->Start(GetGameTime());
	AnimatorHolder::Register( ttar );				
	AnimatorHolder::MarkAsRunning( ttar );
}

static void StartMightaAtBubbleAnimator(int x, int y, bool goesLeft){
	FrameRangeAnimation *fra = (FrameRangeAnimation*) AnimationsParser::GetAnimation(goesLeft?"BubbleLeft":"BubbleRight");
	Sprite *sprite=new Sprite(
								x,
								y,
								false,
								AnimationFilmHolder::GetFilm( "MightaInBubble" ), 
								Terrain::GetActionLayer(), 
								true
							);

	TickAnimation *ta = (TickAnimation*) AnimationsParser::GetAnimation("BubBubbleExpired");
	TimerTickAnimator* ttar = new TimerTickAnimator(ta);
	ttar->SetOnFinish(OnTickTimerFinishCallback, 0);

	MightaInBubbleAnimator* mibanmr = new MightaInBubbleAnimator(ttar);
	mibanmr->RegistCollitions(sprite);
	ta->SetTickAction( MightaInBubbleAnimator::OnBubbleExpiredTime, mibanmr );
	START_ANIMATOR(mibanmr, sprite, fra, GetGameTime() );
	ttar->Start(GetGameTime());
	AnimatorHolder::Register( ttar );				
	AnimatorHolder::MarkAsRunning( ttar );
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

BubBubbleAnimator::BubBubbleAnimator(TimerTickAnimator* _BubBubbleTimer){
	BubBubbleTimer = _BubBubbleTimer;
}

void BubBubbleAnimator::RegistCollitions(Sprite *spr){
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t, this, OnCollisionWithBubble);
	CollisionChecker::RegisterBubbleDrivers(spr, this);
	CollisionChecker::RegisterBubbleWrapAroundDrivers(spr, this);
}

void BubBubbleAnimator::OnBubbleExpiredTime(void* args){
	DASSERT( args);
	BubBubbleAnimator * _this = (BubBubbleAnimator*)args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );

	FrameRangeAnimation *fra = (FrameRangeAnimation*) AnimationsParser::GetAnimation(_this->GetSprite()->GoesLeft()?"BubbleLeft":"BubbleRight");
	Sprite *sprite=new Sprite(
								_this->GetSprite()->GetX(),
								_this->GetSprite()->GetY(),
								false,
								AnimationFilmHolder::GetFilm( "BubPingBubble" ), 
								Terrain::GetActionLayer(), 
								true
							);
	TickAnimation *ta = (TickAnimation*) AnimationsParser::GetAnimation("BubPigBubbleExpired");
	TimerTickAnimator* ttar = new TimerTickAnimator(ta);
	ttar->SetOnFinish(OnTickTimerFinishCallback, 0);

	BubPingBubbleAnimator* bpbamr = new BubPingBubbleAnimator(ttar);
	bpbamr->RegistCollitions(sprite);

	ta->SetTickAction( BubPingBubbleAnimator::OnBubbleExpiredTime, bpbamr );

	ttar->Start(GetGameTime());
	AnimatorHolder::Register( ttar );				
	AnimatorHolder::MarkAsRunning( ttar );
	START_ANIMATOR(bpbamr, sprite, fra, GetGameTime() );
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

	}else{
		//spr1->Move( -1, 0 );
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

BubPingBubbleAnimator::BubPingBubbleAnimator(TimerTickAnimator* _bubBubbleTimer){
	BubBubbleTimer = _bubBubbleTimer;
}

void BubPingBubbleAnimator::RegistCollitions(Sprite* spr){
	CollisionChecker::Register(spr, bubPingBubbleAnimator_t, bubPingBubbleAnimator_t, this, OnCollisionWithBubble);
	CollisionChecker::RegisterBubbleDrivers(spr, this);
	CollisionChecker::RegisterBubbleWrapAroundDrivers(spr, this);
}

void BubPingBubbleAnimator::OnCollisionWithBubFalling(Sprite *bub, Sprite *bubble, void *args){
	KILL_BUB_BUBBLE( BubPingBubbleAnimator, bubble, bub, args );
}

void BubPingBubbleAnimator::OnCollisionWithBubJump(Sprite *bub, Sprite *bubble, void *args){
	KILL_BUB_BUBBLE( BubPingBubbleAnimator, bubble, bub, args );
}

void BubPingBubbleAnimator::OnCollisionWithBubble(Sprite *spr1, Sprite *spr2, void *args){

}

void BubPingBubbleAnimator::OnBubbleExpiredTime(void* args){
	DASSERT( args );
	BubPingBubbleAnimator* _this = (BubPingBubbleAnimator*) args;
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );
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
	KILL_BUB_BUBBLE( BubBubbleAnimator, bubble, pon, args );
}

////////////////////////////ZenChanInBubbleAnimator

static void StartZenChanDieAnimator( int x, int y ){
	Sprite* newSprite = 
		new Sprite(x, y, false, AnimationFilmHolder::GetFilm("ZenChanDie"), Terrain::GetActionLayer(),false);

	MovingPathAnimation* mpa = (MovingPathAnimation*)AnimationsParser::GetAnimation("ZenChanDie");
	ZenChanDieAnimator *bda = new ZenChanDieAnimator();
	bda->RegistCollitions(newSprite);
	START_ANIMATOR( bda, newSprite, mpa, GetGameTime() );
}

ZenChanInBubbleAnimator::ZenChanInBubbleAnimator(TimerTickAnimator* _BubBubbleTimer){
	BubBubbleTimer = _BubBubbleTimer;
}

void ZenChanInBubbleAnimator::RegistCollitions(Sprite* spr){
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t, this, OnCollisionWithBubble);
	CollisionChecker::RegisterBubbleDrivers(spr, this);
	CollisionChecker::RegisterBubbleWrapAroundDrivers(spr, this);
}

void  ZenChanInBubbleAnimator::OnBubbleExpiredTime(void* args){
	DASSERT( args );
	ZenChanInBubbleAnimator* _this = (ZenChanInBubbleAnimator*) args;

	MovingPathAnimation *mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("EnemyAgryBubble");
	Sprite *sprite  =new Sprite(
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
	Sprite *sprite = new Sprite(
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
	KILL_ZEN_CHAN_ANGRY(ZenChanInBubbleMediumAngryAnimator, bubble, zenChan, args );
}

void ZenChanInBubbleMediumAngryAnimator::OnCollisionWithBubJump(Sprite *zenChan, Sprite *bubble, void *args){
	KILL_ZEN_CHAN_ANGRY(ZenChanInBubbleMediumAngryAnimator, bubble, zenChan, args );
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

	FrameRangeAnimation *fra = (FrameRangeAnimation*)AnimationsParser::GetAnimation("ZenChanAngryWalkLeft");
	Sprite *n_sprite = new Sprite(
									_this->GetSprite()->GetX(),
									_this->GetSprite()->GetY(),
									_this->GetSprite()->IsGravityAddicted(),
									AnimationFilmHolder::GetFilm("ZenChanAngry"), 
									Terrain::GetActionLayer(), 
									_this->GetSprite()->GoesLeft()
								);
	ZenChanAngryWalkingAnimator *frtor=new ZenChanAngryWalkingAnimator();
	START_ANIMATOR(frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( _this );
}

void ZenChanInBubbleHighAngryAnimator::OnCollisionWithBubFalling(Sprite *zenChan, Sprite *bubble, void *args){
	KILL_ZEN_CHAN_ANGRY(ZenChanInBubbleHighAngryAnimator, bubble, zenChan, args );

}

void ZenChanInBubbleHighAngryAnimator::OnCollisionWithBubJump(Sprite *zenChan, Sprite *bubble, void *args){
	KILL_ZEN_CHAN_ANGRY(ZenChanInBubbleHighAngryAnimator, bubble, zenChan, args );
}

void ZenChanInBubbleHighAngryAnimator::OnCollisionWithBubble(Sprite *spr1, Sprite *spr2, void *args){

}

//////////////////////MightaInBubbleAnimator

static void StartMightaDieAnimator( int x, int y ){
	Sprite* newSprite = 
		new Sprite(x, y, false, AnimationFilmHolder::GetFilm("MightaDie"), Terrain::GetActionLayer(),false);

	MovingPathAnimation* mpa = (MovingPathAnimation*)AnimationsParser::GetAnimation("MightaDie");
	MightaDieAnimator *bda = new MightaDieAnimator();
	bda->RegistCollitions(newSprite);
	START_ANIMATOR( bda, newSprite, mpa, GetGameTime() );
}

MightaInBubbleAnimator::MightaInBubbleAnimator(TimerTickAnimator* _bubBubbleTimer){
	BubBubbleTimer = _bubBubbleTimer;
}

void MightaInBubbleAnimator::RegistCollitions(Sprite* spr){
	CollisionChecker::Register(spr, bubBubbleAnimator_t, bubBubbleAnimator_t, this, OnCollisionWithBubble);
	CollisionChecker::RegisterBubbleDrivers(spr, this);
	CollisionChecker::RegisterBubbleWrapAroundDrivers(spr, this);
}

void MightaInBubbleAnimator::OnBubbleExpiredTime(void* args){
	DASSERT( args );
	MightaInBubbleAnimator* _this = (MightaInBubbleAnimator*) args;
	MovingPathAnimation *mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("EnemyAgryBubble");
	Sprite *sprite = new Sprite(
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
	Sprite *sprite = new Sprite(
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
	KILL_MIGHTA_ANGRY(MightaInBubbleMediumAngryAnimator, bubble, mighta, args );
}

void MightaInBubbleMediumAngryAnimator::OnCollisionWithBubJump(Sprite *mighta, Sprite *bubble, void *args){
	KILL_MIGHTA_ANGRY(MightaInBubbleMediumAngryAnimator, bubble, mighta, args );
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

	FrameRangeAnimation *fra= (FrameRangeAnimation*)AnimationsParser::GetAnimation("MightaAngryWalkLeft");
	Sprite *n_sprite = new Sprite(
									_this->GetSprite()->GetX(),
									_this->GetSprite()->GetY(),
									_this->GetSprite()->IsGravityAddicted(),
									AnimationFilmHolder::GetFilm("MightaAngry"), 
									Terrain::GetActionLayer(), 
									_this->GetSprite()->GoesLeft()
								);
	MightaAngryWalkingAnimator *frtor=new MightaAngryWalkingAnimator();
	START_ANIMATOR(frtor, n_sprite, fra, GetGameTime() );
	DESTROY_ANIMATOR( _this );
}

void MightaInBubbleHighAngryAnimator::OnCollisionWithBubFalling(Sprite *mighta, Sprite *bubble, void *args){
	KILL_MIGHTA_ANGRY(MightaInBubbleHighAngryAnimator, bubble, mighta, args );
}

void MightaInBubbleHighAngryAnimator::OnCollisionWithBubJump(Sprite *mighta, Sprite *bubble, void *args){
	KILL_MIGHTA_ANGRY(MightaInBubbleHighAngryAnimator, bubble, mighta, args );
}

void MightaInBubbleHighAngryAnimator::OnCollisionWithBubble(Sprite *spr1, Sprite *spr2, void *args){

}