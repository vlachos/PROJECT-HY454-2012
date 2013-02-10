#include "BubbleLogic.h"

#include <math.h>
#include <ctime>

#include "SpritesAttributeParser.h"
#include "StageStartingAttributesParser.h"
#include "MemoryManage.h"

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

	std::vector<StartingAttributes_t> BubbleLogic::powerUpPosXY;
	std::vector<StartingAttributes_t> BubbleLogic::zenChanPosXY;
	std::vector<StartingAttributes_t> BubbleLogic::mightaPosXY;

	///////////// INITIALIZE
	void BubbleLogic::SingletonCreate(void){
		int stageLevel = 1;

		SpritesAttributeParser::SingletonCreate("..\\data\\bitmaps\\sprites\\info\\sprites_attributes_data.xml");

		highScore = 0;
		startingLifes = SpritesAttributeParser::GetAttribute("BubStartingLifes");
		emptyBubblePoints = SpritesAttributeParser::GetAttribute("PointsEmptyBubble");
		powerUpPoints = SpritesAttributeParser::GetAttribute("PointsPowerUp");
		zenChanBubblePoints = SpritesAttributeParser::GetAttribute("PointsZenChanBubble");
		mightaBubblePoints = SpritesAttributeParser::GetAttribute("PointsMightaBubble");
		bananaPoints = SpritesAttributeParser::GetAttribute("PointsBanana");
		orangePoints = SpritesAttributeParser::GetAttribute("PointsOrange");
		peachPoints = SpritesAttributeParser::GetAttribute("PointsPeach");
		waterMelonPoints = SpritesAttributeParser::GetAttribute("PointsWaterMelon");
		blueDiamondPoints = SpritesAttributeParser::GetAttribute("PointsBlueDiamond");

		enemiesForBanana = SpritesAttributeParser::GetAttribute("BananaConditionEnemiesToDefeat");
		enemiesForOrange = SpritesAttributeParser::GetAttribute("OrangeConditionEnemiesToDefeat");
		enemiesForPeach = SpritesAttributeParser::GetAttribute("PeachConditionEnemiesToDefeat");
		enemiesForWaterMelon = SpritesAttributeParser::GetAttribute("WaterMelonConditionEnemiesToDefeat");

		crossStageForRedShoes = SpritesAttributeParser::GetAttribute("RedShoeConditionTimesToCrossTheStage");
		jumpsForYellowSwt = SpritesAttributeParser::GetAttribute("YellowSweetConditionJumpsNeeded");
		ponedBubblesForBlueSwt = SpritesAttributeParser::GetAttribute("BlueSweetConditionPonedBubblesNeeded");
		blustedBubblesForPurpleSwt = SpritesAttributeParser::GetAttribute("PurpleSweetConditionBlustedBubblesNeeded");

		baronSecToRaiseMS = 5;
		baronDecrDelay = 10;

		SpritesAttributeParser::SingletonDestroy();
	
		StageStartingAttributesParser::SingletonCreate("..\\data\\bitmaps\\sprites\\info\\stages_starting_data.xml");
		
		bub = DNEWCLASS(BubProfile, ( startingLifes, StageStartingAttributesParser::GetBubStartingAttribute(stageLevel) ) );
		bob = DNEWCLASS(BubProfile, ( startingLifes, StageStartingAttributesParser::GetBobStartingAttribute(stageLevel) ) );

		std::list<StartingAttributes_t> StartingAttributes = StageStartingAttributesParser::GetPowerUpStartingAttribute(stageLevel);
		for(std::list<StartingAttributes_t>::const_iterator ci = StartingAttributes.begin(); ci!=StartingAttributes.end(); ++ci){
			powerUpPosXY.push_back( (*ci) );
		}

		StartingAttributes = StageStartingAttributesParser::GetZenChanStartingAttribute(stageLevel);
		for(std::list<StartingAttributes_t>::const_iterator ci = StartingAttributes.begin(); ci!=StartingAttributes.end(); ++ci){
			zenChanPosXY.push_back( (*ci) );
		}

		StartingAttributes = StageStartingAttributesParser::GetMightaStartingAttribute(stageLevel);
		for(std::list<StartingAttributes_t>::const_iterator ci = StartingAttributes.begin(); ci!=StartingAttributes.end(); ++ci){
			mightaPosXY.push_back( (*ci) );
		}
		
		StageStartingAttributesParser::SingletonDestroy();

		srand((unsigned)time(0));

		
	}

	///////////// BUBBLUN
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
	void BubbleLogic::BubRedShoesAcquired(void) {
		BubbleLogic::IncrBubScore(powerUpPoints);
		bub->SetRedShoes(true);
	}
	void BubbleLogic::BubYellowSwtAcquired(void) {
		BubbleLogic::IncrBubScore(powerUpPoints);
		bub->SetYellowSwt(true);
	}
	void BubbleLogic::BubBlueSwtAcquired(void) {
		BubbleLogic::IncrBubScore(powerUpPoints);
		bub->SetBlueSwt(true);
	}
	void BubbleLogic::BubPurpleSwtAcquired(void) {
		BubbleLogic::IncrBubScore(powerUpPoints);
		bub->SetPurpleSwt(true);
	}
	void BubbleLogic::BubBananaAcquired(void) { IncrBubScore(bananaPoints); }
	void BubbleLogic::BubOrangeAcquired(void) { IncrBubScore(orangePoints); }
	void BubbleLogic::BubPeachAcquired(void) { IncrBubScore(peachPoints); }
	void BubbleLogic::BubWaterMelonAcquired(void) { IncrBubScore(waterMelonPoints); }
	void BubbleLogic::BubBlueDiamondAcquired(void) { IncrBubScore(blueDiamondPoints); }

	void BubbleLogic::BubPonEmptyBubble(void) { IncrBubScore(emptyBubblePoints); }
	void BubbleLogic::BubPonZenChanBubble(void) {
		bub->IncrEnemiesKilledOnPon();
		IncrBubScore(zenChanBubblePoints);
	}
	void BubbleLogic::BubPonMightaBubble(void) {
		bub->IncrEnemiesKilledOnPon();
		IncrBubScore(mightaBubblePoints);
	}


	///////////// BOBBLUN
	void BubbleLogic::SetBobScore(Points newScore) {
		bob->SetScore(newScore);
		if (bob->GetScore() > highScore) highScore = bob->GetScore();
	}

	void BubbleLogic::IncrBobScore(Points somePoints) {
		bob->IncrScore(somePoints);
		if (bob->GetScore() > highScore)
			highScore = bob->GetScore();
	}

	void BubbleLogic::BobRedShoesAcquired(void) {
		BubbleLogic::IncrBobScore(powerUpPoints);
		bob->SetRedShoes(true);
	}
	void BubbleLogic::BobYellowSwtAcquired(void) {
		BubbleLogic::IncrBobScore(powerUpPoints);
		bob->SetYellowSwt(true);
	}
	void BubbleLogic::BobBlueSwtAcquired(void) {
		BubbleLogic::IncrBobScore(powerUpPoints);
		bob->SetBlueSwt(true);
	}
	void BubbleLogic::BobPurpleSwtAcquired(void) {
		BubbleLogic::IncrBobScore(powerUpPoints);
		bob->SetPurpleSwt(true);
	}
	void BubbleLogic::BobBananaAcquired(void) {	IncrBobScore(bananaPoints); }
	void BubbleLogic::BobOrangeAcquired(void) {	IncrBobScore(orangePoints); }
	void BubbleLogic::BobPeachAcquired(void) { IncrBobScore(peachPoints); }
	void BubbleLogic::BobWaterMelonAcquired(void) { IncrBobScore(waterMelonPoints); }
	void BubbleLogic::BobBlueDiamondAcquired(void) { IncrBobScore(blueDiamondPoints); }

	void BubbleLogic::BobPonEmptyBubble(void) { IncrBobScore(emptyBubblePoints); }
	void BubbleLogic::BobPonZenChanBubble(void) {
		bob->IncrEnemiesKilledOnPon();
		IncrBobScore(zenChanBubblePoints);
	}
	void BubbleLogic::BobPonMightaBubble(void) {
		bob->IncrEnemiesKilledOnPon();
		IncrBobScore(mightaBubblePoints);
	}

	///////////// GENERAL
	Points BubbleLogic::GetPointsOfPoning(unsigned int enemiesPoned){
		return (Points) std::pow((double)2, (double)enemiesPoned-1 ) * 1000;
	}
	Points BubbleLogic::GetPowerUpPoints(void) { return powerUpPoints; }
	Points BubbleLogic::GetBananaPoints(void) { return bananaPoints; }
	Points BubbleLogic::GetOrangePoints(void) { return orangePoints; }
	Points BubbleLogic::GetPeachPoints(void) { return peachPoints; }
	Points BubbleLogic::GetWaterMelonPoints(void) { return waterMelonPoints; }
	Points BubbleLogic::GetBlueDiamondPoints(void) { return blueDiamondPoints; }


	unsigned int BubbleLogic::GetFruitType(){

		unsigned int enemies = bob->GetEnemiesKilledOnPon();

		if (enemies == 0)
			return 5;
		else if ( enemies <= enemiesForBanana)
			return 1;
		else if (enemies <= enemiesForOrange)
			return 2;
		else if (enemies <= enemiesForPeach)
			return 3;
		else if(enemies <= enemiesForWaterMelon)
			return 4;

		return -1;
	}

	///////////// Stating Sprite Attributes
	Coordinates BubbleLogic::GetPowerUpPosXY(void){
		return powerUpPosXY[rand()%powerUpPosXY.size()].first;
	}

	unsigned int BubbleLogic::GetZenChanNum(void) { return zenChanPosXY.size(); }
	Coordinates BubbleLogic::GetZenChanPosXY(unsigned int ith){
		DASSERT(ith < zenChanPosXY.size());
		return zenChanPosXY[ith].first;
	}
	bool BubbleLogic::GetZenChanDirection(unsigned int ith){
		DASSERT(ith < zenChanPosXY.size());
		return zenChanPosXY[ith].second.second;
	}
	bool BubbleLogic::GetZenChanGravity(unsigned int ith){
		DASSERT(ith < zenChanPosXY.size());
		return zenChanPosXY[ith].second.first;
	}

	unsigned int BubbleLogic::GetMightaNum(void) { return mightaPosXY.size(); }
	Coordinates BubbleLogic::GetMightaPosXY(unsigned int ith){
		DASSERT(ith < mightaPosXY.size());
		return mightaPosXY[ith].first;
	}
	bool BubbleLogic::GetMightaDirection(unsigned int ith){
		DASSERT(ith < mightaPosXY.size());
		return mightaPosXY[ith].second.second;
	}
	bool BubbleLogic::GetMightaGravity(unsigned int ith){
		DASSERT(ith < mightaPosXY.size());
		return mightaPosXY[ith].second.first;
	}

	///////////// BARRON VON BLUBA
	double BubbleLogic::GetBaronSecToRaiseMS(void) { return baronSecToRaiseMS; }
	double BubbleLogic::GetBaronDecrDelay(void) { return baronDecrDelay; }

	///////////// CLEANUP
	void BubbleLogic::SingletonCleanUp(void){
		DDELETE( bub);
		DDELETE( bob);
	}