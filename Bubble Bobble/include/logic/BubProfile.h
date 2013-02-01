#ifndef BUBPROFILE_H
#define BUBPROFILE_H

typedef unsigned int Lifes;

class BubProfile : public CharacterLogic {

	private:
		Lifes BubLifes;
		bool hasRedShoes;
		bool eatenYellowSweet;
		bool eatenBlueSweet;
		bool eatenPurpleSweet;

	public
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
}

#endif