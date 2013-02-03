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

		enum animatorType_t GetAnimatorType(void)
			{ return timeTickAnimator_t; }
		
		void Start (timestamp_t t);
		TickAnimation* GetAnimation(void);
		void Progress (timestamp_t currTime);
		void Display(Bitmap at);
};

#endif