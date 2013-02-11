#include "MultiSprite.h"

MultiSprite::MultiSprite(int _x, int _y, bool _gravityAddicted, const AnimationFilm * film, const TileLayer * _tileLayer, bool goesLeft):
					Sprite(_x, _y, _gravityAddicted, film,  _tileLayer, goesLeft){

}


void MultiSprite::Display(Bitmap dest){
	for(int i=0; i<currFilm->GetTotalFrames(); ++i){
		const Rect rect = currFilm->GetFrameBox( i );
		al_draw_bitmap_region(currFilm->GetBitmap(), rect.GetX(), rect.GetY(), 
			rect.GetWidth(), rect.GetHeigth(), GetX()+i*rect.GetWidth(), GetY(), (GoesLeft()?0:ALLEGRO_FLIP_HORIZONTAL));
	}
}