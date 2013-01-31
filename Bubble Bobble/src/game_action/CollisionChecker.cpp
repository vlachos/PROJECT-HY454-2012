#include "CollisionChecker.h"
#include "AnimatorHolder.h"
#include "GameActionUtilities.h"
#include "BubAnimator.h"
#include "BubblesAnimator.h"
#include "ZenChanAnimator.h"
#include "MightaAnimator.h"
#include "ZenChanAnimator.h"
#include "BarronVonBlubaAnimator.h"

typedef Sprite* (*SpriteDispacher_t) (Animator* animr);

static Sprite* GetSpriteFromUnkwownAnimator(Animator* animr){std::cout << "Unknown Animator"; return 0;}
static Sprite* GetSpriteFromBubStandAnimator(Animator* animr) { return (( BubStandAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromBubWalkAnimator(Animator* animr) { return (( BubWalkingAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromBubFallingAnimator(Animator* animr) { return (( BubFallingAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromBubOpenMouthAnimator(Animator* animr) { return (( BubOpenMouthAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromBubJumpAnimator(Animator* animr) { return (( BubJumpAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromBubDieAnimator(Animator* animr) { return (( BubDieAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromPonEffectAnimator(Animator* animr) { return (( PonEffectAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromBubBubbleBlastOffAnimator(Animator* animr) { return (( BubBubbleBlastOffAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromBubBubbleAnimator(Animator* animr) { return (( BubBubbleAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromZenChanInBubbleAnimator(Animator* animr) { return (( ZenChanInBubbleAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromZenChanInBubbleMediumAngryAnimator(Animator* animr) { return  0;}//(( Animator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromZenChanInBubbleHighAngryAnimator(Animator* animr) { return  0;}//(( Animator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromMightaInBubbleAnimator(Animator* animr) { return  0;}//(( Animator*)animr )->GetSprite();}
static Sprite* GetSpriteFromMightaInBubbleMediumAngryAnimator(Animator* animr) { return  0;}//(( Animator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromMightaInBubbleHighAngryAnimator(Animator* animr) { return  0;}//(( Animator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromWaterSpecialBubbleAnimator(Animator* animr) { return  0;}//(( Animator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromZenChanStandAnimator(Animator* animr) { return (( ZenChanStandAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromZenChanWalkAnimator(Animator* animr) { return (( ZenChanWalkingAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromZenChanFallingAnimator(Animator* animr) { return (( ZenChanFallingAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromZenChanJumpAnimator(Animator* animr) { return (( ZenChanJumpAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromZenChanAngryStandAnimator(Animator* animr) { return (( ZenChanAngryStandAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromZenChanAngryWalkAnimator(Animator* animr) { return (( ZenChanAngryWalkingAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromZenChanAngryFallingAnimator(Animator* animr) { return (( ZenChanAngryFallingAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromZenChanAngryJumpAnimator(Animator* animr) { return (( ZenChanAngryJumpAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromMightaStandAnimator(Animator* animr) { return (( MightaStandAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromMightaWalkAnimator(Animator* animr) { return (( MightaWalkingAnimator*)animr )->GetSprite(); }
static Sprite* GetSpriteFromMightaFallingAnimator(Animator* animr) { return (( MightaFallingAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromMightaJumpAnimator(Animator* animr) { return (( MightaJumpAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromMightaAngryStandAnimator(Animator* animr) { return (( MightaAngryStandAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromMightaAngryWalkAnimator(Animator* animr) { return (( MightaAngryWalkingAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromMightaAngryFallingAnimator(Animator* animr) { return (( MightaAngryFallingAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromMightaAngryJumpAnimator(Animator* animr) { return (( MightaAngryJumpAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromBaronVonBlubaStandAnimator(Animator* animr) { return (( BaronVonBlubaStandAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromZenChanDieAnimator(Animator* animr) { return (( ZenChanDieAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromMightaDieAnimator(Animator* animr) { return (( MightaDieAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromBananaAnimator(Animator* animr) { return 0;}//(( BananaAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromOrangeAnimator(Animator* animr) { return  0;}//(( OrangeAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromPeachAnimator(Animator* animr) { return  0;}//(( PeachAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromWaterMelonAnimator(Animator* animr) { return  0;}//(( WaterMelonAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromBlueDiamondAnimator(Animator* animr) { return  0;}//(( BlueDiamondAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromRedShoeAnimator(Animator* animr) { return  0;}//(( RedShoeAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromYellowSweetAnimator(Animator* animr) { return  0;}//(( YellowSweetAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromBlueSweetAnimator(Animator* animr) { return  0;}//(( BlueSweetAnimator*)animr )->GetSprite();}
static Sprite* GetSpriteFromPurpleSweetAnimator(Animator* animr) { return  0;}//(( PurpleSweetAnimator*)animr )->GetSprite();}

SpriteDispacher_t spriteDispatcher[] = {
	GetSpriteFromUnkwownAnimator,
	GetSpriteFromBubStandAnimator,
	GetSpriteFromBubWalkAnimator,
	GetSpriteFromBubFallingAnimator,
	GetSpriteFromBubOpenMouthAnimator,
	GetSpriteFromBubJumpAnimator,
	GetSpriteFromBubDieAnimator,
	GetSpriteFromPonEffectAnimator,
	GetSpriteFromBubBubbleBlastOffAnimator,
	GetSpriteFromBubBubbleAnimator,
	GetSpriteFromZenChanInBubbleAnimator,
	GetSpriteFromZenChanInBubbleMediumAngryAnimator,
	GetSpriteFromZenChanInBubbleHighAngryAnimator,
	GetSpriteFromMightaInBubbleAnimator,
	GetSpriteFromMightaInBubbleMediumAngryAnimator,
	GetSpriteFromMightaInBubbleHighAngryAnimator,
	GetSpriteFromWaterSpecialBubbleAnimator,
	GetSpriteFromZenChanStandAnimator,
	GetSpriteFromZenChanWalkAnimator,
	GetSpriteFromZenChanFallingAnimator,
	GetSpriteFromZenChanJumpAnimator,
	GetSpriteFromZenChanAngryStandAnimator,
	GetSpriteFromZenChanAngryWalkAnimator,
	GetSpriteFromZenChanAngryFallingAnimator,
	GetSpriteFromZenChanAngryJumpAnimator,
	GetSpriteFromMightaStandAnimator,
	GetSpriteFromMightaWalkAnimator,
	GetSpriteFromMightaFallingAnimator,
	GetSpriteFromMightaJumpAnimator,
	GetSpriteFromMightaAngryStandAnimator,
	GetSpriteFromMightaAngryWalkAnimator,
	GetSpriteFromMightaAngryFallingAnimator,
	GetSpriteFromMightaAngryJumpAnimator,
	GetSpriteFromBaronVonBlubaStandAnimator,
	GetSpriteFromZenChanDieAnimator,
	GetSpriteFromMightaDieAnimator,
	GetSpriteFromBananaAnimator,
	GetSpriteFromOrangeAnimator,
	GetSpriteFromPeachAnimator,
	GetSpriteFromWaterMelonAnimator,
	GetSpriteFromBlueDiamondAnimator,
	GetSpriteFromRedShoeAnimator,
	GetSpriteFromYellowSweetAnimator,
	GetSpriteFromBlueSweetAnimator,
	GetSpriteFromPurpleSweetAnimator
};

CollisionChecker* CollisionChecker::Checker;
CollisionChecker::CollisionPairsList CollisionChecker::CollisionPairs;

CollisionChecker::CollisionChecker(){
	CollisionPairs.clear();
	DASSERT(CollisionPairs.size() == 0);
}

CollisionChecker::~CollisionChecker(){
	CollisionChecker::CollisionPairs.clear();
	DASSERT(CollisionPairs.size() == 0);
}

void CollisionChecker::SingletonCreate(){
	CollisionChecker::Checker = DNEWCLASS(CollisionChecker,() );
}

void CollisionChecker::Register (Sprite* s1, Sprite* s2, void* Args, CollisionCallback callBack){ 
	DASSERT(s1); DASSERT(s2); //DASSERT(callBack);
	DASSERT( s1!=s2 );

	unsigned int oldSize = CollisionPairs.size();
	CollisionPairsList::const_iterator info;

	if ((info = std::find_if( CollisionPairs.begin(), CollisionPairs.end(), Find(s1,s2) ) ) == CollisionPairs.end() ){

		CollisionInfo newCollisionInfo;
		newCollisionInfo.master = s1;
		newCollisionInfo.slave = s2;
		newCollisionInfo.Args = Args;
		newCollisionInfo.callBack = callBack;

		CollisionChecker::CollisionPairs.push_back(newCollisionInfo);

		DASSERT(CollisionPairs.size() == oldSize + 1);
	}
	else{
		DASSERT(CollisionPairs.size() == oldSize);
	}
}

void CollisionChecker::Register (Sprite* s1, animatorType_t start, animatorType_t end, void* Args, CollisionCallback callBack){ 
	DASSERT(s1); //DASSERT(callBack);

	Sprite* s2 = 0;
	std::vector<Animator*> relatedAnimators = AnimatorHolder::GetAnimators(start,end);
	
	for(unsigned int i=0; i<relatedAnimators.size(); ++i){
		DASSERT(0 <= start<= ANIMATORS_SIZE);
		
		s2 = spriteDispatcher[(relatedAnimators[i]->GetAnimatorType())](relatedAnimators[i]);
		
		DASSERT(s2);

		CollisionChecker::Register (s1, s2, Args, callBack);
	}
}

void CollisionChecker::Register (Sprite* s1, animatorType_t start, animatorType_t end, CollisionCallback callBack){
	DASSERT(s1); //DASSERT(callBack);

	Sprite* s2 = 0;
	std::vector<Animator*> relatedAnimators = AnimatorHolder::GetAnimators(start,end);
	for(unsigned int i=0; i<relatedAnimators.size(); ++i){
		DASSERT(0 <= start<= ANIMATORS_SIZE);
		s2 = spriteDispatcher[(relatedAnimators[i]->GetAnimatorType())](relatedAnimators[i]);
		DASSERT(s2);

		CollisionChecker::Register (s1, s2, relatedAnimators[i], callBack);
	}
}

void CollisionChecker::RegisterPair (Sprite* s1, animatorType_t start, animatorType_t end, Animator* anim, CollisionCallback callBack){
	DASSERT( s1 && anim );
	std::vector<Animator*> relatedAnimators = AnimatorHolder::GetAnimators(start,end);
	for(unsigned int i=0; i<relatedAnimators.size(); ++i){	
		Animator* amtr = (Animator*) relatedAnimators[i];
		Sprite* s2 = spriteDispatcher[(amtr->GetAnimatorType())](relatedAnimators[i]);
		DASSERT( s2 );
		std::pair< Animator*, Animator* >* args = (std::pair< Animator*, Animator* >*)malloc(sizeof(std::pair< Animator*, Animator* >));
		args->first = anim;
		args->second = amtr;
		CollisionChecker::Register (s1, s2, (void*)args, callBack);
	}
}


void CollisionChecker::Cancel (Sprite* s){
	DASSERT(s);
	unsigned int oldSize;
	bool exists = false;

	CollisionPairsList::const_iterator info;
	while ((info = std::find_if( CollisionPairs.begin(), CollisionPairs.end(), FindAny(s) ) ) != CollisionPairs.end()){
		oldSize = CollisionPairs.size();
		CollisionPairs.erase(info);
		DASSERT(CollisionPairs.size() == oldSize - 1);
	}
}


void CollisionChecker::Cancel (Sprite* s1, Sprite* s2){
	DASSERT(s1); DASSERT(s2);
	unsigned int oldSize;
	CollisionPairsList::const_iterator info;

	oldSize = CollisionPairs.size();
	if ((info = std::find_if( CollisionPairs.begin(), CollisionPairs.end(), Find(s1,s2) ) ) != CollisionPairs.end() ){
		CollisionPairs.erase(info);
		DASSERT(CollisionPairs.size() == oldSize - 1);
	}
	else{
		DASSERT(CollisionPairs.size() == oldSize);
	}
}


void CollisionChecker::SingletonCleanUp(){
	delete Checker;
}

