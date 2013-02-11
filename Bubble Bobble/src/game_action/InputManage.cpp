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


/////////////////////////static functions

static bool CheckDxDirectionWalking(const std::vector<Animator*>& bub, bool direction){
	BubWalkingAnimator* bubWalk = (BubWalkingAnimator*) bub.front();
	offset_t offset = bubWalk->GetAnimation()->GetDx();
	DASSERT( offset!=0 );
	if( ( direction ? (offset > 0) : (offset < 0) ) ) {
		bubWalk->GetAnimation()->SetDx(-offset);
		bubWalk->GetSprite()->SetGoesLeft(direction);
	}

	return true;
}

static bool CheckDxDirectionStand(const std::vector<Animator*>& bub, bool direction){
	BubStandAnimator* _this = (BubStandAnimator*) bub.front();

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

static bool CheckDyDirectionWalking(const std::vector<Animator*>& bub){
	BubWalkingAnimator* _this = (BubWalkingAnimator*) bub.front();
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

static bool CheckDyDirectionStand(const std::vector<Animator*>& bub){
	BubStandAnimator* _this = (BubStandAnimator*) bub.front();
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


/////////////////////////interface functions


bool InputManageHandling::OnKeyUp(void){
	bool retVal = true;
	std::vector<Animator*> bub;
	static timestamp_t oldTime = -1;
	if(!(bub = AnimatorHolder::GetAnimators(bubWalkAnimator_t)).empty()){
		retVal = CheckDyDirectionWalking(bub);
	}else
	if(!(bub = AnimatorHolder::GetAnimators(bubStandAnimator_t)).empty()){
		BubbleLogic::GetBubProfile()->SetJumpOnMove(false);
		retVal = CheckDyDirectionStand(bub);
	}else
	if(!(bub = AnimatorHolder::GetAnimators(startScreenSelectorAnimator_t)).empty()){
		timestamp_t nowTime;
		if( (nowTime = GetCurrTime())>oldTime+START_MENU_SELECTOR_DELAY ){
			oldTime = nowTime;
			StartScreenSelectorAnimator* selector = (StartScreenSelectorAnimator*) bub.front();
			selector->GoUp();
		}
	}else
	if(!(bub = AnimatorHolder::GetAnimators(optionsScreenSelectorAnimator_t)).empty()){
		timestamp_t nowTime;
		if( (nowTime = GetCurrTime())>oldTime+START_MENU_SELECTOR_DELAY ){
			oldTime = nowTime;
			OptionsScreenSelectorAnimator* selector = (OptionsScreenSelectorAnimator*) bub.front();
			selector->GoUp();
		}
	}
	return retVal;
}

bool InputManageHandling::OnKeyDown(void){
	std::vector<Animator*> bub;
	static timestamp_t oldTime = -1;
	if(!(bub = AnimatorHolder::GetAnimators(startScreenSelectorAnimator_t)).empty()){
		timestamp_t nowTime;
		if( (nowTime = GetCurrTime())>oldTime+START_MENU_SELECTOR_DELAY ){
			oldTime = nowTime;
			StartScreenSelectorAnimator* selector = (StartScreenSelectorAnimator*) bub.front();
			selector->GoDown();
		}
	}else
	if(!(bub = AnimatorHolder::GetAnimators(optionsScreenSelectorAnimator_t)).empty()){
		timestamp_t nowTime;
		if( (nowTime = GetCurrTime())>oldTime+START_MENU_SELECTOR_DELAY ){
			oldTime = nowTime;
			OptionsScreenSelectorAnimator* selector = (OptionsScreenSelectorAnimator*) bub.front();
			selector->GoDown();
		}
	}
	return true;
}

bool InputManageHandling::OnKeyLeft(void){
	bool retVal = true;
	std::vector<Animator*> bub;

	if(!(bub = AnimatorHolder::GetAnimators(bubWalkAnimator_t)).empty()){
		retVal = CheckDxDirectionWalking(bub, true);
	}else
	if(!(bub = AnimatorHolder::GetAnimators(bubStandAnimator_t)).empty()){
		retVal = CheckDxDirectionStand(bub, true);
	}else
	if(!(bub = AnimatorHolder::GetAnimators(bubJumpAnimator_t)).empty()){
		BubJumpAnimator *bja=(BubJumpAnimator *)bub.front();
		BubbleLogic::GetBubProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(-2,0):
													   bja->GetSprite()->Move(-1,0);
		bja->GetSprite()->SetGoesLeft(true);
	}else
	if(!(bub = AnimatorHolder::GetAnimators(bubJumpOpenMouthAnimator_t)).empty()){
		BubJumpOpenMouthAnimator *bja=(BubJumpOpenMouthAnimator *)bub.front();
		BubbleLogic::GetBubProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(-2,0):
													   bja->GetSprite()->Move(-1,0);
		bja->GetSprite()->SetGoesLeft(true);
	}else
	if(!(bub = AnimatorHolder::GetAnimators(bubFallingAnimator_t)).empty()){
		BubFallingAnimator *bja=(BubFallingAnimator *)bub.front();
		BubbleLogic::GetBubProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(-2,0):
													   bja->GetSprite()->Move(-1,0);
		bja->GetSprite()->SetGoesLeft(true);
	}

	return retVal;
}

bool InputManageHandling::OnKeyRight(void){
	bool retVal = true;
	std::vector<Animator*> bub;
		
	if(!(bub = AnimatorHolder::GetAnimators(bubWalkAnimator_t)).empty()){
		retVal = CheckDxDirectionWalking(bub, false);
	}else
	if(!(bub = AnimatorHolder::GetAnimators(bubStandAnimator_t)).empty()){
		retVal = CheckDxDirectionStand(bub, false);
	}else 
	if(!(bub = AnimatorHolder::GetAnimators(bubJumpAnimator_t)).empty()){
		BubJumpAnimator *bja=(BubJumpAnimator *)bub.front();
		BubbleLogic::GetBubProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(2,0):
													   bja->GetSprite()->Move(1,0);
		bja->GetSprite()->SetGoesLeft(false);
	}else
	if(!(bub = AnimatorHolder::GetAnimators(bubJumpOpenMouthAnimator_t)).empty()){
		BubJumpOpenMouthAnimator *bja=(BubJumpOpenMouthAnimator *)bub.front();
		BubbleLogic::GetBubProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(2,0):
													   bja->GetSprite()->Move(1,0);
		bja->GetSprite()->SetGoesLeft(false);
	}else
	if(!(bub = AnimatorHolder::GetAnimators(bubFallingAnimator_t)).empty()){
		BubFallingAnimator *bja=(BubFallingAnimator *)bub.front();
		BubbleLogic::GetBubProfile()->IsJumpOnMove() ? bja->GetSprite()->Move(2,0):
													   bja->GetSprite()->Move(1,0);
		bja->GetSprite()->SetGoesLeft(false);
	}

	return retVal;
}

bool InputManageHandling::OnKeySpace(void){
	bool retVal = true;
	std::vector<Animator*> bub;

	static timestamp_t oldTime = -1;

	timestamp_t nowTime;
	if( (nowTime = GetCurrTime())>oldTime+START_MENU_SELECTOR_DELAY ){
		oldTime = nowTime;
		if(!(bub = AnimatorHolder::GetAnimators(bubWalkAnimator_t)).empty()){
			( (BubWalkingAnimator*) bub.front() )->OnOpenMouth();
		}else	
		if(!(bub = AnimatorHolder::GetAnimators(bubStandAnimator_t)).empty()){
			( (BubStandAnimator*) bub.front() )->OnOpenMouth();
		}else	
		if(!(bub = AnimatorHolder::GetAnimators(bubFallingAnimator_t)).empty()){
			( (BubFallingAnimator*) bub.front() )->OnOpenMouth();
		}else	
		if(!(bub = AnimatorHolder::GetAnimators(bubJumpAnimator_t)).empty()){
			( (BubJumpAnimator*) bub.front() )->OnOpenMouth();
		}else	
		if(!(bub = AnimatorHolder::GetAnimators(startScreenSelectorAnimator_t)).empty()){
			retVal = ( (StartScreenSelectorAnimator*) bub.front() )->PressEnter();
		}else	
		if(!(bub = AnimatorHolder::GetAnimators(optionsScreenSelectorAnimator_t)).empty()){
			retVal = ( (OptionsScreenSelectorAnimator*) bub.front() )->PressEnter();
		}
	}
		
	return retVal;
}


bool InputManageHandling::OnKeySelect(void){

	Sprite* sprite = new Sprite(BubbleLogic::GetBobProfile()->GetStartX(),BubbleLogic::GetBobProfile()->GetStartY(),
								BubbleLogic::GetBobProfile()->GetStartGravity(),AnimationFilmHolder::GetFilm("BubWalk"),
								Terrain::GetActionLayer(), BubbleLogic::GetBobProfile()->GetStartDirection());	
	MovingAnimation* anim = (MovingAnimation*) AnimationsParser::GetAnimation("BubStand");															
	BubStandAnimator* animr = new BubStandAnimator();
	animr->RegistCollitions(sprite);

	START_ANIMATOR( animr, sprite, anim, GetGameTime() );
	return true;
}

bool InputManageHandling::OnKeyP(void){
	if(true){
		
	}
	else{
	
	}
	return true;
}