#ifndef BUBBLELOGIC_H
#define BUBBLELOGIC_H

#include "BubProfile.h"

class BubbleLogic {

	public:
		void SingletonCreate(void);

	private:
		BubProfile* bub;
		BubProfile* bob;

		Lifes startingLifes;
		Points emptyBubblePoints;
		Points zenChanBubblePoints;
		Points mightaBubblePoints;
		Points bananaPoints;
		Points orangePoints;
		Points peachPoints;
		Points waterMelonPoints;
		Points blueDiamondPoints;
		Points powerUpPoints;

		unsigned int enemiesForBanana;
		unsigned int enemiesForOrange;
		unsigned int enemiesForPeach;
		unsigned int enemiesForWaterMelon;

		unsigned int crossStageForRedShoes;
		unsigned int jumpsForYellowSwt;
		unsigned int ponedBubblesForBlueSwt;
		unsigned int blustedBubblesForPurpleSwt;

		double baronSecToRaiseMS;
		double baronDecrDelay;

	public:
		BubProfile* GetBubProfile(void);
		BubProfile* GetBobProfile(void);

		Lifes GetStartingLifes(void);
		Points GetEmptyBubblePoints(void);
		Points GetZenChanBubblePoints(void);
		Points GetMightaBubblePoints(void);
		Points GetBananaPoints(void);
		Points GetOrangePoints(void);
		Points GetPeachPoints(void);
		Points GetWaterMelonPoints(void);
		Points GetBlueDiamondPoints(void);
		Points GetPowerUpPoints(void);

		unsigned int GetEnemiesForBanana(void);
		unsigned int GetEnemiesForOrange(void);
		unsigned int GetEnemiesForPeach(void);
		unsigned int GetEnemiesForWaterMelon(void);

		unsigned int GetCrossStageForRedShoes(void);
		unsigned int GetJumpsForYellowSwt(void);
		unsigned int GetPonedBubblesForBlueSwt(void);
		unsigned int GetBlustedBubblesForPurpleSwt(void);

		double GetBaronSecToRaiseMS(void);
		double GetBaronDecrDelay(void);

	public:
		Points GetPointsOfPoning(unsigned int enemiesPoned);

	public:
		void SingletonCleanUp(void);

};

#endif