#include "AnimatorHolder.h"
#include <algorithm>

std::list<Animator*> AnimatorHolder::running;
std::list<Animator*> AnimatorHolder::suspended;

void AnimatorHolder :: Register (Animator* a) { 
	suspended.push_back(a); 
}
	
void AnimatorHolder :: Cancel (Animator* a) { 
	suspended.remove(a); 
}

void AnimatorHolder :: MarkAsRunning (Animator* a){ 
	suspended.remove(a); running.push_back(a); 
}

void AnimatorHolder :: MarkAsSuspended (Animator* a){ 
	running.remove(a); suspended.push_back(a); 
}

void AnimatorHolder :: Progress (timestamp_t currTime) {
	for (std::list<Animator*>::iterator it = running.begin(); it != running.end(); it++)
		(*it)->Progress(currTime);
}