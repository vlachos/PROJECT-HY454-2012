#ifndef ANIMATORHOLDER_H
#define ANIMATORHOLDER_H

#include "Animator.h"
#include <list>

class AnimatorHolder{
	static std::list<Animator*> running, suspended;

public:
	static void Register (Animator* a);
	static void Cancel (Animator* a);
	static void MarkAsRunning (Animator* a);
	static void MarkAsSuspended (Animator* a);
	static void Progress (timestamp_t currTime);
};

#endif