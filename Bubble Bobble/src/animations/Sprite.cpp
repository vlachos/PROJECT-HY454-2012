#include "sprite.h"

void Sprite::Display(Bitmap dest){
	al_draw_bitmap_region(currFilm->GetBitmap(), frameBox.GetX(), frameBox.GetY(), 
		frameBox.GetWidth(), frameBox.GetHeigth(), x, y, 0);
}

void Sprite::Move( Dim _x, Dim _y ){
	x += _x;
	y += _y;
	if(gravityAddicted){
		//overSolidTerrain = check the terrain tiles
		bool overSolidTerrain = true;
		if(overSolidTerrain){

		}else
		if(!isFalling){
			isFalling = false;

		}
	}
}

bool Sprite::CollisionCheck( Sprite * s ){
	DASSERT( s );
	return ( x + frameBox.GetWidth() >= s->GetX() && s->GetX() + s->GetFrameBox().GetWidth() >= x ) &&
		   ( y + frameBox.GetHeigth() >= s->GetY() && s->GetY() + s->GetFrameBox().GetHeigth() >= y ) ;

}