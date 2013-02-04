#include "BubProfile.h"
#include "MemoryManage.h"

	///////// constructors
	BubProfile::BubProfile(Points aScore, Lifes lifes, bool redShoes, bool yellowSw, bool blueSw, bool purpleSw){
		score = aScore;
		lifes = lifes;
		hasRedShoes = redShoes;
		eatenYellowSweet = yellowSw;
		eatenBlueSweet = blueSw;
		eatenPurpleSweet = purpleSw;
	}
	BubProfile::BubProfile(Lifes startLifes){
		score = -1;
		lifes = startLifes;
		hasRedShoes = false;
		eatenYellowSweet = false;
		eatenBlueSweet = false;
		eatenPurpleSweet = false;
	}
	BubProfile::BubProfile(){
		score = -1;
		lifes = DFLT_STARTING_LIFES;
		hasRedShoes = false;
		eatenYellowSweet = false;
		eatenBlueSweet = false;
		eatenPurpleSweet = false;
	}
	///////// destructor
	BubProfile::~BubProfile(){
		score = -1;
		lifes = 0;
		hasRedShoes = false;
		eatenYellowSweet = false;
		eatenBlueSweet = false;
		eatenPurpleSweet = false;
	}

	BubProfile* BubProfile::Clone(BubProfile* aProfile){
		return DNEWCLASS(BubProfile, (	aProfile->GetScore(), aProfile->GetLifes(),
										aProfile->GetRedShoes(), aProfile->GetYellowSwt(),
										aProfile->GetBlueSwt(), aProfile->GetPurpleSwt()  ));
	}

	///////// score
	void BubProfile::IncrScore(Points addedPoints) {
		DASSERT(addedPoints > 0);
		score += addedPoints;
	}
	void BubProfile::SetScore(Points newScore) { score = newScore; }
	Points BubProfile::GetScore(void) { return score; }

	///////// lifes
	void BubProfile::IncrLifes(void) { ++lifes; }
	void BubProfile::DecrLifes(void) { --lifes; }
	Lifes BubProfile::GetLifes(void) { return lifes; }

	//////// power ups
	void BubProfile::SetRedShoes(bool activate) { hasRedShoes = activate; }
	bool BubProfile::GetRedShoes(void) { return hasRedShoes; }

	void BubProfile::SetYellowSwt(bool activate) { eatenYellowSweet = activate; }
	bool BubProfile::GetYellowSwt(void) { return eatenYellowSweet; }

	void BubProfile::SetBlueSwt(bool activate) { eatenBlueSweet = activate; }
	bool BubProfile::GetBlueSwt(void) { return eatenBlueSweet; }

	void BubProfile::SetPurpleSwt(bool activate) { eatenPurpleSweet = activate; }
	bool BubProfile::GetPurpleSwt(void) { return eatenPurpleSweet; }