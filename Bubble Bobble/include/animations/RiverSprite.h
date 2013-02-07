#ifndef RIVERSPRITE_H
#define RIVERSPRITE_H

#include "Sprite.h"
#include <deque>

#define MAX_RIVER_PARTS 8
#define RIVER_DX_DY 16

typedef std::deque<Sprite*> RiverQueue_t;

class RiverSprite : public Sprite{

	public:
		RiverSprite(int _x, int _y, bool _gravityAddicted, const AnimationFilm * film, const TileLayer * _tileLayer, bool goesLeft);
		~RiverSprite();

	private:
		bool riverGoesLeft;
		RiverQueue_t riverQueue;

	public:
		bool IsRiverDirectionLeft(void);
		unsigned int GetRiverLength(void);
		Sprite* GetRiverItem(unsigned int ith);

	public:
		void RiverRush(bool left);
		void RiverFalling(void);
		void RiverStartFalling(void);
		void RiverStopFalling(void);

	private:
		void RiverStepForward(std::string str);
		void RiverFallAndForward(void);

	public:
		void Move( int _x, int _y );
		void Display(Bitmap dest);
};

#endif