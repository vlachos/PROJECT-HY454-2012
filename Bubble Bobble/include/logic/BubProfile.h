#ifndef BUBPROFILE_H
#define BUBPROFILE_H

typedef unsigned int Lifes;
typedef int Points;

#define DFLT_STARTING_LIFES 5

class BubProfile{


	private:
		BubProfile(Points aScore, Lifes lifes, bool redShoes, bool yellowSw, bool blueSw, bool purpleSw);
	public:
		BubProfile(Lifes startLifes);
		BubProfile();
		~BubProfile();

	private:
		Points score;
		Lifes lifes;
		bool hasRedShoes;
		bool eatenYellowSweet;
		bool eatenBlueSweet;
		bool eatenPurpleSweet;

	public:
		BubProfile* Clone(BubProfile* aProfile);

	public:
		void IncrScore(Points addedPoints);
		void SetScore(Points newScore);
		Points GetScore(void);

		void IncrLifes(void);
		void DecrLifes(void);
		Lifes GetLifes(void);

		void SetRedShoes(bool activate);
		bool GetRedShoes(void);

		void SetYellowSwt(bool activate);
		bool GetYellowSwt(void);

		void SetBlueSwt(bool activate);
		bool GetBlueSwt(void);

		void SetPurpleSwt(bool activate);
		bool GetPurpleSwt(void);
};

#endif