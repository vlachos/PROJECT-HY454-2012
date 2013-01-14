#ifndef MOVINGPATHANIMATION_H
#define MOVINGPATHANIMATION_H

#include "Animation.h"
#include <list>

typedef unsigned char frame_t;

struct PathEntry {
    offset_t dx, dy;
    frame_t frame;
    delay_t	delay;
    PathEntry (void) : dx(0), dy(0), frame(0xff), delay(0){}
    PathEntry (const PathEntry& p) :
	dx(p.dx), dy(p.dy), frame(p.frame),delay(p.delay){}
};

class MovingPathAnimation : public Animation{
	std::list<PathEntry> path;

public:
	MovingPathAnimation (const std::list<PathEntry>& _path, animid_t id);
	const std::list<PathEntry>& GetPath (void) const;
    void SetPath (const std::list<PathEntry>& p);
    Animation* Clone (animid_t newId) const;
};

#endif