#ifndef BUBLIFESSPRITE_H
#define BUBLIFESSPRITE_H

#include "MultiSprite.h"

class BubLifesSprite : public MultiSprite{

	public:
		BubLifesSprite(int _x, int _y, bool _gravityAddicted, const AnimationFilm * film, const TileLayer * _tileLayer, bool goesLeft);
	private:
		bool isBubs;

	public:
		void SetIsBubsLifes(bool b) { isBubs = b; }
		void Display(Bitmap dest);
};

#endif