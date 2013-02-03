#include "TickAnimation.h"

TickAnimation::TickAnimation(animid_t _id, delay_t	_delay, byte _repetitions, TickFunc _action, void* _closure): 
				Animation(_id), delay(_delay), repetitions(_repetitions), action(_action), closure(_closure){

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