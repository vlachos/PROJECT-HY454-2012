#ifndef SPRITE_H
#define SPRITE_H

#include <algorithm>
#include <list>
#include "MemoryManage.h"
#include "Metrics.h"
#include "utilities.h"
#include "AnimationFilm.h"
#include "Sprite.h"




class Sprite{
	public:
		class SpriteStartFallingListener{
			public:
				virtual void operator()(Sprite * sprite) const = 0;
		};

		class SpriteStopFallingListener{
			public:
				virtual void operator()(Sprite * sprite) const = 0;
		};

	private:
		byte			frameNo;
		Rect			frameBox;
		Dim				x,y;
		bool			isVisible, gravityAddicted, isFalling;
		AnimationFilm *	currFilm;

		std::list<SpriteStartFallingListener *> spriteStartFallingListener;
		std::list<SpriteStopFallingListener *> spriteStopFallingListener;

		void NotifyStopFalling() {	
			std::list<SpriteStopFallingListener *>::const_iterator iterator;
			for (iterator = spriteStopFallingListener.begin(); iterator != spriteStopFallingListener.end(); ++iterator) {
				(*(*iterator))(this);
			}
		}

		void NotifyStartFalling(){	
			std::list<SpriteStartFallingListener *>::const_iterator iterator;
			for (iterator = spriteStartFallingListener.begin(); iterator != spriteStartFallingListener.end(); ++iterator) {
				(*(*iterator))(this);
			}
		}

	public:
		void SetFrame( byte i){
			if( i != frameNo){
				DASSERT( i < currFilm->GetTotalFrames() );
				frameBox = currFilm->GetFrameBox( frameNo = i );
			}
		}

		Dim GetX(void) { return x; }
		Dim GetY(void) { return y; }
		Rect GetFrameBox(void){ return frameBox; }
		byte GetFrame(void) const { return frameNo; }
		void SetVisibility(bool v) { isVisible = v; }
		bool IsVisible(void) const { return isVisible; }
		bool IsGravityAddicted(void) const { return gravityAddicted; }
		void SetGravityAddicted( bool a ) { gravityAddicted = a; }
		bool IsFalling(void) const { return isFalling; }
		void SetFalling( bool f ) { isFalling = f; }
		bool CollisionCheck( Sprite * s );
		void Display(Bitmap dest);
		void Move( Dim _x, Dim _y );

		void AddStartFallingListener(SpriteStartFallingListener * sl) { spriteStartFallingListener.push_back( sl ); }
		void RemoveStartFallingListener(SpriteStartFallingListener * sl) { spriteStartFallingListener.remove( sl ); }

		void AddStopFallingListener(SpriteStopFallingListener * sl) { spriteStopFallingListener.push_back( sl ); }
		void RemoveStopFallingListener(SpriteStopFallingListener * sl) { spriteStopFallingListener.remove( sl ); }

		Sprite(Dim _x, Dim _y, bool _gravityAddicted, AnimationFilm * film): 
			x(_x), y(_y), currFilm(film), isVisible(true){

			isFalling = false;
			gravityAddicted = _gravityAddicted;
			frameNo = currFilm->GetTotalFrames();
			SetFrame(0);
		}
};

/*
using the listeners...

class outer{
	private:
		class Tmp : public Sprite::SpriteStartFallingListener{
			private:
				outer * r;
			public:
				void operator()(Sprite * sprite)
					{ r->todo(sprite); }
				Tmp (outer * _r): r(_r){}
		};
		Tmp * tmp;
	public:
		void todo(Sprite * sprite);
		outer(Sprite * sprite){
			//sprite->AddStartFallingListener(  );
			//tmp = new Tmp(this);
		}
};


*/

#endif