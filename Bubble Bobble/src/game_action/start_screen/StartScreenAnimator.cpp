#include "StartScreenAnimator.h"
#include "OptionsScreenAnimator.h"
#include "MovingPathAnimation.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"
#include "BubAnimator.h"
#include "GameActionUtilities.h"
#include "AnimationsParser.h"
#include "AnimatorHolder.h"
#include "BitmapFontHolder.h"
#include "CollisionChecker.h"
#include "BitmapLoader.h"
#include "LetterSprite.h"


#include "SpritesParser.h"
#include "AnimationFilm.h"
#include "BitmapLoader.h"

void StartScreenAnimatorActions::CleanUpStartScreen(){
	std::vector<Animator*> startScreenAnimators;
		
	startScreenAnimators = AnimatorHolder::GetAnimators(startScreenStaticAnimator_t);
	DASSERT(!startScreenAnimators.empty());
	for(unsigned int i=0; i<startScreenAnimators.size(); ++i){
		StartScreenStaticAnimator* startScreenAnimator = (StartScreenStaticAnimator*) startScreenAnimators[i];
		REMOVE_FROM_ACTION_ANIMATOR( startScreenAnimator );
		DESTROY_ANIMATOR( startScreenAnimator );
	}
	startScreenAnimators = AnimatorHolder::GetAnimators(startScreenSelectorAnimator_t);
	DASSERT(startScreenAnimators.size() == 1);
	StartScreenSelectorAnimator* startScreenSelectorAnimator = (StartScreenSelectorAnimator*) startScreenAnimators.front();
	REMOVE_FROM_ACTION_ANIMATOR( startScreenSelectorAnimator );
	DESTROY_ANIMATOR( startScreenSelectorAnimator );
}

void StartScreenAnimatorActions::StartGame(){
	MovingPathAnimation *mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("BubInBubble");
	Sprite *sprite = new Sprite(
								250,
								30,
								false,						
								AnimationFilmHolder::GetFilm( "BubInBubble" ), 
								Terrain::GetActionLayer(), 
								false
							);
	sprite->SetOnDrugs(true);
	BubInBubbleAnimator* bibamr = new BubInBubbleAnimator();
	START_ANIMATOR(bibamr, sprite, mpa, GetGameTime() );
}

void StartScreenAnimatorActions::StartStartScreen(){
	MovingAnimation *mpa = (MovingAnimation*) AnimationsParser::GetAnimation("StartScreenStatic");
	Sprite *sprite = new Sprite(
								150,
								30,
								false,						
								AnimationFilmHolder::GetFilm( "BubbleBobbleIntro" ), 
								Terrain::GetActionLayer(), 
								true
							);
	sprite->SetOnDrugs(true);
	StartScreenStaticAnimator* sssamr = new StartScreenStaticAnimator();

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
	StartScreenStaticAnimator* sssamr1 = new StartScreenStaticAnimator();



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
	StartScreenSelectorAnimator* sssamr2 = new StartScreenSelectorAnimator();

	
	std::vector<Rect> test = BitmapFontHolder::GetWordRects( std::string("TEST"), white);
	//std::cout<< test.size()<<"\n";
	AnimationFilm* af = new AnimationFilm( BitmapFontHolder::GetFontsBitmap(), test, "testSprite");
	LetterSprite* sprite3 = new LetterSprite( 150, 200, false, af, Terrain::GetActionLayer(), true);
	MovingAnimation *mpa3 = (MovingAnimation*) AnimationsParser::GetAnimation("StartScreenStatic");
	StartScreenStaticAnimator* sssamr3 = new StartScreenStaticAnimator();

	START_ANIMATOR(sssamr, sprite, mpa, GetGameTime() );
	START_ANIMATOR(sssamr1, sprite1, mpa1, GetGameTime() );
	START_ANIMATOR(sssamr2, sprite2, mpa2, GetGameTime() );
	START_ANIMATOR(sssamr3, sprite3, mpa3, GetGameTime() );
}

StartScreenStaticAnimator::StartScreenStaticAnimator(){

}

StartScreenSelectorAnimator::StartScreenSelectorAnimator(){

}

void StartScreenSelectorAnimator::GoUp(){
	DASSERT( this->GetSprite() && this->GetAnimation() );
	int y = this->GetSprite()->GetY();
	if( y>START_SCREEN_SELECTOR_START_GAME )
		this->GetSprite()->SetY( y - START_SCREEN_SELECTOR_OFFSET );
}

void StartScreenSelectorAnimator::GoDown(){
	DASSERT( this->GetSprite() && this->GetAnimation() );
	int y = this->GetSprite()->GetY();
	if( y<START_SCREEN_SELECTOR_EXIT )
		this->GetSprite()->SetY( y + START_SCREEN_SELECTOR_OFFSET );
}

bool StartScreenSelectorAnimator::PressEnter(){
	bool retVal = true;
	DASSERT( this->GetSprite() && this->GetAnimation() );
	switch(this->GetSprite()->GetY()){
		case START_SCREEN_SELECTOR_START_GAME:	StartScreenAnimatorActions::CleanUpStartScreen();
												StartScreenAnimatorActions::StartGame();
												break;
		case START_SCREEN_SELECTOR_OPTIONS:		StartScreenAnimatorActions::CleanUpStartScreen();
												OptionsScreenAnimatorActions::StartOptionsScreen();
												break;
		case START_SCREEN_SELECTOR_EXIT:			retVal = false;
												break;

		default:								DASSERT(false);
	}

	return retVal;
}

