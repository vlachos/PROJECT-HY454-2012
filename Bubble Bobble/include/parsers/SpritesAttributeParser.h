#ifndef SPRITESATTRIBUTEPARSER_H
#define SPRITESATTRIBUTEPARSER_H

#include <vector>
#include <map>
#include <sstream>
#include "rapidxml.hpp"
#include "Metrics.h"

class SpritesAttributeParser{
	public:
		
		static void				SingletonCreate (const char * path) 
				{ singletonPtr = new SpritesAttributeParser(path); }
		static void				SingletonDestroy (void) 
				{ delete singletonPtr; singletonPtr = 0; }
		
		static  int GetAttribute(const char* id);

	private:
		typedef std::map< std::string, int > attributeMap;
		static SpritesAttributeParser*	singletonPtr;
		static const char *xmlFilePath;
		static attributeMap attributes;

		SpritesAttributeParser(const char * path);
		~SpritesAttributeParser(void);
};

#endif