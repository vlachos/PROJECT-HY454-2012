#include "ScrollingAnimator.h"

	ScrollingAnimator::ScrollingAnimator (void) 
		: actionLayer((TileLayer*) 0), anim((ScrollingAnimation*) 0), currIndex(0){  }
	ScrollingAnimator::~ScrollingAnimator(void) {  }

	ScrollingAnimation* ScrollingAnimator::GetAnimation(void) { return anim; }
	TileLayer* ScrollingAnimator::GetActionLayer(void) { return actionLayer; }


	void ScrollingAnimator::Progress (timestamp_t currTime){
		DASSERT(currIndex>=0 && currIndex< ((int)anim->GetScroll().size()));
		while (currTime > lastTime && currTime - lastTime >= anim->GetScroll()[currIndex].delay){

			actionLayer->Scroll(	
							anim->GetScroll()[currIndex].h, 
							anim->GetScroll()[currIndex].v
						);
		    lastTime += anim->GetScroll()[currIndex].delay;

			if (++currIndex == anim->GetScroll().size()){

				if( !anim->GetContinuous() ){
					state = ANIMATOR_FINISHED;
					NotifyStopped();
					return;
				}
				else{
					currIndex = 0;
				}
			}
		}
		DASSERT(currIndex>=0 && currIndex<((int)anim->GetScroll().size()));
	}
	
	void ScrollingAnimator::Start (TileLayer* aLayer, ScrollingAnimation* anim, timestamp_t t){
		DASSERT(aLayer);
		DASSERT(anim);
		DASSERT(t>=0);

		actionLayer = aLayer;
		anim = anim;
		lastTime = t;
		state = ANIMATOR_RUNNING;
	}

	void ScrollingAnimator::Display(Bitmap at) {  }