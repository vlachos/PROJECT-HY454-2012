#include "MemoryManage.h"
#include <iostream>

#include <algorithm>

/////////////LatelyDestroyable

std::list<LatelyDestroyable*> DestructionManager::dead;

void LatelyDestroyable::Delete::operator()(LatelyDestroyable* o) const
	{ o->inDestruction = true; delete o;}

void DestructionManager::Register (LatelyDestroyable* o) {
	assert(!o->IsAlive()); 
	dead.push_back(o); 
} 

void DestructionManager::Commit (void) {
	
	std::for_each(
		dead.begin(), 
		dead.end(), 
		LatelyDestroyable::Delete()
	); 
	
	dead.clear();
}
