#include "OptionsScreenAnimator.h"
#include "StartScreenAnimator.h"
#include "MovingPathAnimation.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "BubAnimator.h"
#include "GameActionUtilities.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"
#include "CollisionChecker.h"

#define OPTIONS_SCREEN_SELECTOR_OPTION1 210
#define OPTIONS_SCREEN_SELECTOR_OPTION2 230
#define OPTIONS_SCREEN_SELECTOR_OPTION3 250
#define OPTIONS_SCREEN_SELECTOR_OPTION4 270
#define OPTIONS_SCREEN_SELECTOR_BACK	290
#define OPTIONS_SCREEN_SELECTOR_OFFSET	20

void OptionsScreenAnimatorActions::CleanUpOptionsScreen(){
	std::vector<Animator*> optionScreenAnimators;
		
	optionScreenAnimators = AnimatorHolder::GetAnimators(optionsScreenStaticAnimator_t);
	DASSERT(!optionScreenAnimators.empty());
	for(unsigned int i=0; i<optionScreenAnimators.size(); ++i){
		OptionsScreenStaticAnimator* optionScreenAnimator = (OptionsScreenStaticAnimator*) optionScreenAnimators[i];
		REMOVE_FROM_ACTION_ANIMATOR( optionScreenAnimator );
		DESTROY_ANIMATOR( optionScreenAnimator );
	}
	optionScreenAnimators = AnimatorHolder::GetAnimators(optionsScreenSelectorAnimator_t);
	DASSERT(optionScreenAnimators.size() == 1);
	OptionsScreenSelectorAnimator* optionScreenSelectorAnimator = (OptionsScreenSelectorAnimator*) optionScreenAnimators.front();
	REMOVE_FROM_ACTION_ANIMATOR( optionScreenSelectorAnimator );
	DESTROY_ANIMATOR( optionScreenSelectorAnimator );
}

void OptionsScreenAnimatorActions::StartOptionsScreen(){
	MovingAnimation *mpa1 = (MovingAnimation*) AnimationsParser::GetAnimation("StartScreenStatic");
	Sprite *sprite1 = new Sprite(
								10,
								320,
								false,						
								AnimationFilmHolder::GetFilm( "UOCEmblem" ), 
								Terrain::GetActionLayer(), 
								true
							);
	sprite1->SetOnDrugs(true);
	OptionsScreenStaticAnimator* sssamr1 = new OptionsScreenStaticAnimator();

	FrameRangeAnimation *mpa2 = (FrameRangeAnimation*) AnimationsParser::GetAnimation("StartScreenSelector");
	Sprite *sprite2 = new Sprite(
								170,
								210,
								false,						
								AnimationFilmHolder::GetFilm( "SelecterOption" ), 
								Terrain::GetActionLayer(), 
								true
							);
	sprite2->SetOnDrugs(true);
	OptionsScreenSelectorAnimator* sssamr2 = new OptionsScreenSelectorAnimator();

	START_ANIMATOR(sssamr1, sprite1, mpa1, GetGameTime() );
	START_ANIMATOR(sssamr2, sprite2, mpa2, GetGameTime() );
}

OptionsScreenStaticAnimator::OptionsScreenStaticAnimator(){

}

OptionsScreenSelectorAnimator::OptionsScreenSelectorAnimator(){

}

void OptionsScreenSelectorAnimator::GoUp(){
	DASSERT( this->GetSprite() && this->GetAnimation() );
	int y = this->GetSprite()->GetY();
	if( y>OPTIONS_SCREEN_SELECTOR_OPTION1 )
		this->GetSprite()->SetY( y - OPTIONS_SCREEN_SELECTOR_OFFSET );
}

void OptionsScreenSelectorAnimator::GoDown(){
	DASSERT( this->GetSprite() && this->GetAnimation() );
	int y = this->GetSprite()->GetY();
	if( y<OPTIONS_SCREEN_SELECTOR_BACK )
		this->GetSprite()->SetY( y + OPTIONS_SCREEN_SELECTOR_OFFSET );
}

bool OptionsScreenSelectorAnimator::PressEnter(){
	bool retVal = true;
	DASSERT( this->GetSprite() && this->GetAnimation() );
	switch(this->GetSprite()->GetY()){
		case OPTIONS_SCREEN_SELECTOR_OPTION1:	
												break;
		case OPTIONS_SCREEN_SELECTOR_OPTION2:		
												break;
		case OPTIONS_SCREEN_SELECTOR_OPTION3:	
												break;
		case OPTIONS_SCREEN_SELECTOR_OPTION4:	
												break;
		case OPTIONS_SCREEN_SELECTOR_BACK:		OptionsScreenAnimatorActions::CleanUpOptionsScreen();
												StartScreenAnimatorActions::StartStartScreen();
												break;

		default:							DASSERT(false);
	}

	return retVal;
}