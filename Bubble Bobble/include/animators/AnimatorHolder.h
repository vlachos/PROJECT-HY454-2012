#ifndef ANIMATORHOLDER_H
#define ANIMATORHOLDER_H

#include "utilities.h"
#include "Animator.h"
#include <vector>

class AnimatorHolder{
	static std::vector<Animator*> running, suspended;

public:
	static void Register (Animator* a);
	static void Cancel (Animator* a);
	static void MarkAsRunning (Animator* a);
	static void MarkAsSuspended (Animator* a);
	static void Progress (timestamp_t currTime);
	static void Display(Bitmap at);
	static std::vector<Animator*> GetAnimators(enum animatorType_t);
	static std::vector<Animator*> GetAnimators(animatorType_t start, animatorType_t end);
};

#endif