#include "RiverSprite.h"


	RiverSprite::RiverSprite(int _x, int _y, bool _gravityAddicted, const AnimationFilm * film, const TileLayer * _tileLayer, bool goesLeft)
		: Sprite(_x, _y, _gravityAddicted, film, _tileLayer, goesLeft){
		
	}

	RiverSprite::~RiverSprite(){
	}



	unsigned int RiverSprite::GetRiverLength(void) { return riverQueue.size(); }
	Sprite* RiverSprite::GetRiverItem(unsigned int ith){
		DASSERT(0 <= ith < riverQueue.size() );
		return riverQueue[ith];
	}



	void RiverSprite::AppendHFrontLeft(void){
	}

	void RiverSprite::AppendHFrontRight(void){
	}

	void RiverSprite::AppendVFront(void){
	}

	void RiverSprite::AppendBigCornerLeft(void){
	}

	void RiverSprite::AppendBigCornerRight(void){
	}

	void RiverSprite::AppendSmallCornerLeft(void){
	}

	void RiverSprite::AppendSmallCornerRight(void){
	}

	void RiverSprite::SwapHFrontWithMid(void){
	}

	void RiverSprite::SwapVFrontWithMid(void){
	}

	void RiverSprite::Dequeue(void){
	}