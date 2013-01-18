#include "FrameRangeAnimation.h"
#include "MemoryManage.h"

FrameRangeAnimation :: FrameRangeAnimation (frame_t s, frame_t e, offset_t dx, offset_t dy, delay_t d, bool c, animid_t id)
	: start(s), end(e), MovingAnimation(dx, dy, d, c, id){
		DASSERT(s);
		DASSERT(e);
		DASSERT(dx);
		DASSERT(dy);
		DASSERT(d);
		DASSERT(c);
		DASSERT(id);
}

frame_t FrameRangeAnimation ::	GetStartFrame (void) const{
	DASSERT(start);
	return start; 
}

void FrameRangeAnimation :: SetStartFrame (frame_t v){
	DASSERT(v);
	start = v; 
}

frame_t FrameRangeAnimation ::	GetEndFrame (void) const{
	DASSERT(end);
	return end; 
}

void FrameRangeAnimation :: SetEndFrame (frame_t v){ 
	DASSERT(v);
	end = v; 
}

Animation* FrameRangeAnimation :: Clone (animid_t newId) const{
	DASSERT(newId);
	return new FrameRangeAnimation(start, end, GetDx(), GetDy(), GetDelay(), GetContinuous(), newId);
}
