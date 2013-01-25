#include "sprite.h"

void Sprite::Display(Bitmap dest){
	al_draw_bitmap_region(currFilm->GetBitmap(), frameBox.GetX(), frameBox.GetY(), 
		frameBox.GetWidth(), frameBox.GetHeigth(), x-(frameBox.GetWidth()/2), y-frameBox.GetHeigth(), (goesLeft?0:ALLEGRO_FLIP_HORIZONTAL));
}

static bool isSolidTerrain(const TileLayer * tileLayer, Rect frameBox, Dim x, Dim y, Dim _x, Dim _y){
	if (_y<0){
		return tileLayer->isSolid(x+_x, y-frameBox.GetHeigth()+_y, BBUp);
	}
	else if(_x>0){
		return tileLayer->isSolid(x+(frameBox.GetWidth()/2)+_x, y+_y, BBRight);
	}
	else if(_x<0){
		return tileLayer->isSolid(x-(frameBox.GetWidth()/2)+_x, y+_y, BBLeft);
	}
	else if (_y>0){
		return tileLayer->isSolid(x+_x, y+_y, BBDown);
	}
	else{
		return tileLayer->isSolid(x+_x, y+_y, BBDown);
	}
}
static int i=0;
void Sprite::Move( Dim _x, Dim _y ){
	bool canNotMove = isSolidTerrain(tileLayer, frameBox, x, y, _x, _y);
	
	if(!canNotMove){
		x += _x;
		y += _y;
		if(gravityAddicted){
			bool overSolidTerrain = tileLayer->isSolid(x, y+1, BBDown);
			if(overSolidTerrain){
				if(isFalling){
					isFalling = false;
					NotifyStopFalling(); 
				}
			}else
			if (!isFalling) {
			   isFalling = true; 
			   
			   NotifyStartFalling(); 
			}
		}
	}
}

bool Sprite::CollisionCheck( Sprite * s ){
	DASSERT( s );
	return ( x + frameBox.GetWidth() >= s->GetX() && s->GetX() + s->GetFrameBox().GetWidth() >= x ) &&
		   ( y + frameBox.GetHeigth() >= s->GetY() && s->GetY() + s->GetFrameBox().GetHeigth() >= y ) ;

}