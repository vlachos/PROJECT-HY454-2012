#ifndef INVISIBLESPRITES_H
#define INVISIBLESPRITES_H

#include <vector>
#include "Sprite.h"

namespace InvisibleSprites{

	typedef struct _InvisibleDrivers{
		Sprite* sprite;
		void (*callback)(Sprite *, Sprite *, void *);
		_InvisibleDrivers(Sprite* _sprite, void (*_callback)(Sprite *, Sprite *, void *))
			{ sprite = _sprite; callback = _callback; }
	}InvisibleDrivers;

	extern void CreateInvisibleDrivers();
	extern void DestroyInvisibleDrivers();

	extern std::vector<InvisibleDrivers> GetInvisibleBubbleDriversForFrameRange();
	extern std::vector<InvisibleDrivers> GetInvisibleWrapAroundDriversForFrameRange();
}
#endif