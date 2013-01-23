#include "FrameRangeAnimation.h"
#include "MemoryManage.h"

FrameRangeAnimation :: FrameRangeAnimation (frame_t s, frame_t e, offset_t dx, offset_t dy, delay_t d, bool c, animid_t id)
	: start(s), end(e), MovingAnimation(dx, dy, d, c, id){
		DASSERT(s>=0);
		DASSERT(e>=0);
		DASSERT(d>=0);
		DASSERT(id>0);
}

FrameRangeAnimation :: ~FrameRangeAnimation(void){
	start=end=-1;
}

frame_t FrameRangeAnimation ::	GetStartFrame (void) const{
	DASSERT(start>=0);
	return start; 
}

void FrameRangeAnimation :: SetStartFrame (frame_t v){
	DASSERT(v>=0);
	start = v; 
}

frame_t FrameRangeAnimation ::	GetEndFrame (void) const{
	DASSERT(end>=0);
	return end; 
}

void FrameRangeAnimation :: SetEndFrame (frame_t v){ 
	DASSERT(v>=0);
	end = v; 
}

Animation* FrameRangeAnimation :: Clone (animid_t newId) const{
	DASSERT(newId>0);
	return new FrameRangeAnimation(start, end, GetDx(), GetDy(), GetDelay(), GetContinuous(), newId);
}
