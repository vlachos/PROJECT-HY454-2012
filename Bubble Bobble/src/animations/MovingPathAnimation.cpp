#include "MovingPathAnimation.h"
#include <assert.h>

MovingPathAnimation :: MovingPathAnimation (const std::list<PathEntry>& _path, animid_t id)
	:path(_path), Animation(id){
		assert(!_path.empty());
		assert(id);

}
	
const std::list<PathEntry>& MovingPathAnimation :: GetPath (void) const{
	assert(!path.empty());
	return path; 
}

void MovingPathAnimation :: SetPath (const std::list<PathEntry>& p){
	assert(!p.empty());
	assert(!path.empty());
	path.clear(); 
	path = p; 
}

Animation* MovingPathAnimation :: Clone (animid_t newId) const{ 
	assert(newId);
	return new MovingPathAnimation(path, newId); 
}