#include "Animator.h"
#include <assert.h>
#include <iostream>
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
	lastTime += offset; 
}

void Animator :: SetOnFinish (FinishCallback f, void* c=(void*) 0){ 

	onFinish = f; 
	finishClosure = c; 
}

enum animatorType_t Animator ::GetAnimatorType(void){
	return unkwownAnimator_t;
}