#ifndef	ANIMATIONSPARSER_H
#define	ANIMATIONSPARSER_H

#include <vector>
#include <map>
#include <sstream>

#include "rapidxml.hpp"
#include "Metrics.h"
#include "Animation.h"

class AnimationsParser{
	public:
		typedef std::map< std::string, Animation* > animationsMap;
		typedef std::vector<std::string> animationsName;
		static void				SingletonCreate (const char * path) 
				{ singletonPtr = new AnimationsParser(path); }
		static void				SingletonDestroy (void) 
				{ delete singletonPtr; singletonPtr = 0; }
		

		static Animation* GetAnimation(const std::string & id);

		static animationsName::const_iterator GetAnimationsNameIteratorBegin();
		static animationsName::const_iterator GetAnimationsNameIteratorEnd();

	private:
		static AnimationsParser*	singletonPtr;
		static animationsMap map; 
		static animationsName animName;
		static const char *xmlFilePath;

		AnimationsParser(const char * path);
		~AnimationsParser(void);
};


#endif