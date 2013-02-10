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
		typedef enum _directionDrive{
			directionDrive_Up,
			directionDrive_Down,
			directionDrive_Left,
			directionDrive_Right
		}directionDrive;
		typedef struct StartingPosition{
			int x;
			int y;
			int w;
			int h;
			directionDrive d;
			StartingPosition(int _x, int _y, int _w, int _h, directionDrive _d):x(_x), y(_y), w(_w), h(_h), d(_d){}
		}StartingPosition_t;

		typedef std::map< std::string, std::list<StartingAttributes_t> > attributeMap;
		typedef std::map< std::string, std::list<StartingPosition_t> > positionMap;
		typedef std::vector< attributeMap > attributeStages;
		typedef std::vector< positionMap > positionStages;	

		static void				SingletonCreate (const char * path) 
				{ singletonPtr = new StageStartingAttributesParser(path); }
		static void				SingletonDestroy (void) 
				{ delete singletonPtr; singletonPtr = 0; }
		
		static  std::list<StartingAttributes_t> GetZenChanStartingAttribute(unsigned int stageNum);
		static  std::list<StartingAttributes_t> GetMightaStartingAttribute(unsigned int stageNum);
		static  StartingAttributes_t GetBubStartingAttribute(unsigned int stageNum);
		static  StartingAttributes_t GetBobStartingAttribute(unsigned int stageNum);
		static  std::list<StartingAttributes_t> GetPowerUpStartingAttribute(unsigned int stageNum);

		static  std::list<StartingPosition_t> GetInvisibleSpritesPos(unsigned int stageNum);

	private:

		static StageStartingAttributesParser*	singletonPtr;
		static const char *xmlFilePath;
		static attributeStages attributes;
		static positionStages positions;

		struct DeleteAttribute{
			void operator()(attributeMap map){
				map.clear();
			}
		};

		StageStartingAttributesParser(const char * path);
		~StageStartingAttributesParser(void);
};

#endif