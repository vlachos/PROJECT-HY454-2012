#ifndef RIVERSPRITE_H
#define RIVERSPRITE_H

#include "Sprite.h"

#define MAX_RIVER_PARTS 8

typedef std::vector<Sprite*> RiverQueue_t;

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
		void AppendHFrontLeft(void);
		void AppendHFrontRight(void);
		void AppendVFront(void);
		void AppendBigCornerLeft(void);
		void AppendBigCornerRight(void);
		void AppendSmallCornerLeft(void);
		void AppendSmallCornerRight(void);
		void SwapHFrontWithMid(void);
		void SwapVFrontWithMid(void);
		void Dequeue(void);

	public:
		void Display(Bitmap dest);
};

#endif