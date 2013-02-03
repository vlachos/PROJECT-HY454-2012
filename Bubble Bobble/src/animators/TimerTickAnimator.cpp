#include "TimerTickAnimator.h"

TimerTickAnimator::TimerTickAnimator(TickAnimation* _tick):tick(_tick), repetitions(0){
	
}

TimerTickAnimator::~TimerTickAnimator(void){

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