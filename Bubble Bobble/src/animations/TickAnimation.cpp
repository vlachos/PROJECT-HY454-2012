#include "TickAnimation.h"

TickAnimation::TickAnimation(animid_t _id, delay_t	_delay, byte _repetitions, TickFunc _action, void* _closure): 
				delay(_delay), repetitions(_repetitions), action(_action), closure(_closure),Animation(_id){

}

TickAnimation::~TickAnimation(){
	delay=0;
	repetitions=0;
	action=0;
	closure=0;
}

void TickAnimation::NotifyTickAction (void){
	if(action)
		(*action)(closure);
}

Animation* TickAnimation::Clone (animid_t newId) const{
	return new TickAnimation(newId, delay, repetitions, action, closure);
}

delay_t TickAnimation::GetDelay (void) const{
	return delay;
}

void TickAnimation::SetDelay (delay_t v){
	delay = v;
}

byte TickAnimation::GetRepetitions (void) const{
	return repetitions;
}

void TickAnimation::SetRepetitions (byte v){
	repetitions = v;
}

void TickAnimation::SetTickAction(TickFunc	_action, void* _closure){
	action = _action;
	closure = _closure;
}