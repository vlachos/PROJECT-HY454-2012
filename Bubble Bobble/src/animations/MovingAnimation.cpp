#include "MovingAnimation.h"
#include "MemoryManage.h"

MovingAnimation :: MovingAnimation (offset_t _dx, offset_t _dy, delay_t _delay, bool c, animid_t _id)
	: dx(_dx), dy(_dy), delay(_delay), continuous(c), Animation(_id){
		DASSERT(_dx);
		DASSERT(_dy);
		DASSERT(_delay);
		DASSERT(c);
		DASSERT(_id);
}

offset_t MovingAnimation :: GetDx (void) const{
	DASSERT(dx);
	return dx; 
}

void MovingAnimation :: SetDx (offset_t v){
	DASSERT(v);
	dx = v; 
}

offset_t MovingAnimation :: GetDy (void) const{
	DASSERT(dy);
	return dy; 
}

void MovingAnimation :: SetDy (offset_t v){
	DASSERT(v);
	dy = v; 
}

delay_t MovingAnimation :: GetDelay (void) const{
	DASSERT(delay);
	return delay; 
}

void MovingAnimation :: SetDelay (delay_t v){
	DASSERT(v);
	delay = v; 
}

bool MovingAnimation :: GetContinuous (void) const{
	DASSERT(continuous);
	return continuous; 
}

void MovingAnimation :: SetContinuous (bool v){
	DASSERT(v);
	continuous = v; 
}

Animation* MovingAnimation :: Clone (animid_t newId) const{
	DASSERT(newId);
	return new MovingAnimation(dx, dy, delay, continuous, newId); }