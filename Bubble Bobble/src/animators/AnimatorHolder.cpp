#include <algorithm>
#include <assert.h>
#include <iostream>
#include "AnimatorHolder.h"
#include "MemoryManage.h"

std::vector<Animator*> AnimatorHolder::running;
std::vector<Animator*> AnimatorHolder::suspended;

void AnimatorHolder :: Register (Animator* a){
	DASSERT(a);

	suspended.push_back(a); 
}
	
void AnimatorHolder :: Cancel (Animator* a){
	DASSERT(!suspended.empty());
	DASSERT(a);

	std::vector<Animator*>::iterator it = std::find(suspended.begin(), suspended.end(), a);
	DASSERT( it != suspended.end() ); 
	suspended.erase(it); 

}

void AnimatorHolder :: MarkAsRunning (Animator* a){
	DASSERT(!suspended.empty());
	DASSERT(a);

	std::vector<Animator*>::iterator it = std::find(suspended.begin(), suspended.end(), a);
	DASSERT( it != suspended.end() ); 
	suspended.erase(it); 

	running.push_back(a); 
}

void AnimatorHolder :: MarkAsSuspended (Animator* a){
	DASSERT(!running.empty());
	DASSERT(a);

	std::vector<Animator*>::iterator it = std::find(running.begin(), running.end(), a);
	DASSERT( it != running.end() ); 
	running.erase(it); 

	suspended.push_back(a); 
}

void AnimatorHolder :: Progress (timestamp_t currTime){
	DASSERT(currTime>=0);
	DASSERT(!running.empty());
	for (int i=0; i<running.size(); ++i)
		running[i]->Progress(currTime);
}


void AnimatorHolder :: Display(Bitmap at){

	for (int i=0; i<running.size(); ++i)
		running[i]->Display(at);
	
}


std::vector<Animator*> AnimatorHolder:: GetAnimators(enum animatorType_t type){
	std::vector<Animator*> animators;
	for(std::vector<Animator*>::const_iterator ci = running.begin(); ci != running.end(); ++ci){
		if( (*ci)->GetAnimatorType() == type )
			animators.push_back( *ci );
	}
	return animators;
}