#include "StageInitializer.h"
#include "BubbleLogic.h"
#include "AnimatorHolder.h"
#include "AnimationsParser.h"
#include "Sprite.h"
#include "Terrain.h"
#include "BubAnimator.h"
#include "MightaAnimator.h"
#include "ZenChanAnimator.h"
#include "BarronVonBlubaAnimator.h"
#include "RiverAnimator.h"
#include "BubblesAnimator.h"
#include "TimerTickAnimator.h"
#include "TickAnimation.h"
#include "GameActionUtilities.h"

	void StageInitializer::InitNextStage(void){
		InitBubblun();
		InitZenChan();
		InitMighta();
		InitTickAnimators();
	}

	void StageInitializer::InitBubblun(void){
		BubbleLogic::SetBubScore(0);
		Sprite* sprite = new Sprite(BubbleLogic::GetBubProfile()->GetStartX(), BubbleLogic::GetBubProfile()->GetStartY(),
									BubbleLogic::GetBubProfile()->GetStartGravity(), AnimationFilmHolder::GetFilm("BubWalk"),
									Terrain::GetActionLayer(), BubbleLogic::GetBubProfile()->GetStartDirection());
		sprite->SetIsBub(true);
		MovingAnimation* anim = (MovingAnimation*) AnimationsParser::GetAnimation("BubStand");
		BubStandAnimator* animr = new BubStandAnimator();
		animr->RegistCollitions(sprite);
		START_ANIMATOR( animr, sprite, anim, GetGameTime() );
	}

	void StageInitializer::InitZenChan(void){
		for (unsigned int i = 0; i < BubbleLogic::GetZenChanNum(); ++i){
			Sprite* sprite = new Sprite(BubbleLogic::GetZenChanPosXY(i).first, BubbleLogic::GetZenChanPosXY(i).second,
										BubbleLogic::GetZenChanGravity(i), AnimationFilmHolder::GetFilm("ZenChanWalk"),
										Terrain::GetActionLayer(), BubbleLogic::GetZenChanDirection(i));

			FrameRangeAnimation* anim = (FrameRangeAnimation*) AnimationsParser::GetAnimation(sprite->GoesLeft()?"ZenChanWalkLeft":"ZenChanWalkRight");
			ZenChanWalkingAnimator* animr = new ZenChanWalkingAnimator();
			sprite->AddStartFallingListener(animr);
			animr->RegistCollitions(sprite);
			START_ANIMATOR( animr, sprite, anim, GetGameTime() );
		}
	}

	void StageInitializer::InitMighta(void){
		for (unsigned int i = 0; i < BubbleLogic::GetMightaNum(); ++i){
			Sprite* sprite = new Sprite(BubbleLogic::GetMightaPosXY(i).first, BubbleLogic::GetZenChanPosXY(i).second,
										BubbleLogic::GetMightaGravity(i), AnimationFilmHolder::GetFilm("MightaWalk"),
										Terrain::GetActionLayer(), BubbleLogic::GetMightaDirection(i));	

			FrameRangeAnimation* anim = (FrameRangeAnimation*) AnimationsParser::GetAnimation(sprite->GoesLeft()?"MightaWalkLeft":"MightaWalkRight");
			MightaWalkingAnimator* animr = new MightaWalkingAnimator();
			sprite->AddStartFallingListener(animr);
			animr->RegistCollitions(sprite);
			START_ANIMATOR( animr, sprite, anim, GetGameTime() );
		}
	}

	void StageInitializer::InitTickAnimators(void){

		TickAnimation *ta = (TickAnimation*) AnimationsParser::GetAnimation("WaterBubblePeriod");
		ta->SetTickAction( RiverAnimatorActions::StartWaterBubble, 0 );
		TimerTickAnimator* ttar = new TimerTickAnimator(ta);
		ttar->SetOnFinish(BubblesAnimatorActions::OnTickTimerFinishCallback, 0);
		START_TIME_ANIMATOR(ttar, GetGameTime());

		TickAnimation *ta2 = (TickAnimation*) AnimationsParser::GetAnimation("HurryUpStart");
		ta2->SetTickAction( BaronVonBlubaAnimatorActions::StartHurryUpAnimator, 0 );
		TimerTickAnimator* ttar2 = new TimerTickAnimator(ta2);
		ttar2->SetOnFinish(BubblesAnimatorActions::OnTickTimerFinishCallback, 0);
		START_TIME_ANIMATOR(ttar2, GetGameTime());
	}

	void StageInitializer::InitScoreBoard(void){
	}
	void StageInitializer::InitBubLifes(void){

	}