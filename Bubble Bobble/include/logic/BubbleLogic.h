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

	private:
		static void IncrBubScore(Points somePoints);
		static void IncrBobScore(Points somePoints);

	public:
		static BubProfile* GetBubProfile(void);
		static BubProfile* GetBobProfile(void);

		static void SetHighScore(Points newHighScore);
		static Points GetHighScore(void);

		static void SetBubScore(Points newScore);
		static void BubRedShoesAcquired(void);
		static void BubYellowSwtAcquired(void);
		static void BubBlueSwtAcquired(void);
		static void BubPurpleSwtAcquired(void);
		static void BubBananaAcquired(void);
		static void BubOrangeAcquired(void);
		static void BubPeachAcquired(void);
		static void BubWaterMelonAcquired(void);
		static void BubBlueDiamondAcquired(void);
		static void BubPonEmptyBubble(void);
		static void BubPonZenChanBubble(void);
		static void BubPonMightaBubble(void);

		static void SetBobScore(Points newScore);
		static void BobRedShoesAcquired(void);
		static void BobYellowSwtAcquired(void);
		static void BobBlueSwtAcquired(void);
		static void BobPurpleSwtAcquired(void);
		static void BobBananaAcquired(void);
		static void BobOrangeAcquired(void);
		static void BobPeachAcquired(void);
		static void BobWaterMelonAcquired(void);
		static void BobBlueDiamondAcquired(void);
		static void BobPonEmptyBubble(void);
		static void BobPonZenChanBubble(void);
		static void BobPonMightaBubble(void);

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

		static double GetBaronSecToRaiseMS(void);
		static double GetBaronDecrDelay(void);

	public:
		static void SingletonCleanUp(void);

};

#endif