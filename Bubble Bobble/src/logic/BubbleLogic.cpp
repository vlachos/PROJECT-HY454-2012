#include "BubbleLogic.h"
#include "MemoryManage.h"
#include <math.h>

typedef std::pair<unsigned int, std::string> fruitPair;

	BubProfile* BubbleLogic::bub;
	BubProfile* BubbleLogic::bob;

	Points BubbleLogic::highScore;

	Lifes BubbleLogic::startingLifes;

	double BubbleLogic::baronSecToRaiseMS;
	double BubbleLogic::baronDecrDelay;

	Points BubbleLogic::emptyBubblePoints;
	Points BubbleLogic::zenChanBubblePoints;
	Points BubbleLogic::mightaBubblePoints;
	Points BubbleLogic::bananaPoints;
	Points BubbleLogic::orangePoints;
	Points BubbleLogic::peachPoints;
	Points BubbleLogic::waterMelonPoints;
	Points BubbleLogic::blueDiamondPoints;
	Points BubbleLogic::powerUpPoints;

	unsigned int BubbleLogic::enemiesForBanana;
	unsigned int BubbleLogic::enemiesForOrange;
	unsigned int BubbleLogic::enemiesForPeach;
	unsigned int BubbleLogic::enemiesForWaterMelon;

	unsigned int BubbleLogic::crossStageForRedShoes;
	unsigned int BubbleLogic::jumpsForYellowSwt;
	unsigned int BubbleLogic::ponedBubblesForBlueSwt;
	unsigned int BubbleLogic::blustedBubblesForPurpleSwt;

	std::vector<Coordinates> BubbleLogic::powerUpPosXY;


	void BubbleLogic::SingletonCreate(void){

		highScore = 0;
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

		powerUpPosXY.push_back( std::make_pair(100,111) );
		powerUpPosXY.push_back( std::make_pair(210,191) );
		powerUpPosXY.push_back( std::make_pair(100,271) );
		powerUpPosXY.push_back( std::make_pair(210,431) );
	}


	BubProfile* BubbleLogic::GetBubProfile(void) { return bub; }
	BubProfile* BubbleLogic::GetBobProfile(void) { return bob; }

	void BubbleLogic::SetHighScore(Points newHighScore) { highScore = newHighScore; }
	Points BubbleLogic::GetHighScore(void) { return highScore; }

	void BubbleLogic::SetBubScore(Points newScore) {
		bub->SetScore(newScore);
		if (bub->GetScore() > highScore)
			highScore = bub->GetScore();
	}
	void BubbleLogic::IncrBubScore(Points somePoints) {
		bub->IncrScore(somePoints);
		if (bub->GetScore() > highScore)
			highScore = bub->GetScore();
	}

	void BubbleLogic::SetBobScore(Points newScore) {
		bob->SetScore(newScore);
		if (bob->GetScore() > highScore)
			highScore = bob->GetScore();
	}
	void BubbleLogic::IncrBobScore(Points somePoints) {
		bob->IncrScore(somePoints);
		if (bob->GetScore() > highScore)
			highScore = bob->GetScore();
	}

	Lifes BubbleLogic::GetStartingLifes(void) { return startingLifes; }

	double BubbleLogic::GetBaronSecToRaiseMS(void) { return baronSecToRaiseMS; }
	double BubbleLogic::GetBaronDecrDelay(void) { return baronDecrDelay; }

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
	std::string BubbleLogic::GetFruitType(unsigned int enemiesTerminated){

		if (enemiesTerminated <= enemiesForBanana)		return "Banana";
		else if (enemiesTerminated <= enemiesForOrange) return "Orange";
		else if (enemiesTerminated <= enemiesForPeach)	return "Peach";
		else											return "WaterMelon";
	}

	unsigned int BubbleLogic::GetCrossStageForRedShoes(void) { return crossStageForRedShoes; }
	unsigned int BubbleLogic::GetJumpsForYellowSwt(void) { return jumpsForYellowSwt; }
	unsigned int BubbleLogic::GetPonedBubblesForBlueSwt(void) { return ponedBubblesForBlueSwt; }
	unsigned int BubbleLogic::GetBlustedBubblesForPurpleSwt(void) { return blustedBubblesForPurpleSwt; }

	Coordinates BubbleLogic::GetPowerUpPosXY(unsigned int ith){
		DASSERT(ith < powerUpPosXY.size());
		return powerUpPosXY[ith];
	}

	Points GetPointsOfPoning(unsigned int enemiesPoned){
		return std::pow((double)2, (double)enemiesPoned-1 ) * 1000;
	}

	void BubbleLogic::SingletonCleanUp(void){
		DDELETE( bub);
		DDELETE( bob);
	}