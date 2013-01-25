#ifndef MOVINGPATHANIMATION_H
#define MOVINGPATHANIMATION_H

#include "Animation.h"
#include <vector>

typedef unsigned char frame_t;

struct PathEntry {
	offset_t dx, dy;
	frame_t frame;
	delay_t	delay;
	
	PathEntry (void) : dx(0), dy(0), frame(0xff), delay(0){}
	
	PathEntry (offset_t _dx, offset_t _dy, frame_t _frame, delay_t _delay) :
	dx(_dx), dy(_dy), frame(_frame),delay(_delay){}
   
	PathEntry (const PathEntry& p) :
	dx(p.dx), dy(p.dy), frame(p.frame),delay(p.delay){}
};

class MovingPathAnimation : public Animation{
	std::vector<PathEntry> path;
	int currIndex;
	bool continuous;
public:
	MovingPathAnimation (const std::vector<PathEntry> _path, animid_t id, bool c);
	~MovingPathAnimation(void);
	const std::vector<PathEntry>& GetPath (void) const;
    void SetPath (const std::vector<PathEntry>& p);
    Animation* Clone (animid_t newId) const;
	int GetCurrIndex(){return currIndex;}
	void SetCurrIndex(int index) { currIndex = index; }
	bool GetContinuous (void) const{return continuous;}
	void SetContinuous (bool v){ continuous = v;}
};

#endif