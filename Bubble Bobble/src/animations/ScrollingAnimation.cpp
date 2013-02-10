#include "ScrollingAnimation.h"

	ScrollingAnimation::ScrollingAnimation (const std::vector<ScrollEntry>& _scroll, animid_t id, bool c)
		:scroll(_scroll), Animation(id), continuous(c){
		DASSERT(!_scroll.empty());
		DASSERT(id>0);
	}
	ScrollingAnimation::~ScrollingAnimation (void){}


	Animation* ScrollingAnimation::Clone (animid_t newId) const{
		DASSERT(newId>0);
		return new ScrollingAnimation(scroll, newId, continuous);
	}

	void ScrollingAnimation::SetScroll (const std::vector<ScrollEntry>& p) { 
		scroll.clear();
		scroll = p;
	}

	const std::vector<ScrollEntry>& ScrollingAnimation :: GetScroll (void) const{
		DASSERT(!scroll.empty());
		return scroll; 
	}

	void ScrollingAnimation::SetContinuous (bool c){ continuous = c;}
	bool ScrollingAnimation::GetContinuous (void) const{return continuous;}

