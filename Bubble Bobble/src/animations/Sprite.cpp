#include "sprite.h"

void Sprite::Display(Bitmap dest){
		
	al_draw_bitmap_region(currFilm->GetBitmap(), frameBox.GetX(), frameBox.GetY(), 
		frameBox.GetWidth(), frameBox.GetHeigth(), x-(frameBox.GetWidth()/2), y-frameBox.GetHeigth(), (goesLeft?0:ALLEGRO_FLIP_HORIZONTAL));
}

static bool isSolidTerrain(const TileLayer * tileLayer, Rect frameBox, int x, int y, int _x, int _y){
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
void Sprite::Move( int _x, int _y ){
	
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
	DASSERT( s!=this );
	Dim _H = frameBox.GetHeigth();
	Dim _W = frameBox.GetWidth();
	Dim _x = x - _W/2;
	Dim _y = y - _H;

	Dim __H = s->GetFrameBox().GetHeigth();
	Dim __W = s->GetFrameBox().GetWidth();
	Dim __x = s->GetX() - __W/2;
	Dim __y = s->GetY() - __H;

	/*
	if( !( ( _x > __x + __W || _x + _W < __x ) &&
		    (_y > __y + __H || _y + _H < __y) )  ){
			  std::cout << "inn\n";
	}

	//std::cout << _x<< "<=" <<__x<< "&&"<< __x<< "<="<< _x +_W<< " bool " << (_x <= __x && __x <= (_x + _W)  )<<"\n" ;
	//std::cout << "Zen x: "<< __x << " ,y:" << __y << " , Height:" << s->GetFrameBox().GetHeigth()<< " ,Width: "<< s->GetFrameBox().GetWidth() <<"\n";
	//std::cout << "Bub x:" << _x << " ,y:" << _y << " , Height:" << frameBox.GetHeigth()<< " ,Width: "<< frameBox.GetWidth() <<"\n";
	*/

	if (!goesLeft){
	return (
			 (	( (__x <= _x) && (_x <= (__x + __W)) ) &&
						( (__y <= _y) && (_y <= (__y + __H)) )	)
								||
		     (	( (_x <= __x) && (__x <= (_x + _W)) ) &&
						( ( _y <= __y) && (__y <= (_y + _H)) )	)
		   );
	}
	else{
		return (
			 (	( (__x <= _x) && (_x <= (__x + __W)) ) &&
						( ( _y <= __y) && (__y <= (_y + _H)) )	)
								||
		     (	( (_x <= __x) && (__x <= (_x + _W)) ) &&
						( (__y <= _y) && (_y <= (__y + __H)) )	)
		   );
	}
}