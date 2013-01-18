#include "MovingPathAnimation.h"
#include "MemoryManage.h"

MovingPathAnimation :: MovingPathAnimation (const std::list<PathEntry>& _path, animid_t id)
	:path(_path), Animation(id){
		DASSERT(!_path.empty());
		DASSERT(id);

}
	
const std::list<PathEntry>& MovingPathAnimation :: GetPath (void) const{
	DASSERT(!path.empty());
	return path; 
}

void MovingPathAnimation :: SetPath (const std::list<PathEntry>& p){
	DASSERT(!p.empty());
	DASSERT(!path.empty());
	path.clear(); 
	path = p; 
}

Animation* MovingPathAnimation :: Clone (animid_t newId) const{ 
	DASSERT(newId);
	return new MovingPathAnimation(path, newId); 
}