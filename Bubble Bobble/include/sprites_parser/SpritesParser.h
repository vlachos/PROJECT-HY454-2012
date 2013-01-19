#ifndef	SPRITESPARSER_H
#define	SPRITESPARSER_H

#include <vector>
#include <sstream>

#include "rapidxml.hpp"
#include "Metrics.h"

namespace SpriteParserSpecifications {

	enum SpritesSize {
		spritesSize_sixteen		= 0,
		spritesSize_thirtytwo	= 1,
		spritesSize_sixtyfour	= 2
	};

	template <typename T>
	  int EnumToInt ( T t ){
		 return ( int ) t;
	}

	static char * strSpritesSize [3] = {
		"16x16",
		"32x32",
		"64x64"
	};

}

class SpriteParser{
	public:

		static void				SingletonCreate (const char * path) 
				{ singletonPtr = new SpriteParser(path); }
		static void				SingletonDestroy (void) 
				{ delete singletonPtr; singletonPtr = 0; }
		

		static std::vector<Rect> GetSprite(const std::string & id);
		static std::string GetBitmapName(const std::string & id);
		static int GetTotalSprites();

	private:
		static SpriteParser*	singletonPtr;
		static rapidxml::xml_node<> * rootNode;
		static std::vector<char> buffer;
		static const char *xmlFilePath;
		static std::string bitmapName;
		static int spritesSize;
		static int totalSprites;

		SpriteParser(const char * path);
		~SpriteParser(void);

	public:
		class SpriteParserIterator{

			private:
				static rapidxml::xml_node<> * iteratorSpriteNode;
				static int remainningSprites;

			public:
				static void StartIterator();
				static bool HasNext(void);
				static char * GetNext(void);
		};
};

#endif