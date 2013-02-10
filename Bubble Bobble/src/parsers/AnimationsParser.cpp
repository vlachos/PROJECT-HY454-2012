#include "AnimationsParser.h"

#include <algorithm>
#include <fstream>
#include <list>
#include <string.h>
#include <stdlib.h>

#include "ParsersUtilities.h"
#include "MemoryManage.h"
#include "MovingAnimation.h"
#include "FrameRangeAnimation.h"
#include "FrameListAnimation.h"
#include "MovingPathAnimation.h"
#include "FlashAnimation.h"
#include "TickAnimation.h"

AnimationsParser*					AnimationsParser::singletonPtr;
AnimationsParser::animationsMap		AnimationsParser::map; 
AnimationsParser::animationsName	AnimationsParser::animName;
const char *						AnimationsParser::xmlFilePath;

namespace AnimationLoaderDelete{
	struct DeleteAnimation{
		void operator()(std::pair<std::string, Animation*> _pair){
			_pair.second->Destroy();
		}
	};
}

static Animation* GetCurrentAnimation(rapidxml::xml_node<>* anim){
	DASSERT( anim );

	DNEWPTR(rapidxml::xml_attribute<>, type);
	type = anim->first_attribute("type");
	DASSERT(type);

	DNEWPTR(char, strType);
	strType = type->value();
	DASSERT(strType);

	DNEWPTR(Animation, retVal);

	if( !strcmp(strType, "MovingAnimation") ){
		retVal = new MovingAnimation( GetGetIntAtrr( anim, "dx" ), GetGetIntAtrr( anim, "dy" ), 
								GetGetIntAtrr( anim, "delay" ), GetGetBoolAtrr( anim, "continue" ), 1);
	}else
	if( !strcmp(strType, "FrameRangeAnimation") ){
		retVal = new FrameRangeAnimation(GetGetIntAtrr( anim, "start" ), GetGetIntAtrr( anim, "end" ),
								GetGetIntAtrr( anim, "dx" ), GetGetIntAtrr( anim, "dy" ), 
								GetGetIntAtrr( anim, "delay" ), GetGetBoolAtrr( anim, "continue" ), 1);
	}else
	if( !strcmp(strType, "FrameListAnimation") ){		
		int _listSize = GetGetIntAtrr( anim, "listSize" );
		DASSERT( _listSize > 0 );
		
		std::list<frame_t> frames;
		int index=0;
		for ( rapidxml::xml_node<> * bbox = anim->first_node("list"); bbox; bbox = bbox->next_sibling(), ++index ) {
			frames.push_back( GetGetIntAtrr( bbox, "frame" ) );
		}
		DASSERT( index == _listSize && frames.size() == index);

		retVal = new FrameListAnimation( frames, GetGetIntAtrr( anim, "dx" ), GetGetIntAtrr( anim, "dy" ), 
								GetGetIntAtrr( anim, "delay" ), GetGetBoolAtrr( anim, "continue" ), 1);
	}else
	if( !strcmp(strType, "MovingPathAnimation") ){
		
		std::vector<PathEntry> paths;
		int index=0;

		for ( rapidxml::xml_node<> * bbox = anim->first_node("list"); bbox; bbox = bbox->next_sibling(), ++index ) {

			PathEntry pathentry( GetGetIntAtrr( bbox, "dx" ), GetGetIntAtrr( bbox, "dy" ),
								 GetGetIntAtrr( bbox, "frame" ), GetGetIntAtrr( bbox, "delay" ) );

			paths.push_back( pathentry );
		}

		retVal = new MovingPathAnimation( paths, 1, false);
	}else
	if( !strcmp(strType, "FlashAnimation") ){
		retVal = new FlashAnimation( GetGetIntAtrr( anim, "repetitions" ), GetGetIntAtrr( anim, "showDelay" ),
								 GetGetIntAtrr( anim, "hideDelay" ), 1 );
	}else
	if( !strcmp(strType, "TickAnimation") ){
		retVal = new TickAnimation( 1, GetGetIntAtrr( anim, "delay" ), GetGetIntAtrr( anim, "repetitions" ), 0, 0);
	}else
		DASSERT(false);

	DASSERT( retVal );
	return retVal;
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
		Animation* animation = GetCurrentAnimation( iterate );
		DASSERT( animation );
		animName.push_back( iterate->name() );
		map[ iterate->name() ] = animation;
	}
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
	return i->second->Clone(1);
}

AnimationsParser::animationsName::const_iterator AnimationsParser::GetAnimationsNameIteratorBegin(){
	return animName.begin();
}

AnimationsParser::animationsName::const_iterator AnimationsParser::GetAnimationsNameIteratorEnd(){
	return animName.end();
}