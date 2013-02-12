#include "InputManage.h"
#include "GameActionUtilities.h"
#include "vector"
#include "CollisionChecker.h"
#include "Animator.h"
#include "AnimatorHolder.h"
#include "BubAnimator.h"
#include "AnimationsParser.h"
#include "ZenChanAnimator.h"
#include "BubblesAnimator.h"
#include "StartScreenAnimator.h"
#include "OptionsScreenAnimator.h"
#include "BubbleLogic.h"
#include "MightaAnimator.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"

#define START_MENU_SELECTOR_DELAY 200
#define PAUSE_DELAY 500
#define BLAST_DELAY 400
#define BLAST_QUICK_DELAY 200


/////////////////////////static functions

static bool CheckDxDirectionWalking(BubWalkingAnimator* bub, bool direction){
	BubWalkingAnimator* bubWalk = bub;
	offset_t offset = bubWalk->GetAnimation()->GetDx();
	DASSERT( offset!=0 );
	if( ( direction ? (offset > 0) : (offset < 0) ) ) {
		bubWalk->GetAnimation()->SetDx(-offset);
		bubWalk->GetSprite()->SetGoesLeft(direction);
	}

	return true;
}

static bool CheckDxDirectionStand(BubStandAnimator* bub, bool direction){
	BubStandAnimator* _this = bub;

	REMOVE_FROM_ACTION_ANIMATOR( _this );

	DASSERT( _this->GetAnimation() && _this->GetSprite() );

	animid_t id = _this->GetAnimation()->GetId();
	Sprite* newSprite = _this->GetSprite();
	newSprite->ClearListeners();
	FrameRangeAnimation * ma = (FrameRangeAnimation*) AnimationsParser::GetAnimation( BubbleLogic::GetBubProfile()->GetBubWalkAnimation(direction) );
	newSprite->SetFrame(0);
	newSprite->SetGoesLeft(direction);

	BubWalkingAnimator* mar = new BubWalkingAnimator();

	newSprite->AddStartFallingListener(mar);
	mar->SetOnFinish(BubWalkingAnimator::OnFinishCallback, mar);
	mar->RegistCollitions(newSprite);

	START_ANIMATOR( mar, newSprite, ma, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( _this );
	return true;
}

static bool CheckDyDirectionWalking(BubWalkingAnimator* bub){
	BubWalkingAnimator* _this = bub;
	DASSERT( _this->GetAnimation() && _this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( _this );

	Sprite* newSprite = _this->GetSprite();
	newSprite->ClearListeners();
	MovingPathAnimation * ma = (MovingPathAnimation*) AnimationsParser::GetAnimation( BubbleLogic::GetBubProfile()->GetBubJump());
	BubJumpAnimator* mar = new BubJumpAnimator();
	mar->RegistCollitions(newSprite);
	
	START_ANIMATOR( mar, newSprite, ma, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( _this );
	return true;
}

static bool CheckDyDirectionStand(BubStandAnimator* bub){
	BubStandAnimator* _this = bub;
	DASSERT( _this->GetAnimation() && _this->GetSprite() );
	REMOVE_FROM_ACTION_ANIMATOR( _this );

	Sprite* newSprite = _this->GetSprite();

	newSprite->ClearListeners();
	MovingPathAnimation * ma = (MovingPathAnimation*) AnimationsParser::GetAnimation( BubbleLogic::GetBubProfile()->GetBubJump() );
	BubJumpAnimator* mar = new BubJumpAnimator();
	mar->RegistCollitions(newSprite);
	
	START_ANIMATOR( mar, newSprite, ma, GetGameTime() );
	DESTROY_ANIMATOR_WITHOUT_SPRITE( _this );

	return true;
}


///////////////////////////////static funcs


static bool _OnKeyUp(bool bubId){
	std::vector<Animator*> bub;

	if(!(bub = AnimatorHolder::GetAnimators(bubWalkAnimator_t)).empty()){
		for(std::vector<Animator*>::const_iterator ci = bub.begin(); ci!=bub.end(); ++ci){	
			if( ( (BubWalkingAnimator*) *ci )->GetSprite()->IsBub() == bubId ){								
				return CheckDyDirectionWalking((BubWalkingAnimator*)*ci); 
			}																				
		}
	}
	if(!(bub = AnimatorHolder::GetAnimators(bubStandAnimator_t)).empty()){

		for(std::vector<Animator*>::const_iterator ci = bub.begin(); ci!=bub.end(); ++ci){	
			if( ( (BubStandAnimator*) *ci )->GetSprite()->IsBub() == bubId ){
				if(bubId)
					BubbleLogic::GetBubProfile()->SetJumpOnMove(false);
				else
					BubbleLogic::GetBobProfile()->SetJumpOnMove(false);
				return CheckDyDirectionStand((BubStandAnimator*)*ci); 
			}																				
		}
	}
	return false;
}

static bool _OnKeyLeft(bool bubId){

	std::vector<Animator*> bub;

	if(!(bub = AnimatorHolder::GetAnimators(bubWalkAnimator_t)).empty()){
		for(std::vector<Animator*>::const_iterator ci = bub.begin(); ci!=bub.end(); ++ci){	
			if( ( (BubWalkingAnimator*) *ci )->GetSprite()->IsBub() == bubId ){								
				return CheckDxDirectionWalking((BubWalkingAnimator*)*ci, true);
			}																				
		}
	}
	if(!(bub = AnimatorHolder::GetAnimators(bubStandAnimator_t)).empty()){
		for(std::vector<Animator*>::const_iterator ci = bub.begin(); ci!=bub.end(); ++ci){	
			if( ( (BubStandAnimator*) *ci )->GetSprite()->IsBub() == bubId ){								
				return CheckDxDirectionStand((BubStandAnimator*)*ci, true);
			}																				
		}
	}
	if(!(bub = AnimatorHolder::GetAnimators(bubJumpAnimator_t)).empty()){
		for(std::vector<Animator*>::const_iterator ci = bub.begin(); ci!=bub.end(); ++ci){	
			if( ( (BubJumpAnimator*) *ci )->GetSprite()->IsBub() == bubId ){	
				BubJumpAnimator *bja=(BubJumpAnimator *)*ci;
				if(bubId)
					BubbleLogic::GetBubProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(-2,0):
													   bja->GetSprite()->Move(-1,0);
				else
					BubbleLogic::GetBobProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(-2,0):
													   bja->GetSprite()->Move(-1,0);
				bja->GetSprite()->SetGoesLeft(true);
				return true;
			}																				
		}
	}
	if(!(bub = AnimatorHolder::GetAnimators(bubJumpOpenMouthAnimator_t)).empty()){
		for(std::vector<Animator*>::const_iterator ci = bub.begin(); ci!=bub.end(); ++ci){	
			if( ( (BubJumpOpenMouthAnimator*) *ci )->GetSprite()->IsBub() == bubId ){								
				BubJumpOpenMouthAnimator *bja=(BubJumpOpenMouthAnimator *)*ci;
				if(bubId)
					BubbleLogic::GetBubProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(-2,0):
													   bja->GetSprite()->Move(-1,0);
				else
					BubbleLogic::GetBobProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(-2,0):
													   bja->GetSprite()->Move(-1,0);
				bja->GetSprite()->SetGoesLeft(true);
				return true;
			}																				
		}
	}
	if(!(bub = AnimatorHolder::GetAnimators(bubFallingAnimator_t)).empty()){
		for(std::vector<Animator*>::const_iterator ci = bub.begin(); ci!=bub.end(); ++ci){	
			if( ( (BubFallingAnimator*) *ci )->GetSprite()->IsBub() == bubId ){								
				BubFallingAnimator *bja=(BubFallingAnimator *)*ci;
				if(bubId)
					BubbleLogic::GetBubProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(-2,0):
													   bja->GetSprite()->Move(-1,0);
				else
					BubbleLogic::GetBobProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(-2,0):
													   bja->GetSprite()->Move(-1,0);
				bja->GetSprite()->SetGoesLeft(true);
				return true;
			}																				
		}
	}

	return false;
}

static bool _OnKeyRight(bool bubId){
	std::vector<Animator*> bub;
		
	if(!(bub = AnimatorHolder::GetAnimators(bubWalkAnimator_t)).empty()){
		for(std::vector<Animator*>::const_iterator ci = bub.begin(); ci!=bub.end(); ++ci){	
			if( ( (BubWalkingAnimator*) *ci )->GetSprite()->IsBub() == bubId ){								
				return CheckDxDirectionWalking((BubWalkingAnimator*)*ci, false); 
			}																				
		}
	}
	if(!(bub = AnimatorHolder::GetAnimators(bubStandAnimator_t)).empty()){
		for(std::vector<Animator*>::const_iterator ci = bub.begin(); ci!=bub.end(); ++ci){	
			if( ( (BubStandAnimator*) *ci )->GetSprite()->IsBub() == bubId ){								
				return CheckDxDirectionStand((BubStandAnimator*)*ci, false);
			}																				
		}
	}
	if(!(bub = AnimatorHolder::GetAnimators(bubJumpAnimator_t)).empty()){
		for(std::vector<Animator*>::const_iterator ci = bub.begin(); ci!=bub.end(); ++ci){	
			if( ( (BubJumpAnimator*) *ci )->GetSprite()->IsBub() == bubId ){								
				BubJumpAnimator *bja=(BubJumpAnimator *)*ci;
				if(bubId)
					BubbleLogic::GetBubProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(2,0):
													   bja->GetSprite()->Move(1,0);
				else
					BubbleLogic::GetBobProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(2,0):
													   bja->GetSprite()->Move(1,0);
				bja->GetSprite()->SetGoesLeft(false);
				return true;
			}																				
		}
	}
	if(!(bub = AnimatorHolder::GetAnimators(bubJumpOpenMouthAnimator_t)).empty()){
		for(std::vector<Animator*>::const_iterator ci = bub.begin(); ci!=bub.end(); ++ci){	
			if( ( (BubJumpOpenMouthAnimator*) *ci )->GetSprite()->IsBub() == bubId ){								
				BubJumpOpenMouthAnimator *bja=(BubJumpOpenMouthAnimator *)*ci;
				if(bubId)
					BubbleLogic::GetBubProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(2,0):
													   bja->GetSprite()->Move(1,0);
				else
					BubbleLogic::GetBobProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(2,0):
													   bja->GetSprite()->Move(1,0);
				bja->GetSprite()->SetGoesLeft(false);
				return true;
			}																				
		}
	}
	if(!(bub = AnimatorHolder::GetAnimators(bubFallingAnimator_t)).empty()){
		for(std::vector<Animator*>::const_iterator ci = bub.begin(); ci!=bub.end(); ++ci){	
			if( ( (BubFallingAnimator*) *ci )->GetSprite()->IsBub() == bubId ){								
				BubFallingAnimator *bja=(BubFallingAnimator *)*ci;
				if(bubId)
					BubbleLogic::GetBubProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(2,0):
													   bja->GetSprite()->Move(1,0);
				else
					BubbleLogic::GetBobProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(2,0):
													   bja->GetSprite()->Move(1,0);
				bja->GetSprite()->SetGoesLeft(false);
				return true;
			}																				
		}
	}
	return false;
}



static bool _OnKeySpace(bool bubId){
	bool retVal = true;
	std::vector<Animator*> bub;
	bool hasYellowSwt = false;
	static timestamp_t bubOldTime = -1;
	static timestamp_t bobOldTime = -1;
	timestamp_t nowTime = GetGameTime();

	if (bubId) hasYellowSwt = BubbleLogic::GetBubProfile()->GetYellowSwt();
	else hasYellowSwt = BubbleLogic::GetBobProfile()->GetYellowSwt();
	std::cout << "Yellow Sweet :    " << hasYellowSwt << "\n";
	if ( nowTime > (bubId ? bubOldTime : bobOldTime) + (!hasYellowSwt ? BLAST_DELAY : BLAST_QUICK_DELAY) ){
		bubId ? bubOldTime = nowTime : bobOldTime = nowTime;

		if(!(bub = AnimatorHolder::GetAnimators(bubWalkAnimator_t)).empty()){
			for(std::vector<Animator*>::const_iterator ci = bub.begin(); ci!=bub.end(); ++ci){	
				if( ( (BubWalkingAnimator*) *ci )->GetSprite()->IsBub() == bubId ){		

					( (BubWalkingAnimator*) *ci )->OnOpenMouth();									
					return true;																
				}																				
			}			
		}
		if(!(bub = AnimatorHolder::GetAnimators(bubStandAnimator_t)).empty()){
			for(std::vector<Animator*>::const_iterator ci = bub.begin(); ci!=bub.end(); ++ci){	
				if( ( (BubStandAnimator*) *ci )->GetSprite()->IsBub() == bubId ){					
					( (BubStandAnimator*) *ci )->OnOpenMouth();									
					return true;																
				}																				
			}	
		}
		if(!(bub = AnimatorHolder::GetAnimators(bubFallingAnimator_t)).empty()){
			for(std::vector<Animator*>::const_iterator ci = bub.begin(); ci!=bub.end(); ++ci){	
				if( ( (BubFallingAnimator*) *ci )->GetSprite()->IsBub() == bubId ){	


					( (BubFallingAnimator*) *ci )->OnOpenMouth();									
					return true;																
				}																				
			}	
		}
		if(!(bub = AnimatorHolder::GetAnimators(bubJumpAnimator_t)).empty()){
			for(std::vector<Animator*>::const_iterator ci = bub.begin(); ci!=bub.end(); ++ci){	
				if( ( (BubJumpAnimator*) *ci )->GetSprite()->IsBub() == bubId ){					
					( (BubJumpAnimator*) *ci )->OnOpenMouth();									
					return true;																
				}																				
			}
		}
	
	}
	return false;
}


/////////////////////////interface functions

bool InputManageHandling::OnBubKeyUp(){
	return _OnKeyUp(true);
}
bool InputManageHandling::OnBubKeyLeft(){
	return _OnKeyLeft(true);
}
bool InputManageHandling::OnBubKeyRight(){
	return _OnKeyRight(true);
}
bool InputManageHandling::OnBubKeySpace(){
	return _OnKeySpace(true);
}
bool InputManageHandling::OnBobKeyUp(){
	return _OnKeyUp(false);
}
bool InputManageHandling::OnBobKeyLeft(){
	return _OnKeyLeft(false);
}
bool InputManageHandling::OnBobKeyRight(){
	return _OnKeyRight(false);
}
bool InputManageHandling::OnBobKeySpace(){
	return _OnKeySpace(false);
}

///////////////////////////////////////////////

bool InputManageHandling::OnKeyUp(){
	std::vector<Animator*> bub;
	static timestamp_t oldTime = -1;
	
	timestamp_t nowTime;
	if( (nowTime = GetCurrTime())>oldTime+START_MENU_SELECTOR_DELAY ){
		oldTime = nowTime;
		if(!(bub = AnimatorHolder::GetAnimators(startScreenSelectorAnimator_t)).empty()){
			oldTime = nowTime;
			StartScreenSelectorAnimator* selector = (StartScreenSelectorAnimator*) bub.front();
			selector->GoUp();
			return true;
		}else
		if(!(bub = AnimatorHolder::GetAnimators(optionsScreenSelectorAnimator_t)).empty()){
			oldTime = nowTime;
			OptionsScreenSelectorAnimator* selector = (OptionsScreenSelectorAnimator*) bub.front();
			selector->GoUp();
			return true;
		}
	}
	return false;
}

bool InputManageHandling::OnKeyDown(){
	std::vector<Animator*> bub;
	static timestamp_t oldTime = -1;
	
	if(!(bub = AnimatorHolder::GetAnimators(startScreenSelectorAnimator_t)).empty()){
		timestamp_t nowTime;
		if( (nowTime = GetCurrTime())>oldTime+START_MENU_SELECTOR_DELAY ){
			oldTime = nowTime;
			StartScreenSelectorAnimator* selector = (StartScreenSelectorAnimator*) bub.front();
			selector->GoDown();
			return true;
		}
	}else
	if(!(bub = AnimatorHolder::GetAnimators(optionsScreenSelectorAnimator_t)).empty()){
		timestamp_t nowTime;
		if( (nowTime = GetCurrTime())>oldTime+START_MENU_SELECTOR_DELAY ){
			oldTime = nowTime;
			OptionsScreenSelectorAnimator* selector = (OptionsScreenSelectorAnimator*) bub.front();
			selector->GoDown();
			return true;
		}
	}
	return true;
}

bool InputManageHandling::OnKeySpace(void){
	bool retVal = true;
	std::vector<Animator*> bub;

	static timestamp_t oldTime = -1;

	timestamp_t nowTime;
	if( (nowTime = GetCurrTime())>oldTime+START_MENU_SELECTOR_DELAY ){
		oldTime = nowTime;

		if(!(bub = AnimatorHolder::GetAnimators(startScreenSelectorAnimator_t)).empty()){
			return ( (StartScreenSelectorAnimator*) bub.front() )->PressEnter();
		}else	
		if(!(bub = AnimatorHolder::GetAnimators(optionsScreenSelectorAnimator_t)).empty()){
			( (OptionsScreenSelectorAnimator*) bub.front() )->PressEnter();
		}
	}
	return true;
}


bool InputManageHandling::OnKeySelect(){
	if(BubbleLogic::GetBobProfile()->GetScore()==-1){
		BubbleLogic::GetBobProfile()->SetScore(0);
		Sprite* sprite = new Sprite(BubbleLogic::GetBobProfile()->GetStartX(),BubbleLogic::GetBobProfile()->GetStartY(),
									BubbleLogic::GetBobProfile()->GetStartGravity(),AnimationFilmHolder::GetFilm("BubWalk"),
									Terrain::GetActionLayer(), BubbleLogic::GetBobProfile()->GetStartDirection());	
		MovingAnimation* anim = (MovingAnimation*) AnimationsParser::GetAnimation("BubStand");															
		BubStandAnimator* animr = new BubStandAnimator();
		sprite->SetIsBub(false);
		animr->RegistCollitions(sprite);

		START_ANIMATOR( animr, sprite, anim, GetGameTime() );
	}
	return true;
}

bool InputManageHandling::OnKeyP(void){
	static timestamp_t oldTime = -1;

	timestamp_t nowTime;
	if( (nowTime = GetCurrTime())>oldTime + PAUSE_DELAY ){
		oldTime = nowTime;

		if ( !BubbleLogic::IsGamePaused() ){
			BubbleLogic::SetTimeBeforePause( GetCurrTime() );
			BubbleLogic::SetGamePaused(true);
		}
		else{
			AnimatorHolder::TimeShiftAnimators(GetCurrTime() - BubbleLogic::GetTimeBeforePause() );
			BubbleLogic::SetTimeBeforePause( 0);
			BubbleLogic::SetGamePaused(false);
		}
	}
	return true;
}