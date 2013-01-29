#ifndef MOVINGPATHANIMATION_H
#define MOVINGPATHANIMATION_H

#include "Animation.h"
#include <vector>

typedef unsigned char frame_t;

struct PathEntry {
	int x, y;
	frame_t frame;
	delay_t	delay;
	
	PathEntry (void) : x(0), y(0), frame(0xff), delay(0){}
	
	PathEntry (int _x, int _y, frame_t _frame, delay_t _delay) :
	x(_x), y(_y), frame(_frame),delay(_delay){}
   
	PathEntry (const PathEntry& p) :
	x(p.x), y(p.y), frame(p.frame),delay(p.delay){}
};

class MovingPathAnimation : public Animation{
	std::vector<PathEntry> path;
	bool continuous;
public:
	MovingPathAnimation (const std::vector<PathEntry> _path, animid_t id, bool c);
	~MovingPathAnimation(void);
	const std::vector<PathEntry>& GetPath (void) const;
    void SetPath (const std::vector<PathEntry> p);
    Animation* Clone (animid_t newId) const;
	bool GetContinuous (void) const{return continuous;}
	void SetContinuous (bool v){ continuous = v;}
};

#endif