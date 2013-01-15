#include "Animator.h"
#include <assert.h>

/*Protected*/
void Animator::NotifyStopped (void){
	if(onFinish)
		(*onFinish)(this, finishClosure);
}

/*Public*/
Animator :: Animator (void) :
    lastTime(0), state(ANIMATOR_FINISHED), 
    onFinish((FinishCallback) 0), finishClosure((void*) 0){}

Animator :: ~Animator(){}

void Animator :: Stop (void){
	if (!HasFinished()) {
		state = ANIMATOR_STOPPED;
		NotifyStopped();
	}
}
	
bool Animator :: HasFinished (void) const{ 
	return state != ANIMATOR_RUNNING; 
}

void Animator :: TimeShift (timestamp_t offset){
	assert(offset);
	lastTime += offset; 
}

void Animator :: SetOnFinish (FinishCallback f, void* c=(void*) 0){ 
	assert(f);
	assert(c);

	onFinish = f; 
	finishClosure = c; 
}