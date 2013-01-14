#include "FrameRangeAnimation.h"
#include <assert.h>

FrameRangeAnimation :: FrameRangeAnimation (frame_t s, frame_t e, offset_t dx, offset_t dy, delay_t d, bool c, animid_t id)
	: start(s), end(e), MovingAnimation(dx, dy, d, c, id){
		assert(s);
		assert(e);
		assert(dx);
		assert(dy);
		assert(d);
		assert(c);
		assert(id);
}

frame_t FrameRangeAnimation ::	GetStartFrame (void) const{
	assert(start);
	return start; 
}

void FrameRangeAnimation :: SetStartFrame (frame_t v){
	assert(v);
	start = v; 
}

frame_t FrameRangeAnimation ::	GetEndFrame (void) const{
	assert(end);
	return end; 
}

void FrameRangeAnimation :: SetEndFrame (frame_t v){ 
	assert(v);
	end = v; 
}

Animation* FrameRangeAnimation :: Clone (animid_t newId) const{
	assert(newId);
	return new FrameRangeAnimation(start, end, GetDx(), GetDy(), GetDelay(), GetContinuous(), newId);
}
