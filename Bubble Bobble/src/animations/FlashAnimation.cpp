#include "FlashAnimation.h"
#include "MemoryManage.h"

FlashAnimation :: FlashAnimation (frame_t n, delay_t show, delay_t hide,animid_t id ) 
	:repetitions(n), hideDelay(hide), showDelay(show), Animation(id){
		DASSERT(n>=0);
		DASSERT(show>=0);
		DASSERT(hide>=0);
		DASSERT(id>0);
}

void FlashAnimation :: SetRepetitions (frame_t n){
	DASSERT(n>=0);
	repetitions = n; 
}

frame_t FlashAnimation :: GetRepetitions (void) const{
	DASSERT(repetitions>=0);
	return repetitions; 
}
    
void FlashAnimation :: SetHideDeay (delay_t d){
	DASSERT(d>=0);
	hideDelay = d; 
}
    
delay_t FlashAnimation :: GetHideDeay (void) const{
	DASSERT(hideDelay>=0);
	return hideDelay; 
}
    
void FlashAnimation :: SetShowDeay (delay_t d){
	DASSERT(d>=0);
	showDelay = d; 
}
    
delay_t FlashAnimation :: GetShowDeay (void) const{
	DASSERT(showDelay>=0);
	return showDelay; 
}
	
Animation* FlashAnimation :: Clone (animid_t newId) const{
	DASSERT(newId>0);
	return new FlashAnimation(repetitions, hideDelay, showDelay, newId); 
}