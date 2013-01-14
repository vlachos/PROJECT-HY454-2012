#include "Animation.h"
#include <assert.h>

Animation :: Animation (animid_t _id) : id(_id) {
	assert(_id>=0);
}

animid_t Animation :: GetId (void) {
	assert(id>=0);
	return id; 
}

Animation :: ~Animation() {
}