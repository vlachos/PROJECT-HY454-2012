#include "BubLifesSprite.h"
#include "BubbleLogic.h"

BubLifesSprite::BubLifesSprite(int _x, int _y, bool _gravityAddicted, const AnimationFilm * film, const TileLayer * _tileLayer, bool goesLeft):
					MultiSprite(_x, _y, _gravityAddicted, film,  _tileLayer, goesLeft) { isBubs = true; }


void BubLifesSprite::Display(Bitmap dest){
	int maxLifes = -1;
	isBubs ? maxLifes=BubbleLogic::GetBubProfile()->GetLifes() : maxLifes=BubbleLogic::GetBobProfile()->GetLifes();
	for(int i=0; i<maxLifes; ++i){
		const Rect rect = currFilm->GetFrameBox( i );
		al_draw_bitmap_region(currFilm->GetBitmap(), rect.GetX(), rect.GetY(), 
			rect.GetWidth(), rect.GetHeigth(), GetX()+i*rect.GetWidth(), GetY(), (GoesLeft()?0:ALLEGRO_FLIP_HORIZONTAL));
	}
}