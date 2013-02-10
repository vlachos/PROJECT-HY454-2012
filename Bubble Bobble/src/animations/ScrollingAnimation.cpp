#include "ScrollingAnimation.h"

	ScrollingAnimation::ScrollingAnimation (const std::vector<ScrollEntry>& _scroll, animid_t id, bool c)
		:scroll(_scroll), Animation(id), continuous(c){
		DASSERT(!_scroll.empty());
		DASSERT(id>0);
	}
	ScrollingAnimation::ScrollingAnimation(void):Animation(1), continuous(false){
		for (unsigned int i=0; i<TILE_LAYER_STAGE_HEIGHT; ++i){
			scroll.push_back(ScrollEntry (HorizIntact, Down, 150) );
		}
	}

	ScrollingAnimation::~ScrollingAnimation (void){}


	Animation* ScrollingAnimation::Clone (animid_t newId) const{
		DASSERT(newId>0);
		return new ScrollingAnimation(scroll, newId, continuous);
	}

	void ScrollingAnimation::SetScroll (const std::vector<ScrollEntry>& p) { 
		DASSERT(!p.empty());
		DASSERT(!scroll.empty());
		scroll.clear();
		scroll = p;
	}

	const std::vector<ScrollEntry>& ScrollingAnimation :: GetScroll (void) const{
		DASSERT(!scroll.empty());
		return scroll; 
	}

	void ScrollingAnimation::SetContinuous (bool c){ continuous = c;}
	bool ScrollingAnimation::GetContinuous (void) const{return continuous;}

