#include "AnimationFilm.h"
#include "MemoryManage.h"
#include <allegro5\allegro.h>

AnimationFilm :: AnimationFilm()
	:bitmap(0) {}

AnimationFilm :: AnimationFilm (Bitmap _bitmap, const std::vector<Rect> _boxes, const std::string& _id)
	: bitmap(_bitmap), boxes(_boxes), id(_id){

		DASSERT(!(_boxes.empty()));
		DASSERT((!_id.empty()));
}

AnimationFilm ::~AnimationFilm(){
	boxes.clear();
	unullify( bitmap ); // only bitmap loader can delte a bitmap 
	id.clear();
}
    
byte AnimationFilm :: GetTotalFrames (void) const{
	DASSERT(!(boxes.empty()));

	return boxes.size(); 
}
    
Bitmap AnimationFilm :: GetBitmap (void) const {
	DASSERT(bitmap);

	return bitmap; 
}
    
const std::string AnimationFilm :: GetId (void) const {
	DASSERT(!(id.empty()));

	return id; 
}
    
const Rect AnimationFilm :: GetFrameBox (byte frameNo) const { 
	DASSERT(boxes.size()>frameNo); 

	return boxes[frameNo]; 
}
    
/*void AnimationFilm :: DisplayFrame (Bitmap dest, const Point& at, byte frameNo) const{
	DASSERT(dest);
	DASSERT(at.GetX()>=0);
	DASSERT(at.GetY()>=0);
	DASSERT(frameNo>=0);

	// Here is masked blit
}*/