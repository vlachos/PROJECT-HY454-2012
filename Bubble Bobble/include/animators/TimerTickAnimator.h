#ifndef TIMERTICKANIMATOR_H
#define TIMERTICKANIMATOR_H

#include "Animator.h"
#include "TickAnimation.h"

class TimerTickAnimator : public Animator{
	private:
		TickAnimation*	tick;
		byte			repetitions;
	public:
		TimerTickAnimator(TickAnimation* _tick);
		~TimerTickAnimator(void);
		void Progress (timestamp_t currTime);
};

#endif