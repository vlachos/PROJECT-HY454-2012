#ifndef	SPRITESPARSER_H
#define	SPRITESPARSER_H

#include "rapidxml.hpp"
#include <vector>

namespace spriteParserSpecifications {

	enum spritesSize {
		spritesSize_sixteen		= 0,
		spritesSize_thirtytwo	= 1,
		spritesSize_sixtyfour	= 2
	};

	static char * strspritesSize [3] = {
		"16x16",
		"32x32",
		"64x64"
	};

}

class SpriteParser{
	public:
		static void				SingletonCreate (void) { singletonPtr = new SpriteParser; }
		static void				SingletonDestroy (void) { delete singletonPtr; singletonPtr = 0; }
		
		//i will do it std::vector<Rect>, when we create Rect!
		static std::vector<char> * getSprite(const std::string& id);

	private:
		static SpriteParser*	singletonPtr;
		static rapidxml::xml_node<> * root_node;
		static std::vector<char> buffer;
		static int spritesSize;

		SpriteParser(void);
		~SpriteParser(void);
};

#endif