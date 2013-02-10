#ifndef SCROLLINGANIMATION_H
#define SCROLLINGANIMATION_H

#include "Animation.h"
#include "TileLayer.h"
#include "TerrainUtilities.h"
#include <vector>

struct ScrollEntry{
	HorizScroll h;
	VertScroll v;
	delay_t delay;

	ScrollEntry (void) : h(HorizIntact), v(VertIntact), delay(0){}
	
	ScrollEntry (HorizScroll _h, VertScroll _v, delay_t _delay) :
	h(_h), v(_v), delay(_delay){}
   
	ScrollEntry (const ScrollEntry& scr) :
	h(scr.h), v(scr.v), delay(scr.delay){}
};

class ScrollingAnimation : public Animation {
	private:
		std::vector<ScrollEntry> scroll;
		bool continuous;

	public:
		ScrollingAnimation (const std::vector<ScrollEntry>& _scroll, animid_t id, bool c);
		~ScrollingAnimation (void);

	public:
		Animation* Clone (animid_t newId) const;
		void SetScroll (const std::vector<ScrollEntry>& p);
		const std::vector<ScrollEntry>& GetScroll (void) const;
		bool GetContinuous (void) const;
		void SetContinuous (bool c);

};

#endif