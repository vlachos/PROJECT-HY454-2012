
#ifndef	SPRITESPARSER_H
#define	SPRITESPARSER_H

#include <vector>
#include <map>
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
		typedef std::map< std::string, std::vector<Rect> > spritesMap;
		typedef std::vector<std::string> spritesName;
		static void				SingletonCreate (const char * path) 
				{ singletonPtr = new SpriteParser(path); }
		static void				SingletonDestroy (void) 
				{ delete singletonPtr; singletonPtr = 0; }
		

		static std::vector<Rect> GetSprite(const std::string & id);
		static std::string GetBitmapName(const std::string & id);
		static int GetTotalSprites();

		static spritesName::const_iterator GetSpritesNameIteratorBegin();
		static spritesName::const_iterator GetSpritesNameIteratorEnd();

	private:
		static SpriteParser*	singletonPtr;
		static spritesMap map; 
		static spritesName SpritesName;
		static const char *xmlFilePath;
		static std::string bitmapName;

		SpriteParser(const char * path);
		~SpriteParser(void);
};

#endif