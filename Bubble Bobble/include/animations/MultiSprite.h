#ifndef MULTISPRITE_H
#define MULTISPRITE_H

#include "Sprite.h"

class MultiSprite : public Sprite{
	public:
		MultiSprite(int _x, int _y, bool _gravityAddicted, const AnimationFilm * film, const TileLayer * _tileLayer, bool goesLeft);

		void Display(Bitmap dest);
};

#endif