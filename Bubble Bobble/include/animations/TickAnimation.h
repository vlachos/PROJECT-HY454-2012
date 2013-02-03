#ifndef TICKANIMATION_H
#define TICKANIMATION_H

#include "Animation.h"

class TickAnimation : public Animation{
	public:
		typedef void (*TickFunc)(void* closure);
	private:
		delay_t		delay;
		byte		repetitions;
		TickFunc	action;
		void*		closure;
	public:
		TickAnimation(animid_t, delay_t, byte, TickFunc, void*);
		~TickAnimation();

		void NotifyTickAction (void);
		delay_t GetDelay (void) const;
		void SetDelay (delay_t v);
		byte GetRepetitions (void) const;
		void SetRepetitions (byte v);
};

#endif