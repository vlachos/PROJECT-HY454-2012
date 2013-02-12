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
#include "MultiSprite.h"
#include "SoundAPI.h"
#include "BubbleLogic.h"

#define OPTIONS_SCREEN_SELECTOR_OPTION1 210
#define OPTIONS_SCREEN_SELECTOR_OPTION2 230
#define OPTIONS_SCREEN_SELECTOR_OPTION3 250
#define OPTIONS_SCREEN_SELECTOR_OPTION4 270
#define OPTIONS_SCREEN_SELECTOR_BACK	290
#define OPTIONS_SCREEN_SELECTOR_OFFSET	20

static std::list<AnimationFilm*>				animationFilmHolderLateDestraction;

namespace OptionsDeleteAnimationFilm{

	struct DeleteAnimationFilm{
		void operator()(AnimationFilm* af){
			delete af;
		}
	};

}

char * option1 = "MUSIC ON";
char * option2 = "WALK SLOW";
char * option3 = "BUBBLE SPEED SLOW";
char * option4 = "BLAST POWER SLOW";

static void StartWordAnimator(const char* word, int x, int y){
	std::vector<Rect> wordRect = BitmapFontHolder::GetWordRects( std::string(word), white);
	AnimationFilm* af = new AnimationFilm( BitmapFontHolder::GetFontsBitmap(), wordRect, word);
	animationFilmHolderLateDestraction.push_back(af);
	MultiSprite* sprite = new MultiSprite( x, y, false, af, Terrain::GetActionLayer(), true);
	MovingAnimation *mpa = (MovingAnimation*) AnimationsParser::GetAnimation("StartScreenStatic");
	OptionsScreenStaticAnimator* sssamr = new OptionsScreenStaticAnimator();

	START_ANIMATOR(sssamr, sprite, mpa, GetGameTime() );
}

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

	std::for_each(
					animationFilmHolderLateDestraction.begin(),
					animationFilmHolderLateDestraction.end(),
					OptionsDeleteAnimationFilm::DeleteAnimationFilm()
				);
	animationFilmHolderLateDestraction.clear();
}

void OptionsScreenAnimatorActions::StartOptionsScreen(int y){
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
								y,
								false,						
								AnimationFilmHolder::GetFilm( "SelecterOption" ), 
								Terrain::GetActionLayer(), 
								true
							);
	sprite2->SetOnDrugs(true);
	OptionsScreenSelectorAnimator* sssamr2 = new OptionsScreenSelectorAnimator();

	StartWordAnimator(option1, 210, 220);
	StartWordAnimator(option2, 210, 240);
	StartWordAnimator(option3, 210, 260);
	StartWordAnimator(option4, 210, 280);
	StartWordAnimator("BACK", 210, 300);

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
	int y = 210;
	DASSERT( this->GetSprite() && this->GetAnimation() );
	switch(this->GetSprite()->GetY()){
		case OPTIONS_SCREEN_SELECTOR_OPTION1:	if(!strcmp(option1, "MUSIC ON")) {
													SoundAPI::mute(true);
													option1 = "MUSIC OFF";
												}else{
													SoundAPI::mute(false);
													option1 = "MUSIC ON";
													SoundAPI::PlaySoundContinue(SoundAPI::soundKind_enterYourInitials_t, true);
												}
												break;
		case OPTIONS_SCREEN_SELECTOR_OPTION2:	if(!strcmp(option2, "WALK SLOW")) {
													option2 = "WALK FAST";
													BubbleLogic::GetBobProfile()->SetRedShoes(true);
												}else{
													option2 = "WALK SLOW";
													BubbleLogic::GetBobProfile()->SetRedShoes(false);
												}
												y = 230;
												break;
		case OPTIONS_SCREEN_SELECTOR_OPTION3:	if(!strcmp(option3, "BUBBLE SPEED SLOW")) {
													option3 = "BUBBLE SPEED FAST";
													BubbleLogic::GetBobProfile()->SetBlueSwt(true);
												}else{
													option3 = "BUBBLE SPEED SLOW";
													BubbleLogic::GetBobProfile()->SetBlueSwt(false);
												}
												y = 250;
												break;
		case OPTIONS_SCREEN_SELECTOR_OPTION4:	if(!strcmp(option4, "BLAST POWER SLOW")) {
													option4 = "BLAST POWER FAST";
													BubbleLogic::GetBobProfile()->SetPurpleSwt(true);
												}else{
													option4 = "BLAST POWER SLOW";
													BubbleLogic::GetBobProfile()->SetPurpleSwt(false);
												}
												y = 270;
												break;
		case OPTIONS_SCREEN_SELECTOR_BACK:		OptionsScreenAnimatorActions::CleanUpOptionsScreen();
												StartScreenAnimatorActions::StartStartScreen();
												return true;

		default:							DASSERT(false);
	}

	OptionsScreenAnimatorActions::CleanUpOptionsScreen();
	OptionsScreenAnimatorActions::StartOptionsScreen(y);

	return retVal;
}