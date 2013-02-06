#ifndef BUBBLELOGIC_H
#define BUBBLELOGIC_H

#include "BubProfile.h"
#include "Metrics.h"
#include <vector>

typedef std::pair<Coordinates, std::pair<bool,bool> > StartingAttributes_t;

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

		static std::vector<StartingAttributes_t> powerUpPosXY;
		static std::vector<StartingAttributes_t> zenChanPosXY;
		static std::vector<StartingAttributes_t> mightaPosXY;

	private:
		static void IncrBubScore(Points somePoints);
		static void IncrBobScore(Points somePoints);

	public:
		static BubProfile* GetBubProfile(void);
		static BubProfile* GetBobProfile(void);

		static void SetHighScore(Points newHighScore);
		static Points GetHighScore(void);

		static void SetBubScore(Points newScore);
		//acquired power up
		static void BubRedShoesAcquired(void);
		static void BubYellowSwtAcquired(void);
		static void BubBlueSwtAcquired(void);
		static void BubPurpleSwtAcquired(void);
		//acquired fruit
		static void BubBananaAcquired(void);
		static void BubOrangeAcquired(void);
		static void BubPeachAcquired(void);
		static void BubWaterMelonAcquired(void);
		static void BubBlueDiamondAcquired(void);
		static void BubPonEmptyBubble(void);
		static void BubPonZenChanBubble(void);
		static void BubPonMightaBubble(void);
		//power up condition
		static bool BubCrossedStage(void);
		static bool BubJumped(void);
		static bool BubPonedBubble(void);
		static bool BubBlastedBubble(void);

		static void SetBobScore(Points newScore);
		//acquired power up
		static void BobRedShoesAcquired(void);
		static void BobYellowSwtAcquired(void);
		static void BobBlueSwtAcquired(void);
		static void BobPurpleSwtAcquired(void);
		//acquired fruit
		static void BobBananaAcquired(void);
		static void BobOrangeAcquired(void);
		static void BobPeachAcquired(void);
		static void BobWaterMelonAcquired(void);
		static void BobBlueDiamondAcquired(void);
		static void BobPonEmptyBubble(void);
		static void BobPonZenChanBubble(void);
		static void BobPonMightaBubble(void);
		//power up condition
		static bool BobCrossedStage(void);
		static bool BobJumped(void);
		static bool BobPonedBubble(void);
		static bool BobBlastedBubble(void);

		static unsigned int GetFruitType(unsigned int enemiesTerminated);

		//starting sprite attributes
		static Coordinates GetPowerUpPosXY(void);

		static unsigned int GetZenChanNum(void);
		static Coordinates GetZenChanPosXY(unsigned int ith);
		static bool GetZenChanDirection(unsigned int ith);
		static bool GetZenChanGravity(unsigned int ith);

		static unsigned int GetMightaNum(void);
		static Coordinates GetMightaPosXY(unsigned int ith);
		static bool GetMightaDirection(unsigned int ith);
		static bool GetMightaGravity(unsigned int ith);

		static Points GetPointsOfPoning(unsigned int enemiesPoned);

		static double GetBaronSecToRaiseMS(void);
		static double GetBaronDecrDelay(void);

	public:
		static void SingletonCleanUp(void);

};

#endif