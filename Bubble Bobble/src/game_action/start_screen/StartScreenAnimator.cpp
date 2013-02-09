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

static std::list<AnimationFilm*>				animationFilmHolderLateDestraction;

namespace StartWordAnimatorDeleter{

	struct DeleteAnimationFilm{
		void operator()(AnimationFilm* af){
			delete af;
		}
	};

}

static void StartWordAnimator(const char* word, int x, int y){
	std::vector<Rect> wordRect = BitmapFontHolder::GetWordRects( std::string(word), white);
	AnimationFilm* af = new AnimationFilm( BitmapFontHolder::GetFontsBitmap(), wordRect, word);
	animationFilmHolderLateDestraction.push_back(af);
	LetterSprite* sprite = new LetterSprite( x, y, false, af, Terrain::GetActionLayer(), true);
	MovingAnimation *mpa = (MovingAnimation*) AnimationsParser::GetAnimation("StartScreenStatic");
	StartScreenStaticAnimator* sssamr = new StartScreenStaticAnimator();

	START_ANIMATOR(sssamr, sprite, mpa, GetGameTime() );
}

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

	std::for_each(
					animationFilmHolderLateDestraction.begin(),
					animationFilmHolderLateDestraction.end(),
					StartWordAnimatorDeleter::DeleteAnimationFilm()
				);
	animationFilmHolderLateDestraction.clear();
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

	StartWordAnimator("START GAME", 210, 220);
	StartWordAnimator("OPTIONS", 210, 240);
	StartWordAnimator("EXIT", 210, 260);


	START_ANIMATOR(sssamr, sprite, mpa, GetGameTime() );
	START_ANIMATOR(sssamr1, sprite1, mpa1, GetGameTime() );
	START_ANIMATOR(sssamr2, sprite2, mpa2, GetGameTime() );

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

