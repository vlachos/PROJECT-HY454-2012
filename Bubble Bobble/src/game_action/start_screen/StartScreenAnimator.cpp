#include "StartScreenAnimator.h"
#include "OptionsScreenAnimator.h"
#include "AnimatorHolder.h"
#include "AnimationFilmHolder.h"
#include "BitmapFontHolder.h"
#include "Terrain.h"
#include "ScrollingAnimator.h"
#include "ScrollingAnimation.h"
#include "MovingPathAnimation.h"
#include "BubAnimator.h"
#include "GameActionUtilities.h"
#include "AnimationsParser.h"
#include "CollisionChecker.h"
#include "BitmapLoader.h"
#include "MultiSprite.h"
#include "SoundAPI.h"

#include "SpritesParser.h"
#include "AnimationFilm.h"
#include "BitmapLoader.h"

#include "StageInitializer.h"

static std::list<AnimationFilm*>	animationFilmHolderLateDestraction;

namespace StartWordAnimatorDeleter{

	struct DeleteAnimationFilm{
		void operator()(AnimationFilm* af){
			delete af;
		}
	};

}

static void StartWordAnimator(const char* word, int x, int y, FontColor_t color){
	std::vector<Rect> wordRect = BitmapFontHolder::GetWordRects( std::string(word), color);
	AnimationFilm* af = new AnimationFilm( BitmapFontHolder::GetFontsBitmap(), wordRect, word);
	animationFilmHolderLateDestraction.push_back(af);
	MultiSprite* sprite = new MultiSprite( x, y, false, af, Terrain::GetActionLayer(), true);
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
	StageInitializer::InitNextStage();
	StageInitializer::ScrollToNextStage();
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
	START_ANIMATOR(sssamr, sprite, mpa, GetGameTime() );

	MovingAnimation *mpa1 = (MovingAnimation*) AnimationsParser::GetAnimation("StartScreenStatic");
	Sprite *sprite1 = new Sprite(
								10,
								340,
								false,						
								AnimationFilmHolder::GetFilm( "UOCEmblem" ), 
								Terrain::GetActionLayer(), 
								true
							);
	sprite1->SetOnDrugs(true);
	StartScreenStaticAnimator* sssamr1 = new StartScreenStaticAnimator();
	START_ANIMATOR(sssamr1, sprite1, mpa1, GetGameTime() );

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
	START_ANIMATOR(sssamr2, sprite2, mpa2, GetGameTime() );

	StartWordAnimator("START GAME", 210, 220, white);
	StartWordAnimator("OPTIONS", 210, 240, white);
	StartWordAnimator("EXIT", 210, 260, white);

	StartWordAnimator("CREATORS:", 180, 320, red);
	StartWordAnimator("JAPOSTOL", 340, 320, red);
	StartWordAnimator("VLACHOS", 348, 340, red);
	StartWordAnimator("AKYRIAK", 348, 360, red);

	StartWordAnimator("    CSD UOC", 128, 390, white);
	StartWordAnimator(" COURSE - HY454", 120, 420, white);
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
												SoundAPI::PlaySoundOnce(SoundAPI::soundKind_theStoryBegin_t, true);
												StartScreenAnimatorActions::StartGame();
												break;
		case START_SCREEN_SELECTOR_OPTIONS:		StartScreenAnimatorActions::CleanUpStartScreen();
												OptionsScreenAnimatorActions::StartOptionsScreen(210);
												break;
		case START_SCREEN_SELECTOR_EXIT:			retVal = false;
												break;

		default:								DASSERT(false);
	}

	return retVal;
}

