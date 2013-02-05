#ifndef INVISIBLESPRITES_H
#define INVISIBLESPRITES_H

#include <vector>
#include "Sprite.h"

class InvisibleSprites{
	public:
		typedef struct _InvisibleDrivers{
			Sprite* sprite;
			void (*callback)(Sprite *, Sprite *, void *);
			_InvisibleDrivers(Sprite* _sprite, void (*_callback)(Sprite *, Sprite *, void *))
				{ sprite = _sprite; callback = _callback; }
		}InvisibleDrivers;

		static void	SingletonCreate () { singletonPtr = new InvisibleSprites(); }
		static void	SingletonDestroy (void) { delete singletonPtr; singletonPtr = 0; }

		static std::vector<InvisibleDrivers> GetInvisibleBubbleDriversForFrameRange();
		static std::vector<InvisibleDrivers> GetInvisibleWrapAroundDrivers();

	private:
		static InvisibleSprites*	singletonPtr;
		static std::vector<InvisibleDrivers> driversForFrameRange;
		static std::vector<InvisibleDrivers> wrapAroundDrivers;

		InvisibleSprites();
		~InvisibleSprites();
};
#endif