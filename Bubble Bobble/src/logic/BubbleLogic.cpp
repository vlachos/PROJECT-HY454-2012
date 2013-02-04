#include "BubbleLogic.h"
#include "MemoryManage.h"

	void BubbleLogic::SingletonCreate(void){

		startingLifes = 5;
		emptyBubblePoints = 10;
		powerUpPoints = 100;
		zenChanBubblePoints = 800;
		mightaBubblePoints = 1000;
		bananaPoints = 500;
		orangePoints = 1000;
		peachPoints = 2000;
		waterMelonPoints = 3000;
		blueDiamondPoints = 5000;

		enemiesForBanana = 1;
		enemiesForOrange = 2;
		enemiesForPeach = 3;
		enemiesForWaterMelon = 4;

		crossStageForRedShoes = 2;
		jumpsForYellowSwt = 5;
		ponedBubblesForBlueSwt = 5;
		blustedBubblesForPurpleSwt = 5;

		baronSecToRaiseMS = 5;
		baronDecrDelay = 10;

		bub = DNEWCLASS(BubProfile, (startingLifes) );
		bob = DNEWCLASS(BubProfile, (startingLifes) );
	}

	BubProfile* BubbleLogic::GetBubProfile(void) { return bub; }
	BubProfile* BubbleLogic::GetBobProfile(void) { return bob; }

	Lifes BubbleLogic::GetStartingLifes(void) { return startingLifes; }
	Points BubbleLogic::GetEmptyBubblePoints(void) { return emptyBubblePoints; }
	Points BubbleLogic::GetPowerUpPoints(void) { return powerUpPoints; }
	Points BubbleLogic::GetZenChanBubblePoints(void) { return zenChanBubblePoints; }
	Points BubbleLogic::GetMightaBubblePoints(void) { return mightaBubblePoints; }
	Points BubbleLogic::GetBananaPoints(void) { return bananaPoints; }
	Points BubbleLogic::GetOrangePoints(void) { return orangePoints; }
	Points BubbleLogic::GetPeachPoints(void) { return peachPoints; }
	Points BubbleLogic::GetWaterMelonPoints(void) { return waterMelonPoints; }
	Points BubbleLogic::GetBlueDiamondPoints(void) { return blueDiamondPoints; }

	unsigned int BubbleLogic::GetEnemiesForBanana(void) { return enemiesForBanana; }
	unsigned int BubbleLogic::GetEnemiesForOrange(void) { return enemiesForOrange; }
	unsigned int BubbleLogic::GetEnemiesForPeach(void) { return enemiesForPeach; }
	unsigned int BubbleLogic::GetEnemiesForWaterMelon(void) { return enemiesForWaterMelon; }

	unsigned int BubbleLogic::GetCrossStageForRedShoes(void) { return crossStageForRedShoes; }
	unsigned int BubbleLogic::GetJumpsForYellowSwt(void) { return jumpsForYellowSwt; }
	unsigned int BubbleLogic::GetPonedBubblesForBlueSwt(void) { return ponedBubblesForBlueSwt; }
	unsigned int BubbleLogic::GetBlustedBubblesForPurpleSwt(void) { return blustedBubblesForPurpleSwt; }

	double BubbleLogic::GetBaronSecToRaiseMS(void) { return baronSecToRaiseMS; }
	double BubbleLogic::GetBaronDecrDelay(void) { return baronDecrDelay; }

	Points GetPointsOfPoning(unsigned int enemiesPoned){
		return enemiesPoned;
	}

	void BubbleLogic::SingletonCleanUp(void){
		DDELETE( bub);
		DDELETE( bob);
	}