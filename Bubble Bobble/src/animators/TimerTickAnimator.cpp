#include "TimerTickAnimator.h"
#include <iostream>

TimerTickAnimator::TimerTickAnimator(TickAnimation* _tick):tick(_tick), repetitions(0){
	
}

TimerTickAnimator::~TimerTickAnimator(void){

}

TickAnimation* TimerTickAnimator::GetAnimation(void){
	return tick;
}

void TimerTickAnimator::Start (timestamp_t t){
	DASSERT(t>=0);
	lastTime = t;
	state = ANIMATOR_RUNNING;
}

void TimerTickAnimator::Display(Bitmap at){

}

void TimerTickAnimator::Progress (timestamp_t currTime){
	DASSERT(tick);
	DASSERT(lastTime<=currTime);

	while (currTime > lastTime && currTime - lastTime >= tick->GetDelay()){
		
		tick->NotifyTickAction();
		lastTime += tick->GetDelay();
		if (++repetitions==tick->GetRepetitions()) {
			state = ANIMATOR_FINISHED;
			
			NotifyStopped();
			return;
		}
	}
}