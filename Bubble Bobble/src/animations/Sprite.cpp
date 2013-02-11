#include "sprite.h"

void Sprite::Display(Bitmap dest){
	if(isBub==-1)
		al_draw_bitmap_region(currFilm->GetBitmap(), frameBox.GetX(), frameBox.GetY(), 
			frameBox.GetWidth(), frameBox.GetHeigth(), x, y, (goesLeft?0:ALLEGRO_FLIP_HORIZONTAL));
	else
		al_draw_bitmap_region(currFilm->GetBitmap(), isBub?frameBox.GetX():frameBox.GetX()+BUB_IMAGE_OFFSET, frameBox.GetY(), 
			frameBox.GetWidth(), frameBox.GetHeigth(), x, y, (goesLeft?0:ALLEGRO_FLIP_HORIZONTAL));
}

bool Sprite::IsSolidTerrain(int _x, int _y){
	bool s=false;
	if (_y<0){
		s = tileLayer->isSolid(x+(frameBox.GetWidth()/2)+_x, y+_y, BBUp);
	}
	if(s) return true;
	s=false;
	if(_x>0){
		s = tileLayer->isSolid(x+(frameBox.GetWidth())+_x, y+frameBox.GetHeigth()+_y, BBRight);
	}
	if(s) return true;
	s=false;
	if(_x<0){
		s = tileLayer->isSolid(x+_x, (y+frameBox.GetHeigth())+_y, BBLeft);
	}
	if(s) return true;
	s=false;
	if (_y>0){
		s= tileLayer->isSolid(x+(frameBox.GetWidth()/2)+_x, y+frameBox.GetHeigth()+_y, BBDown);
	}
	
	return s;
}

void Sprite::Move( int _x, int _y ){
	bool canNotMove = IsSolidTerrain(_x, _y);

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
	int _H = frameBox.GetHeigth()-COLLISION_OFFSET;
	int _W = frameBox.GetWidth()-COLLISION_OFFSET;
	int _x = x+COLLISION_OFFSET;
	int _y = y+COLLISION_OFFSET;

	int __H = s->GetFrameBox().GetHeigth()-COLLISION_OFFSET;
	int __W = s->GetFrameBox().GetWidth()-COLLISION_OFFSET;
	int __x = s->GetX()+COLLISION_OFFSET;
	int __y = s->GetY()+COLLISION_OFFSET;

	return  (	(( (__x <= _x) && (_x <= (__x + __W)) ) || 
								( (_x <= __x) && (__x <= (_x + _W)) ))
								&&
						(( (__y <= _y) && (_y <= (__y + __H )) )	 ||
								( ( _y <= __y) && (__y <= (_y + _H )) ) ) );
								

	//std::cout << "Bub x:" << _x << " ,y:" << _y << " , Height:" << frameBox.GetHeigth()<< " ,Width: "<< frameBox.GetWidth() <<"\n";

	//std::cout << _x<< "<=" <<__x<< "&&"<< __x<< "<="<< _x +_W<< " bool " << (_x <= __x && __x <= (_x + _W)  )<<"\n" ;
	//std::cout << s->currFilm->GetId()<< ", " << res << ", Zen x: "<< __x << " ,y:" << __y << " , Height:" << s->GetFrameBox().GetHeigth()<< " ,Width: "<< s->GetFrameBox().GetWidth() <<"\n";
}