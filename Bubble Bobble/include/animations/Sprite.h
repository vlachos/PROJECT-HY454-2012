#ifndef SPRITE_H
#define SPRITE_H

#include <algorithm>
#include <vector>
#include "MemoryManage.h"
#include "Metrics.h"
#include "utilities.h"
#include "AnimationFilm.h"
#include "Sprite.h"
#include "TileLayer.h"

#define COLLISION_OFFSET 8

class Sprite : public LatelyDestroyable{
	public:
		class SpriteStartFallingListener{
			public:
				virtual void OnStartFalling(Sprite * sprite) = 0;
		};

		class SpriteStopFallingListener{
			public:
				virtual void OnStopFalling(Sprite * sprite) = 0;
		};
		
	private:
		byte			frameNo;
		Rect			frameBox;
		int				x,y;
		bool			isVisible, gravityAddicted, isFalling, goesLeft, onDrugs;
	protected:
		const AnimationFilm *	currFilm;
	private:
		const TileLayer *		tileLayer;

		std::vector<SpriteStartFallingListener *> spriteStartFallingListener;
		std::vector<SpriteStopFallingListener *> spriteStopFallingListener;

		void NotifyStopFalling() {	
			if (IsAlive()){
				for (unsigned int i=0; i<spriteStopFallingListener.size(); ++i) {
					spriteStopFallingListener[i]->OnStopFalling(this);
				}
			}
		}

		void NotifyStartFalling(){	
			std::list<SpriteStartFallingListener *>::const_iterator iterator;
			if (IsAlive()){
				for (unsigned int i=0; i<spriteStartFallingListener.size(); ++i) {
					spriteStartFallingListener[i]->OnStartFalling(this);
				}
			}
		}

	public:
		void SetFrame( byte i){
			if( i != frameNo){
				DASSERT( i < currFilm->GetTotalFrames() );
				frameBox = currFilm->GetFrameBox( frameNo = i );
			}
		}

		int GetX(void) const { return x; }
		int GetY(void) const { return y; }
		void SetX(int _x) { x = _x; }
		void SetY(int _y) { y = _y; }
		Rect GetFrameBox(void) const{ return frameBox; }
		byte GetFrame(void) const { return frameNo; }
		void SetVisibility(bool v) { isVisible = v; }
		bool IsVisible(void) const { return isVisible; }
		bool IsGravityAddicted(void) const { return gravityAddicted; }
		void SetGravityAddicted( bool a ) { gravityAddicted = a; }
		bool IsFalling(void) const { return isFalling; }
		void SetFalling( bool f ) { isFalling = f; }
		bool GoesLeft() const { return goesLeft; }
		void SetGoesLeft( bool _goesLeft ) { goesLeft = _goesLeft; }
		void SetOnDrugs(bool b) { onDrugs = b; }
		bool IsOnDrugs() { return onDrugs; }
		const TileLayer * GetActionLayer(void) { return tileLayer; }
		const AnimationFilm* GetFilm(void) { return currFilm; }
		void SetFilm(const AnimationFilm * film) { currFilm = film; }
		bool CollisionCheck( Sprite * s );
		virtual void Display(Bitmap dest);
		void Move( int _x, int _y );
		bool IsSolidTerrain(int _x, int _y);

		void AddStartFallingListener(SpriteStartFallingListener * sl) { spriteStartFallingListener.push_back( sl ); }
		void RemoveStartFallingListener(SpriteStartFallingListener * sl) { 
			std::vector<SpriteStartFallingListener*>::iterator it = std::find(spriteStartFallingListener.begin(), spriteStartFallingListener.end(), sl);
			DASSERT( it != spriteStartFallingListener.end() ); 
			spriteStartFallingListener.erase(it); 
		}
		void RemoveAllStartFallingListeners( void ) { spriteStartFallingListener.clear(); }

		void AddStopFallingListener(SpriteStopFallingListener * sl) { spriteStopFallingListener.push_back( sl ); }
		void RemoveStopFallingListener(SpriteStopFallingListener * sl) { 
			std::vector<SpriteStopFallingListener*>::iterator it = std::find(spriteStopFallingListener.begin(), spriteStopFallingListener.end(), sl);
			DASSERT( it != spriteStopFallingListener.end() ); 
			spriteStopFallingListener.erase(it); 
		}
		void RemoveAllStopFallingListeners( void ) { spriteStopFallingListener.clear(); }

		void ClearListeners() { RemoveAllStopFallingListeners( ); RemoveAllStartFallingListeners();}
		Sprite(int _x, int _y, bool _gravityAddicted, const AnimationFilm * film, const TileLayer * _tileLayer, bool goesLeft): 
			x(_x), y(_y), currFilm(film), isVisible(true), tileLayer(_tileLayer), goesLeft(goesLeft){
			isFalling = false;
			gravityAddicted = _gravityAddicted;
			frameNo = currFilm->GetTotalFrames();
			SetFrame(0);
			onDrugs = false;
		}

		Sprite* Clone() { return new Sprite(x,y,gravityAddicted,currFilm,tileLayer,goesLeft); }
};

#endif