#include "MovingPathAnimation.h"

MovingPathAnimation :: MovingPathAnimation (const std::list<PathEntry>& _path, animid_t id)
	:path(_path), Animation(id){}
	
const std::list<PathEntry>& MovingPathAnimation :: GetPath (void) const { 
	return path; 
}

void MovingPathAnimation :: SetPath (const std::list<PathEntry>& p) { 
	path.clear(); 
	path = p; 
}

Animation* MovingPathAnimation :: Clone (animid_t newId) const{ 
	return new MovingPathAnimation(path, newId); 
}