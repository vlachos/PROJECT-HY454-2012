#include <algorithm>
#include <assert.h>
#include <iostream>
#include "AnimatorHolder.h"
#include "MemoryManage.h"

std::list<Animator*> AnimatorHolder::running;
std::list<Animator*> AnimatorHolder::suspended;

void AnimatorHolder :: Register (Animator* a){
	DASSERT(a);

	suspended.push_back(a); 
}
	
void AnimatorHolder :: Cancel (Animator* a){
	DASSERT(!suspended.empty());
	DASSERT(a);

	suspended.remove(a); 
}

void AnimatorHolder :: MarkAsRunning (Animator* a){
	DASSERT(!suspended.empty());
	DASSERT(a);

	suspended.remove(a); running.push_back(a); 
}

void AnimatorHolder :: MarkAsSuspended (Animator* a){
	DASSERT(!running.empty());
	DASSERT(a);

	running.remove(a); suspended.push_back(a); 
}

void AnimatorHolder :: Progress (timestamp_t currTime){
	DASSERT(currTime>=0);
	DASSERT(!running.empty());

	for (std::list<Animator*>::iterator it = running.begin(); it != running.end(); it++)
		(*it)->Progress(currTime);
}


void AnimatorHolder :: Display(Bitmap at){
	for (std::list<Animator*>::iterator it = running.begin(); it != running.end(); it++){
		(*it)->Display(at);
	}
}
