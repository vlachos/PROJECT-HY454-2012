#ifndef LETTERSPRITE_H
#define LETTERSPRITE_H

#include "Sprite.h"

class LetterSprite : public Sprite{
	public:
		LetterSprite(int _x, int _y, bool _gravityAddicted, const AnimationFilm * film, const TileLayer * _tileLayer, bool goesLeft);

		void Display(Bitmap dest);
};

#endif