#ifndef SPRITE_H
#define SPRITE_H

#include "MemoryManage.h"
#include "Metrics.h"
#include "utilities.h"
#include "AnimationFilm.h"
#include "Sprite.h"

class Sprite{
	private:
		byte			frameNo;
		Rect			frameBox;
		Dim				x,y;
		bool			isVisible;
		AnimationFilm *	currFilm;

	public:
		void SetFrame( byte i){
			if( i != frameNo){
				DASSERT( i < currFilm->GetTotalFrames() );
				frameBox = currFilm->GetFrameBox( frameNo = i );
			}
		}

		byte GetFrame(void) const { return frameNo; }
		void SetVisibility(bool v) { isVisible = v; }
		bool IsVisible(void) const { return isVisible; }
		bool CollisionCheck( Sprite * s );
		void Display(Bitmap dest, Rect & da);
		void Move( Dim _x, Dim _y );

		Sprite(Dim _x, Dim _y, AnimationFilm * film): x(_x), y(_y), currFilm(film), isVisible(true){
			frameNo = currFilm->GetTotalFrames();
			SetFrame(0);
		}
};

#endif