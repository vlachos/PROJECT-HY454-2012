#include "AnimatorHolder.h"
#include <algorithm>
#include <assert.h>

std::list<Animator*> AnimatorHolder::running;
std::list<Animator*> AnimatorHolder::suspended;

void AnimatorHolder :: Register (Animator* a){
	assert(!suspended.empty());
	assert(a);

	suspended.push_back(a); 
}
	
void AnimatorHolder :: Cancel (Animator* a){
	assert(!suspended.empty());
	assert(a);

	suspended.remove(a); 
}

void AnimatorHolder :: MarkAsRunning (Animator* a){
	assert(!suspended.empty());
	assert(!running.empty());
	assert(a);

	suspended.remove(a); running.push_back(a); 
}

void AnimatorHolder :: MarkAsSuspended (Animator* a){
	assert(!suspended.empty());
	assert(!running.empty());
	assert(a);

	running.remove(a); suspended.push_back(a); 
}

void AnimatorHolder :: Progress (timestamp_t currTime){
	assert(currTime);
	assert(!running.empty());

	for (std::list<Animator*>::iterator it = running.begin(); it != running.end(); it++)
		(*it)->Progress(currTime);
}