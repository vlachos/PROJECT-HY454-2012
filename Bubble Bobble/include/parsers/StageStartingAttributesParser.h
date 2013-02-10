#ifndef STAGESTARTINGATTRIBUTESPARSER_H
#define STAGESTARTINGATTRIBUTESPARSER_H

#include <vector>
#include <list>
#include <map>
#include <sstream>

#include "rapidxml.hpp"
#include "Metrics.h"

class StageStartingAttributesParser{
	public:
		
		static void				SingletonCreate (const char * path) 
				{ singletonPtr = new StageStartingAttributesParser(path); }
		static void				SingletonDestroy (void) 
				{ delete singletonPtr; singletonPtr = 0; }
		
		static  std::list<StartingAttributes_t> GetZenChanStartingAttribute(unsigned int stageNum);
		static  std::list<StartingAttributes_t> GetMightaStartingAttribute(unsigned int stageNum);
		static  StartingAttributes_t GetBubStartingAttribute(unsigned int stageNum);
		static  StartingAttributes_t GetBobStartingAttribute(unsigned int stageNum);
		static  std::list<StartingAttributes_t> GetPowerUpStartingAttribute(unsigned int stageNum);

	private:
		typedef std::map< std::string, std::list<StartingAttributes_t> > attributeMap;
		typedef std::vector< attributeMap > attributeStages;
		static StageStartingAttributesParser*	singletonPtr;
		static const char *xmlFilePath;
		static attributeStages attributes;

		struct DeleteAttribute{
			void operator()(attributeMap map){
				map.clear();
			}
		};

		StageStartingAttributesParser(const char * path);
		~StageStartingAttributesParser(void);
};

#endif