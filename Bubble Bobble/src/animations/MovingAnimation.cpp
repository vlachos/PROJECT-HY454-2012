#include "MovingAnimation.h"
#include <assert.h>

MovingAnimation :: MovingAnimation (offset_t _dx, offset_t _dy, delay_t _delay, bool c, animid_t _id)
	: dx(_dx), dy(_dy), delay(_delay), continuous(c), Animation(_id){
		assert(_dx);
		assert(_dy);
		assert(_delay);
		assert(c);
		assert(_id);
}

offset_t MovingAnimation :: GetDx (void) const{
	assert(dx);
	return dx; 
}

void MovingAnimation :: SetDx (offset_t v){
	assert(v);
	dx = v; 
}

offset_t MovingAnimation :: GetDy (void) const{
	assert(dy);
	return dy; 
}

void MovingAnimation :: SetDy (offset_t v){
	assert(v);
	dy = v; 
}

delay_t MovingAnimation :: GetDelay (void) const{
	assert(delay);
	return delay; 
}

void MovingAnimation :: SetDelay (delay_t v){
	assert(v);
	delay = v; 
}

bool MovingAnimation :: GetContinuous (void) const{
	assert(continuous);
	return continuous; 
}

void MovingAnimation :: SetContinuous (bool v){
	assert(v);
	continuous = v; 
}

Animation* MovingAnimation :: Clone (animid_t newId) const{
	assert(newId);
	return new MovingAnimation(dx, dy, delay, continuous, newId); }