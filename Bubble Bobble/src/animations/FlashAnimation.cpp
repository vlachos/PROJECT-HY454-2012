#include "FlashAnimation.h"
#include <assert.h>

FlashAnimation :: FlashAnimation (frame_t n, delay_t show, delay_t hide,animid_t id ) 
	:repetitions(n), hideDelay(hide), showDelay(show), Animation(id){
		assert(n);
		assert(show);
		assert(hide);
		assert(id);
}

void FlashAnimation :: SetRepetitions (frame_t n){
	assert(n);
	repetitions = n; 
}

frame_t FlashAnimation :: GetRepetitions (void) const{
	assert(repetitions);
	return repetitions; 
}
    
void FlashAnimation :: SetHideDeay (delay_t d){
	assert(d);
	hideDelay = d; 
}
    
delay_t FlashAnimation :: GetHideDeay (void) const{
	assert(hideDelay);
	return hideDelay; 
}
    
void FlashAnimation :: SetShowDeay (delay_t d){
	assert(d);
	showDelay = d; 
}
    
delay_t FlashAnimation :: GetShowDeay (void) const{
	assert(showDelay);
	return showDelay; 
}
	
Animation* FlashAnimation :: Clone (animid_t newId) const{
	assert(newId);
	assert(newId>=0);
	return new FlashAnimation(repetitions, hideDelay, showDelay, newId); 
}