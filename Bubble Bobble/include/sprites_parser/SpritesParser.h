#ifndef	SPRITESPARSER_H
#define	SPRITESPARSER_H

#include "rapidxml.hpp"
#include <vector>

namespace SpriteParserSpecifications {

	enum SpritesSize {
		spritesSize_sixteen		= 0,
		spritesSize_thirtytwo	= 1,
		spritesSize_sixtyfour	= 2
	};

	static char * strSpritesSize [3] = {
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
		static std::vector<char> * GetSprite(const std::string& id);

	private:
		static SpriteParser*	singletonPtr;
		static rapidxml::xml_node<> * rootNode;
		static std::vector<char> buffer;
		static int spritesSize;

		SpriteParser(void);
		~SpriteParser(void);
};

#endif