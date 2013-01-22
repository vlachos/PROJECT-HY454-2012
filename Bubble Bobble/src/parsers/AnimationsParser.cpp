#include "AnimationsParser.h"

#include <algorithm>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "MemoryManage.h"
#include "Metrics.h"

AnimationsParser*					AnimationsParser::singletonPtr;
AnimationsParser::animationsMap		AnimationsParser::map; 
AnimationsParser::animationsName	AnimationsParser::animName;
const char *						AnimationsParser::xmlFilePath;


namespace AnimationLoaderDelete{

	struct DeleteAnimation{
		void operator()(std::pair<std::string, Animation*> _pair){
			delete _pair.second;
		}
	};

}


static Animation* GetCurrentAnimation(rapidxml::xml_node<>* anim){
	return 0;
}

AnimationsParser::AnimationsParser(const char * path){

	xmlFilePath = path;
	rapidxml::xml_document<> doc;
	//open path and read
	std::ifstream theFile (xmlFilePath);
	std::vector<char> buffer = std::vector<char>((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	//parse
	doc.parse<0>( &buffer[0] );

	DNEWPTR( rapidxml::xml_node<>, rootNode);
	rootNode = doc.first_node("animations");
	DASSERT( rootNode );

	DNEWPTR( char,  _totalSpritesNum );
	_totalSpritesNum = rootNode->first_attribute("totalAnimations")->value();
	DASSERT( _totalSpritesNum );

	unsigned int totalAnimations = atoi( _totalSpritesNum );
	DASSERT( totalAnimations > 0 );

	for(rapidxml::xml_node<>* iterate = rootNode->first_node(); iterate; iterate = iterate->next_sibling()){
		Animation* animation = GetCurrentAnimation(iterate);
		DASSERT( animation );
		animName.push_back( iterate->name() );
		map[ iterate->name() ] = animation;
	}

	DASSERT( animName.size() == totalAnimations && map.size() == totalAnimations );
}



AnimationsParser::~AnimationsParser(){
	std::for_each( map.begin(),
         map.end(),
		 AnimationLoaderDelete::DeleteAnimation() );

	map.clear();
	animName.clear();
	unullify( xmlFilePath );
}

Animation * AnimationsParser::GetAnimation(const std::string & id){
	AnimationsParser::animationsMap::const_iterator i = map.find(id);
	DASSERT( i!=map.end() );
	return i->second->Clone(0);
}

AnimationsParser::animationsName::const_iterator AnimationsParser::GetAnimationsNameIteratorBegin(){
	return animName.begin();
}

AnimationsParser::animationsName::const_iterator AnimationsParser::GetAnimationsNameIteratorEnd(){
	return animName.end();
}