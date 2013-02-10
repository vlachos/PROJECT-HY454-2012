#include "RiverSprite.h"
#include "AnimationFilmHolder.h"


	/////////// constructor / destructor
	RiverSprite::RiverSprite(int _x, int _y, bool _gravityAddicted, const AnimationFilm* film, const TileLayer * _tileLayer, bool goesLeft)
		: Sprite(_x, _y, _gravityAddicted, film, _tileLayer, goesLeft) {
			riverGoesLeft = goesLeft;

			Coordinates tileStart = _tileLayer->GetTileCoordinates(_y, _x);
			Coordinates startXY = _tileLayer->GetXYCoordinates(tileStart.first, tileStart.second);

			if (goesLeft)	SetX(startXY.first);
			else	SetX(startXY.first-1);
			SetY(startXY.second-1);

			riverQueue.push_front(new Sprite(GetX(), GetY(),IsGravityAddicted(),film,GetActionLayer(),GoesLeft()));

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
		RiverStepForward("RiverHFront","RiverHMid");
		//SetFilm(AnimationFilmHolder::GetFilm("RiverHFront"));
		SetGoesLeft(left);
	}

	void RiverSprite::RiverFalling(void){
		RiverStepForward("RiverVFront","RiverVMid");
		//SetFilm(AnimationFilmHolder::GetFilm("RiverVFront"));
		SetGoesLeft(true);
	}

	void RiverSprite::RiverStartFalling(void){
		//SetNewFront("RiverBigCorner");
		SetGoesLeft(true);
	}

	void RiverSprite::RiverStopFalling(void){
		//SetNewFront("RiverSmallCorner");
		SetGoesLeft(riverGoesLeft);
	}

	void RiverSprite::SetNewFront(std::string str){
		int x = riverQueue[0]->GetX();
		int y = riverQueue[0]->GetY();
		bool left = riverQueue[0]->GoesLeft();

		riverQueue.pop_front();
		riverQueue.push_front(new Sprite(x, y, IsGravityAddicted(),
									AnimationFilmHolder::GetFilm(str),GetActionLayer(), left) );
	}

	void RiverSprite::SetNewBack(std::string str){
		int x = riverQueue[riverQueue.size()-1]->GetX();
		int y = riverQueue[riverQueue.size()-1]->GetY();
		bool left = !riverQueue[riverQueue.size()-1]->GoesLeft();

		riverQueue.pop_back();
		riverQueue.push_back(new Sprite(x, y, IsGravityAddicted(),
									AnimationFilmHolder::GetFilm(str),GetActionLayer(), left) );
	}


	///////// private mutators
	void RiverSprite::RiverStepForward(std::string frontStr, std::string midStr){

		SetNewFront(midStr);

		riverQueue.push_front(new Sprite(GetX(), GetY(),IsGravityAddicted(),
								AnimationFilmHolder::GetFilm(frontStr),GetActionLayer(),GoesLeft()));

		//deque
		if (riverQueue.size() > MAX_RIVER_PARTS)
			riverQueue.pop_back();
	}

	///////// move
	void RiverSprite::Move( int _x, int _y ){

		if ( IsFalling() ){
			RiverFalling();
		}
		else{
			RiverRush(GoesLeft());
		}
		Sprite::Move(_x, _y);
	}

	///////// display
	void RiverSprite::Display(Bitmap dest){
		for (unsigned int i=0; i<riverQueue.size(); ++i)
			riverQueue[i]->Display(dest);
	}