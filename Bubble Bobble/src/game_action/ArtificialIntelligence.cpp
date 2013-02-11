#include "ArtificialIntelligence.h"
#include <vector>
#include "Animator.h"
#include "ZenChanAnimator.h"
#include "MightaAnimator.h"
#include "BarronVonBlubaAnimator.h"
#include "RiverAnimator.h"
#include "AnimatorHolder.h"
#include "CollisionChecker.h"
#include "GameActionUtilities.h"
#include "AnimationsParser.h"


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
			std::vector<Animator*> anim = AnimatorHolder::GetAnimators(bubStandAnimator_t, bubJumpAnimator_t);
			if(!anim.empty()){
				Sprite * bub = ((MovingAnimator*)anim.front())->GetSprite();
				static int offset = 10;
				if(bub->GetY() - offset <= r->GetSprite()->GetY() &&
					bub->GetY() + bub->GetFrameBox().GetHeigth() + offset >= r->GetSprite()->GetY() ){
					//throwbubble and fix direction

				}
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


void ArtificialIntelligence::HandleRiver(){
	std::vector<Animator*> river;

	if(!(river = AnimatorHolder::GetAnimators(riverAnimator_t)).empty()){
		for(unsigned int i = 0; i<river.size(); ++i){
			RiverAnimator* r = (RiverAnimator*) river[i];
			if( r->GetSprite()->IsSolidTerrain( r->GetSprite()->GoesLeft() ? -1 : 1, 0 ) ){

				r->GetAnimation()->SetDx( -r->GetAnimation()->GetDx()  );
				r->GetSprite()->SetGoesLeft( !r->GetSprite()->GoesLeft() );
			}
		}
	}
}

void ArtificialIntelligence::HandleBarronVonBluba(){
	std::vector<Animator*> barron;

	if(!(barron = AnimatorHolder::GetAnimators(baronVonBlubaStandAnimator_t)).empty()){
		DASSERT(barron.size() == 1);
		BaronVonBlubaStandAnimator* r = (BaronVonBlubaStandAnimator*) barron.front();
		Sprite* baron = r->GetSprite();
		std::vector<Animator*> anim = AnimatorHolder::GetAnimators(bubStandAnimator_t, bubJumpAnimator_t);
		if(!anim.empty()){
			const int offset = 30;
			MovingPathAnimation *mpa;
			Sprite * bub = ((MovingAnimator*)anim.front())->GetSprite();
			if(baron->GetX() + offset  < bub->GetX() ){
				if(r->prevDirection == BaronVonBlubaStandAnimator::direction_up_t || 
					r->prevDirection == BaronVonBlubaStandAnimator::direction_down_t){
						mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("BarronVonBlubaRushRight");
				}else
				if(baron->GetY() + offset < bub->GetY())
					mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("BarronVonBlubaRushUp");
				else
					mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("BarronVonBlubaRushDown");
			}else
			if(baron->GetX() > bub->GetX() ){
				if(r->prevDirection == BaronVonBlubaStandAnimator::direction_up_t || 
					r->prevDirection == BaronVonBlubaStandAnimator::direction_down_t){
						mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("BarronVonBlubaRushLeft");
				}else
				if(baron->GetY()<bub->GetY())
					mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("BarronVonBlubaRushUp");
				else
					mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("BarronVonBlubaRushDown");
			}else
			if(baron->GetY() > bub->GetY() ){
				if(r->prevDirection == BaronVonBlubaStandAnimator::direction_left_t || 
					r->prevDirection == BaronVonBlubaStandAnimator::direction_rigth_t){
						mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("BarronVonBlubaRushUp");
				}else
				if(baron->GetX()>bub->GetX())
					mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("BarronVonBlubaRushLeft");
				else
					mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("BarronVonBlubaRushRight");
			}else
			if(baron->GetY() < bub->GetY() ){
				if(r->prevDirection == BaronVonBlubaStandAnimator::direction_left_t || 
					r->prevDirection == BaronVonBlubaStandAnimator::direction_rigth_t){
						mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("BarronVonBlubaRushDown");
				}else
				if(baron->GetX()>bub->GetX())
					mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("BarronVonBlubaRushLeft");
				else
					mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("BarronVonBlubaRushRight");
			}else
				DASSERT(false);

			baron->ClearListeners();
			BaronVonBlubaRushAnimator* bvbrar = new BaronVonBlubaRushAnimator();
			bvbrar->RegistCollitions(baron);

			REMOVE_FROM_ACTION_ANIMATOR( r );
			DESTROY_ANIMATOR_WITHOUT_SPRITE(r);

			START_ANIMATOR(bvbrar, baron, mpa, GetGameTime() );
		}
		
	}
}