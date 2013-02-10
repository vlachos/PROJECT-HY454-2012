#include "BubProfile.h"
#include "MemoryManage.h"


	///////// constructors
	BubProfile::BubProfile(Lifes startLifes, StartingAttributes_t startAttr){
		score = -1;
		startXY = startAttr.first;
		startGravity = startAttr.second.first;
		startDirection = startAttr.second.second;
		lifes = startLifes;
		enemiesKilledOnPon = 0;
		hasRedShoes = false;
		eatenYellowSweet = false;
		eatenBlueSweet = false;
		eatenPurpleSweet = false;
		timesCrossedStage = 0;
		timesJumped = 0;
		timesBlastedBubble = 0;
		timesPonedBubble = 0;
	}
	BubProfile::BubProfile(){
		score = -1;
		startXY = std::make_pair(0, 0);
		startGravity = true;
		startDirection = true;
		lifes = DFLT_STARTING_LIFES;
		enemiesKilledOnPon = 0;
		hasRedShoes = false;
		eatenYellowSweet = false;
		eatenBlueSweet = false;
		eatenPurpleSweet = false;
		timesCrossedStage = 0;
		timesJumped = 0;
		timesBlastedBubble = 0;
		timesPonedBubble = 0;
	}
	///////// destructor
	BubProfile::~BubProfile(){
		score = -1;
		startGravity = false;
		startDirection = false;
		lifes = 0;
		enemiesKilledOnPon = 0;
		hasRedShoes = false;
		eatenYellowSweet = false;
		eatenBlueSweet = false;
		eatenPurpleSweet = false;
		timesCrossedStage = 0;
		timesJumped = 0;
		timesBlastedBubble = 0;
		timesPonedBubble = 0;
	}

	void BubProfile::InitBlastAnimationMap(void){}

	///////// starting attributes
	int BubProfile::GetStartX(void) { return startXY.first; }
	int BubProfile::GetStartY(void) { return startXY.second; }
	bool BubProfile::GetStartDirection(void) { return startDirection; }
	bool BubProfile::GetStartGravity(void) { return startGravity; }

	///////// score
	void BubProfile::IncrScore(Points addedPoints) {
		DASSERT(addedPoints >= 0);
		score += addedPoints;
	}
	void BubProfile::SetScore(Points newScore) { score = newScore; }
	Points BubProfile::GetScore(void) { return score; }

	///////// lifes
	void BubProfile::IncrLifes(void) { ++lifes; }
	void BubProfile::DecrLifes(void) { --lifes; }
	Lifes BubProfile::GetLifes(void) { return lifes; }

	///////// Enemies poned
	void BubProfile::SetEnemiesKilledOnPon(unsigned int enemies) { enemiesKilledOnPon = enemies; }
	void BubProfile::IncrEnemiesKilledOnPon(void) { ++enemiesKilledOnPon; }
	unsigned int BubProfile::GetEnemiesKilledOnPon(void) { return enemiesKilledOnPon; }

	//////// power ups
	void BubProfile::SetRedShoes(bool activate) { hasRedShoes = activate; }
	bool BubProfile::GetRedShoes(void) { return hasRedShoes; }

	void BubProfile::SetYellowSwt(bool activate) { eatenYellowSweet = activate;	}
	bool BubProfile::GetYellowSwt(void) { return eatenYellowSweet; }

	void BubProfile::SetBlueSwt(bool activate) { eatenBlueSweet = activate;	}
	bool BubProfile::GetBlueSwt(void) { return eatenBlueSweet; }

	void BubProfile::SetPurpleSwt(bool activate) { eatenPurpleSweet = activate;	}
	bool BubProfile::GetPurpleSwt(void) { return eatenPurpleSweet; }

	void BubProfile::IncrTimesCrossedStage(void) { ++timesCrossedStage; }
	unsigned int BubProfile::GetTimesCrossedStage(void) { return timesCrossedStage; }

	void BubProfile::IncrTimesJumped(void) { ++timesJumped; }
	unsigned int BubProfile::GetTimesJumped(void) { return timesJumped; }

	void BubProfile::IncrTimesBlastedABubble(void) { ++timesBlastedBubble; }
	unsigned int BubProfile::GetTimesBlastedBubble(void) { return timesBlastedBubble; }

	void BubProfile::IncrTimesPonedABubble(void) { ++timesPonedBubble; }
	unsigned int BubProfile::GetTimesPonedBubble(void) { return timesPonedBubble; }


	const std::string BubProfile::GetBubbleBlastAnimation(bool goesLeft) {

		if (goesLeft){
			if (!eatenPurpleSweet && !eatenBlueSweet)		return "BubBubbleBlastOffLeft";
			else if (eatenPurpleSweet && !eatenBlueSweet)	return "BubBubbleQuickBlastOffLeft";
			else if (!eatenPurpleSweet && eatenBlueSweet)	return "BubBubblePowerBlastOffLeft";
			else											return "BubBubbleQuickPowerBlastOffLeft";
		}
		else{
			if (!eatenPurpleSweet && !eatenBlueSweet)		return "BubBubbleBlastOffRight";
			else if (eatenPurpleSweet && !eatenBlueSweet)	return "BubBubbleQuickBlastOffRight";
			else if (!eatenPurpleSweet && eatenBlueSweet)	return "BubBubblePowerBlastOffRight";
			else											return "BubBubbleQuickPowerBlastOffRight";
		}
	}

	const std::string BubProfile::GetBubWalkAnimation(bool goesLeft) {

		if (!hasRedShoes && goesLeft )		return std::string("BubWalkLeft");
		else if (!hasRedShoes && !goesLeft )return std::string("BubWalkRight");
		else if (hasRedShoes && goesLeft )	return std::string("BubQuickWalkLeft");
		else if (hasRedShoes && !goesLeft ) return std::string("BubQuickWalkRight");

		return std::string();
	}

	const std::string BubProfile::GetBubOpenMouthWalkAnimation(bool goesLeft) {

		if (!hasRedShoes && goesLeft )		return std::string("BubOpenMouthWalkingLeft");
		else if (!hasRedShoes && !goesLeft )return std::string("BubOpenMouthWalkingRight");
		else if (hasRedShoes && goesLeft )	return std::string("BubOpenMouthQuickWalkingLeft");
		else if (hasRedShoes && !goesLeft ) return std::string("BubOpenMouthQuickWalkingRight");

		return std::string();
	}

	const std::string BubProfile::GetBubJumpStand(void) {
		if (!hasRedShoes)	return "BubJumpStand";
		else				return "BubQuickJumpStand";
	}

	const std::string BubProfile::GetBubJumpWalking(void) {
		if (!hasRedShoes)	return "BubJumpWalking";
		else				return "BubQuickJumpWalking";
	}