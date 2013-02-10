#include "StageStartingAttributesParser.h"

#include <algorithm>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "ParsersUtilities.h"

StageStartingAttributesParser::attributeStages		StageStartingAttributesParser::attributes;
StageStartingAttributesParser*						StageStartingAttributesParser::singletonPtr;
const char *										StageStartingAttributesParser::xmlFilePath;


static StartingAttributes_t getNewAttribute( rapidxml::xml_node<>* node ){
	return std::make_pair( 
							std::make_pair( 
											GetGetIntAtrr( node, "x" ), 
											GetGetIntAtrr( node, "y" )
										  ), 
							std::make_pair( 
											GetGetBoolAtrr( node, "gravityAddict" ), 
											GetGetBoolAtrr( node, "goesLeft" )
										  ) 
						 );
}

StageStartingAttributesParser::StageStartingAttributesParser(const char * path){
	xmlFilePath = path;
	rapidxml::xml_document<> doc;
	//open path and read
	std::ifstream theFile (xmlFilePath);
	std::vector<char> buffer = std::vector<char>((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	//parse
	doc.parse<0>( &buffer[0] );

	DNEWPTR( rapidxml::xml_node<>, rootNode);
	rootNode = doc.first_node("StartingSprites");
	DASSERT( rootNode );

	int totealStages = GetGetIntAtrr( rootNode, "totalStages" );
	DASSERT(totealStages>0);

	attributes.resize(totealStages);

	int stages = 0;
	attributeMap attrMap;
	for(rapidxml::xml_node<>* stagesIterate = rootNode->first_node(); stagesIterate; stagesIterate = stagesIterate->next_sibling()){
		int currStage = GetGetIntAtrr( stagesIterate, "stageNum" );
		DASSERT( currStage == ++stages);

		attrMap.clear();

		std::list<StartingAttributes_t> charAttrs;
		charAttrs.push_front(getNewAttribute( stagesIterate->first_node("BubXY") ));
		attrMap["BubXY"] = charAttrs;

		charAttrs.clear();
		charAttrs.push_front(getNewAttribute( stagesIterate->first_node("BobXY") ));
		attrMap["BobXY"] = charAttrs;

		charAttrs.clear();
		for(rapidxml::xml_node<>* charAttrsIterate = stagesIterate->first_node("ZenChanXY")->first_node(); charAttrsIterate; charAttrsIterate = charAttrsIterate->next_sibling()){
			charAttrs.push_front(getNewAttribute( charAttrsIterate ));
		}
		attrMap["ZenChanXY"] = charAttrs;

		charAttrs.clear();
		for(rapidxml::xml_node<>* charAttrsIterate = stagesIterate->first_node("MightaXY")->first_node(); charAttrsIterate; charAttrsIterate = charAttrsIterate->next_sibling()){
			charAttrs.push_front(getNewAttribute( charAttrsIterate ));
		}
		attrMap["MightaXY"] = charAttrs;

		charAttrs.clear();
		for(rapidxml::xml_node<>* charAttrsIterate = stagesIterate->first_node("PowerUpXY")->first_node(); charAttrsIterate; charAttrsIterate = charAttrsIterate->next_sibling()){
			charAttrs.push_front(getNewAttribute( charAttrsIterate ));
		}
		attrMap["PowerUpXY"] = charAttrs;

		attributes[stages-1] = attrMap;
	}
}

StageStartingAttributesParser::~StageStartingAttributesParser(){
	std::for_each(	
					attributes.begin(),
					attributes.end(),
					DeleteAttribute() 
				);

	attributes.clear();
	unullify( xmlFilePath );
}

std::list<StartingAttributes_t> StageStartingAttributesParser::GetZenChanStartingAttribute(unsigned int stageNum){
	DASSERT( stageNum<attributes.size() );
	return attributes[stageNum]["ZenChanXY"];
}

std::list<StartingAttributes_t> StageStartingAttributesParser::GetMightaStartingAttribute(unsigned int stageNum){
	DASSERT( stageNum<attributes.size() );
	return attributes[stageNum]["MightaXY"];
}

StartingAttributes_t StageStartingAttributesParser::GetBubStartingAttribute(unsigned int stageNum){
	DASSERT( stageNum<attributes.size() );
	std::list<StartingAttributes_t> bub = attributes[stageNum]["BubXY"];
	DASSERT(bub.size()==1);
	return bub.front();
}

StartingAttributes_t StageStartingAttributesParser::GetBobStartingAttribute(unsigned int stageNum){
	DASSERT( stageNum<attributes.size() );
	std::list<StartingAttributes_t> bob = attributes[stageNum]["BobXY"];
	DASSERT(bob.size()==1);
	return bob.front();
}

std::list<StartingAttributes_t> StageStartingAttributesParser::GetPowerUpStartingAttribute(unsigned int stageNum){
	DASSERT( stageNum<attributes.size() );
	return attributes[stageNum]["PowerUpXY"];
}
