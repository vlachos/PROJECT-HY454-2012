#include "Animation.h"
#include "MemoryManage.h"

Animation :: Animation (animid_t _id) : id(_id) {
	DASSERT(_id>0);
}

animid_t Animation :: GetId (void) {
	DASSERT(id>0);
	return id; 
}

Animation :: ~Animation() {
}