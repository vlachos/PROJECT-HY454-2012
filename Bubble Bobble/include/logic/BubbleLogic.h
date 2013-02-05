#ifndef BUBBLELOGIC_H
#define BUBBLELOGIC_H

#include "BubProfile.h"
#include "Metrics.h"
#include <vector>

class BubbleLogic {

	public:
		static void SingletonCreate(void);

	private:
		static Points highScore;

		static BubProfile* bub;
		static BubProfile* bob;
		static Lifes startingLifes;

		static double baronSecToRaiseMS;
		static double baronDecrDelay;

		static Points emptyBubblePoints;
		static Points zenChanBubblePoints;
		static Points mightaBubblePoints;
		static Points bananaPoints;
		static Points orangePoints;
		static Points peachPoints;
		static Points waterMelonPoints;
		static Points blueDiamondPoints;
		static Points powerUpPoints;

		static unsigned int enemiesForBanana;
		static unsigned int enemiesForOrange;
		static unsigned int enemiesForPeach;
		static unsigned int enemiesForWaterMelon;

		static unsigned int crossStageForRedShoes;
		static unsigned int jumpsForYellowSwt;
		static unsigned int ponedBubblesForBlueSwt;
		static unsigned int blustedBubblesForPurpleSwt;

		static std::vector<Coordinates> powerUpPosXY;

	public:
		static BubProfile* GetBubProfile(void);
		static BubProfile* GetBobProfile(void);

		static void SetHighScore(Points newHighScore);
		static Points GetHighScore(void);

		static void SetBubScore(Points newScore);
		static void IncrBubScore(Points somePoints);

		static void SetBobScore(Points newScore);
		static void IncrBobScore(Points somePoints);

		static Lifes GetStartingLifes(void);

		static double GetBaronSecToRaiseMS(void);
		static double GetBaronDecrDelay(void);

		static Points GetEmptyBubblePoints(void);
		static Points GetZenChanBubblePoints(void);
		static Points GetMightaBubblePoints(void);
		static Points GetBananaPoints(void);
		static Points GetOrangePoints(void);
		static Points GetPeachPoints(void);
		static Points GetWaterMelonPoints(void);
		static Points GetBlueDiamondPoints(void);
		static Points GetPowerUpPoints(void);

		static unsigned int GetEnemiesForBanana(void);
		static unsigned int GetEnemiesForOrange(void);
		static unsigned int GetEnemiesForPeach(void);
		static unsigned int GetEnemiesForWaterMelon(void);
		static unsigned int GetFruitType(unsigned int enemiesTerminated);

		static unsigned int GetCrossStageForRedShoes(void);
		static unsigned int GetJumpsForYellowSwt(void);
		static unsigned int GetPonedBubblesForBlueSwt(void);
		static unsigned int GetBlustedBubblesForPurpleSwt(void);

		static Coordinates GetPowerUpPosXY(void);

		static Points GetPointsOfPoning(unsigned int enemiesPoned);

	public:
		static void SingletonCleanUp(void);

};

#endif