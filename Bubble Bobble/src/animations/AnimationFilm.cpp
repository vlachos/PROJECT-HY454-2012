#include "AnimationFilm.h"

AnimationFilm :: AnimationFilm (Bitmap _bitmap, const std::vector<Rect> _boxes, const std::string& _id)
	: bitmap(_bitmap), boxes(_boxes), id(_id){}
    
byte AnimationFilm :: GetTotalFrames (void) const { 
	return boxes.size(); 
}
    
Bitmap AnimationFilm :: GetBitmap (void) const { 
	return bitmap; 
}
    
const std::string AnimationFilm :: GetId (void) const { 
	return id; 
}
    
const Rect AnimationFilm :: GetFrameBox (byte frameNo) const { 
	assert(boxes.size()>frameNo); 
	return boxes[frameNo]; 
}
    
void AnimationFilm :: DisplayFrame (Bitmap dest, const Point& at, byte frameNo) const{
	
}