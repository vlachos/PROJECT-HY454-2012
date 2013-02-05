#include "ArtificialIntelligence.h"
#include <vector>
#include "Animator.h"
#include "ZenChanAnimator.h"
#include "AnimatorHolder.h"

void ArtificialIntelligence::HandleZenChan(){
	std::vector<Animator*> zenChan;

	if(!(zenChan = AnimatorHolder::GetAnimators(zenChanWalkAnimator_t)).empty()){
		for(unsigned int i = 0; i<zenChan.size(); ++i){
			ZenChanWalkingAnimator* r = (ZenChanWalkingAnimator*) zenChan[i];
			int x =  r->GetSprite()->GoesLeft() ? -15 : 15;
			if( r->GetSprite()->IsSolidTerrain( x, 0 ) ){
				r->GetAnimation()->SetDx( -r->GetAnimation()->GetDx()  );
			}
			
		}
	}
}