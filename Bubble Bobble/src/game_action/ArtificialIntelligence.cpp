#include "ArtificialIntelligence.h"
#include <vector>
#include "Animator.h"
#include "ZenChanAnimator.h"
#include "MightaAnimator.h"
#include "AnimatorHolder.h"

void ArtificialIntelligence::HandleZenChan(){
	std::vector<Animator*> zenChan;

	if(!(zenChan = AnimatorHolder::GetAnimators(zenChanWalkAnimator_t)).empty()){
		for(unsigned int i = 0; i<zenChan.size(); ++i){
			ZenChanWalkingAnimator* r = (ZenChanWalkingAnimator*) zenChan[i];
			int x =  r->GetSprite()->GoesLeft() ? -15 : 15;
			if( r->GetSprite()->IsSolidTerrain( x, 0 ) ){
				r->GetAnimation()->SetDx( -r->GetAnimation()->GetDx()  );
				r->GetSprite()->SetGoesLeft( !r->GetSprite()->GoesLeft() );
			}
		}
	}
}

void ArtificialIntelligence::HandleMighta(){
	std::vector<Animator*> mighta;

	if(!(mighta = AnimatorHolder::GetAnimators(mightaWalkAnimator_t)).empty()){
		for(unsigned int i = 0; i<mighta.size(); ++i){
			MightaWalkingAnimator* r = (MightaWalkingAnimator*) mighta[i];
			int x =  r->GetSprite()->GoesLeft() ? -15 : 15;
			if( r->GetSprite()->IsSolidTerrain( x, 0 ) ){
				r->GetAnimation()->SetDx( -r->GetAnimation()->GetDx()  );
				r->GetSprite()->SetGoesLeft( !r->GetSprite()->GoesLeft() );
			}
		}
	}
}

void ArtificialIntelligence::HandleAngryZenChan(){
	std::vector<Animator*> zenChan;

	if(!(zenChan = AnimatorHolder::GetAnimators(zenChanAngryWalkAnimator_t)).empty()){
		for(unsigned int i = 0; i<zenChan.size(); ++i){
			ZenChanAngryWalkingAnimator* r = (ZenChanAngryWalkingAnimator*) zenChan[i];
			int x =  r->GetSprite()->GoesLeft() ? -15 : 15;
			if( r->GetSprite()->IsSolidTerrain( x, 0 ) ){
				r->GetAnimation()->SetDx( -r->GetAnimation()->GetDx()  );
				r->GetSprite()->SetGoesLeft( !r->GetSprite()->GoesLeft() );
			}
		}
	}
}

void ArtificialIntelligence::HandleAngryMighta(){
	std::vector<Animator*> mighta;

	if(!(mighta = AnimatorHolder::GetAnimators(mightaAngryWalkAnimator_t)).empty()){
		for(unsigned int i = 0; i<mighta.size(); ++i){
			MightaAngryWalkingAnimator* r = (MightaAngryWalkingAnimator*) mighta[i];
			int x =  r->GetSprite()->GoesLeft() ? -15 : 15;
			if( r->GetSprite()->IsSolidTerrain( x, 0 ) ){
				r->GetAnimation()->SetDx( -r->GetAnimation()->GetDx()  );
				r->GetSprite()->SetGoesLeft( !r->GetSprite()->GoesLeft() );
			}
		}
	}
}