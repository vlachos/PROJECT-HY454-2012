#include "FlashAnimation.h"
#include "MemoryManage.h"

FlashAnimation :: FlashAnimation (frame_t n, delay_t show, delay_t hide,animid_t id ) 
	:repetitions(n), hideDelay(hide), showDelay(show), Animation(id){
		DASSERT(n);
		DASSERT(show);
		DASSERT(hide);
		DASSERT(id);
}

void FlashAnimation :: SetRepetitions (frame_t n){
	DASSERT(n);
	repetitions = n; 
}

frame_t FlashAnimation :: GetRepetitions (void) const{
	DASSERT(repetitions);
	return repetitions; 
}
    
void FlashAnimation :: SetHideDeay (delay_t d){
	DASSERT(d);
	hideDelay = d; 
}
    
delay_t FlashAnimation :: GetHideDeay (void) const{
	DASSERT(hideDelay);
	return hideDelay; 
}
    
void FlashAnimation :: SetShowDeay (delay_t d){
	DASSERT(d);
	showDelay = d; 
}
    
delay_t FlashAnimation :: GetShowDeay (void) const{
	DASSERT(showDelay);
	return showDelay; 
}
	
Animation* FlashAnimation :: Clone (animid_t newId) const{
	DASSERT(newId);
	DASSERT(newId>=0);
	return new FlashAnimation(repetitions, hideDelay, showDelay, newId); 
}