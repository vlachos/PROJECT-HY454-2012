#include "MovingPathAnimation.h"
#include "MemoryManage.h"

MovingPathAnimation :: MovingPathAnimation (const std::vector<PathEntry> _path, animid_t id, bool c)
	:path(_path), Animation(id),continuous(c){
		DASSERT(!_path.empty());
		DASSERT(id>0);

}

MovingPathAnimation :: ~MovingPathAnimation(void){
	path.clear();
}
	
const std::vector<PathEntry>& MovingPathAnimation :: GetPath (void) const{
	DASSERT(!path.empty());
	return path; 
}

void MovingPathAnimation :: SetPath (const std::vector<PathEntry> p){
	DASSERT(!p.empty());
	DASSERT(!path.empty());
	path.clear(); 
	path = p; 
}

Animation* MovingPathAnimation :: Clone (animid_t newId) const{ 
	DASSERT(newId>0);
	return new MovingPathAnimation(path, newId, continuous); 
}