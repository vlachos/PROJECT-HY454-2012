#include "AnimationFilm.h"
#include <assert.h>
#include <allegro5\allegro.h>


AnimationFilm :: AnimationFilm (Bitmap _bitmap, const std::vector<Rect> _boxes, const std::string& _id)
	: bitmap(_bitmap), boxes(_boxes), id(_id){

		assert(_bitmap);
		assert(!(_boxes.empty()));
		assert((!_id.empty()));
}
    
byte AnimationFilm :: GetTotalFrames (void) const{
	assert(!(boxes.empty()));

	return boxes.size(); 
}
    
Bitmap AnimationFilm :: GetBitmap (void) const {
	assert(bitmap);

	return bitmap; 
}
    
const std::string AnimationFilm :: GetId (void) const {
	assert(!(id.empty()));

	return id; 
}
    
const Rect AnimationFilm :: GetFrameBox (byte frameNo) const { 
	assert(boxes.size()>frameNo); 

	return boxes[frameNo]; 
}
    
void AnimationFilm :: DisplayFrame (Bitmap dest, const Point& at, byte frameNo) const{
	assert(dest);
	assert(&at);
	assert(frameNo);

	// Here is masked blit
}