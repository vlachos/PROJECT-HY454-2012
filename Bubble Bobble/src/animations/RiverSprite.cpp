#include "RiverSprite.h"
#include "AnimationFilmHolder.h"


	/////////// constructor / destructor
	RiverSprite::RiverSprite(int _x, int _y, bool _gravityAddicted, const AnimationFilm * film, const TileLayer * _tileLayer, bool goesLeft)
		: Sprite(_x, _y, _gravityAddicted, film, _tileLayer, goesLeft) {
			riverGoesLeft = goesLeft;
			Coordinates tileStart = _tileLayer->GetTileCoordinates(_y, _x);
			Coordinates startXY = _tileLayer->GetXYCoordinates(tileStart.first, tileStart.second);
			SetX(startXY.first);
			SetY(startXY.second-1);
	}
	RiverSprite::~RiverSprite() {  }


	////////// access to queue
	bool RiverSprite::IsRiverDirectionLeft(void) { return riverGoesLeft; }

	unsigned int RiverSprite::GetRiverLength(void) { return riverQueue.size(); }
	Sprite* RiverSprite::GetRiverItem(unsigned int ith){
		DASSERT(0 <= ith < riverQueue.size() );
		return riverQueue[ith];
	}

	////////// mutate queue
	void RiverSprite::RiverRush(bool left){
		RiverStepForward("RiverHMid");

		SetFilm(AnimationFilmHolder::GetFilm("RiverHFront"));
		SetGoesLeft(left);
	}

	void RiverSprite::RiverFalling(void){
		RiverStepForward("RiverVMid");

		SetFilm(AnimationFilmHolder::GetFilm("RiverVFront"));
		SetGoesLeft(true);
	}

	void RiverSprite::RiverStartFalling(void){

		// and change the leading sprite accordingly
		SetFilm(AnimationFilmHolder::GetFilm("RiverBigCorner"));
	}

	void RiverSprite::RiverStopFalling(void){

		// and change the leading sprite accordingly
		SetFilm(AnimationFilmHolder::GetFilm("RiverSmallCorner"));
		SetGoesLeft(riverGoesLeft);
	}

	///////// private mutators
	void RiverSprite::RiverStepForward(std::string str){

		//push the leading river, to the front of the river queue
		SetFilm(AnimationFilmHolder::GetFilm(str));
		riverQueue.push_front(this->Clone());

		//deque
		if (riverQueue.size() > MAX_RIVER_PARTS)
			riverQueue.pop_back();
	}

	///////// move
	void RiverSprite::Move( int _x, int _y ){
		Sprite::Move(_x, _y);

		if ( IsFalling() ){
			RiverFalling();
		}
		else{
			RiverRush(GoesLeft());
		}
		
	}

	///////// display
	void RiverSprite::Display(Bitmap dest){
		Sprite::Display(dest);

		for (unsigned int i=0; i<riverQueue.size(); ++i)
			riverQueue[i]->Display(dest);
	}