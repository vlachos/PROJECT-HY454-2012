#include "sprite.h"

void Sprite::Display(Bitmap dest){
		
	al_draw_bitmap_region(currFilm->GetBitmap(), frameBox.GetX(), frameBox.GetY(), 
		frameBox.GetWidth(), frameBox.GetHeigth(), x, y, (goesLeft?0:ALLEGRO_FLIP_HORIZONTAL));
}

static bool isSolidTerrain(const TileLayer * tileLayer, Rect frameBox, int x, int y, int _x, int _y){
	if (_y<0){
		return tileLayer->isSolid(x+(frameBox.GetWidth()/2)+_x, y+_y, BBUp);
	}
	if(_x>0){
		return tileLayer->isSolid(x+(frameBox.GetWidth())+_x, y+frameBox.GetHeigth()/2+_y, BBRight);
	}
	if(_x<0){
		return tileLayer->isSolid(x+_x, (y+frameBox.GetHeigth()/2)+_y, BBLeft);
	}
	if (_y>0){
		return tileLayer->isSolid(x+(frameBox.GetWidth()/2)+_x, y+frameBox.GetHeigth()+_y, BBDown);
	}
	
	return true;
}
static int i=0;
void Sprite::Move( int _x, int _y ){
	bool canNotMove = isSolidTerrain(tileLayer, frameBox, x, y, _x, _y);

	if(!canNotMove || onDrugs){
		x += _x;
		y += _y;
		if(gravityAddicted){
			bool overSolidTerrain = tileLayer->isSolid(x+frameBox.GetWidth()/2, y+frameBox.GetHeigth()+1, BBDown);
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
	DASSERT( s && s!=this );
	int _H = frameBox.GetHeigth();
	int _W = frameBox.GetWidth();
	int _x = x;
	int _y = y;
	//std::cout << "Bub x:" << _x << " ,y:" << _y << " , Height:" << frameBox.GetHeigth()<< " ,Width: "<< frameBox.GetWidth() <<"\n";
	int __H = s->GetFrameBox().GetHeigth();
	int __W = s->GetFrameBox().GetWidth();
	int __x = s->GetX();
	int __y = s->GetY();

	/*
	return( !( ( _x > __x + __W || _x + _W < __x ) &&
		    (_y > __y + __H || _y + _H < __y) )  );
	*/
	bool res = (	(( (__x <= _x) && (_x <= (__x + __W)) ) || ( (_x <= __x) && (__x <= (_x + _W)) )) &&
						(( (__y <= _y) && (_y <= (__y + __H)) )	 || ( ( _y <= __y) && (__y <= (_y + _H)) ) ) );
								
	//std::cout << _x<< "<=" <<__x<< "&&"<< __x<< "<="<< _x +_W<< " bool " << (_x <= __x && __x <= (_x + _W)  )<<"\n" ;
	//std::cout << s->currFilm->GetId()<< ", " << res << ", Zen x: "<< __x << " ,y:" << __y << " , Height:" << s->GetFrameBox().GetHeigth()<< " ,Width: "<< s->GetFrameBox().GetWidth() <<"\n";
	
	return res;
	/*
	return (
			 (	( (__x <= _x) && (_x <= (__x + __W)) ) &&
						( (__y <= _y) && (_y <= (__y + __H)) )	)
								||
		     (	( (_x <= __x) && (__x <= (_x + _W)) ) &&
						( ( _y <= __y) && (__y <= (_y + _H)) )	)
		   );
		   */
	/*
	if (goesLeft){
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
	}*/
}