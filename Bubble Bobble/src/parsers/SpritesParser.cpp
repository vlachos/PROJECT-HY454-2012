#include "SpritesParser.h"

#include <algorithm>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "MemoryManage.h"
#include "Metrics.h"

#define ALIGN_SIZE(a, s) ( (a) << (s) )

const char *				SpriteParser::xmlFilePath;
SpriteParser *				SpriteParser::singletonPtr;
std::string					SpriteParser::bitmapName;
SpriteParser::spritesMap	SpriteParser::map;
SpriteParser::spritesName	SpriteParser::SpritesName;


static std::vector<Rect> GetCurrentSprite(rapidxml::xml_node<>* current, byte spritesSize){
	DASSERT( current && spritesSize>=0 );
	int totalFrames;
	std::vector<Rect> rects;

	DNEWPTR( char,  _totalFrames);
	_totalFrames = current->first_attribute("frames")->value();
	DASSERT( _totalFrames );
		
	totalFrames = atoi( _totalFrames );
	DASSERT( totalFrames > 0 );

	int index=0;
	for ( rapidxml::xml_node<> * bbox = current->first_node("bbox"); bbox; bbox = bbox->next_sibling(), ++index ) {

		DNEWPTR(rapidxml::xml_attribute<>, currBox);
		currBox = bbox->first_attribute("box");

		DNEWPTR(rapidxml::xml_attribute<>, dx);
		dx = bbox->first_attribute("x");
			
		DNEWPTR(rapidxml::xml_attribute<>, dy);
		dy = bbox->first_attribute("y");

		DNEWPTR(rapidxml::xml_attribute<>, h);
		h = bbox->first_attribute("h");

		DNEWPTR(rapidxml::xml_attribute<>, w);
		w = bbox->first_attribute("w");

		DASSERT( dx && dx->value() && dy && dy->value() && h && h->value() && w && w->value() );
		Rect rect( ALIGN_SIZE( StringToDim( dx->value() ), spritesSize ), ALIGN_SIZE( StringToDim( dy->value()), spritesSize ), 
					ALIGN_SIZE( StringToDim( h->value() ), spritesSize ), ALIGN_SIZE(  StringToDim( w->value()), spritesSize ) );
		rects.push_back( rect );
	}
	DASSERT( index == totalFrames && rects.size() == index);
	

	return rects;
}


SpriteParser::SpriteParser(const char * path){
	
	xmlFilePath = path;
	rapidxml::xml_document<> doc;
	//open path and read
	std::ifstream theFile (xmlFilePath);
	std::vector<char> buffer = std::vector<char>((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	//parse
	doc.parse<0>( &buffer[0] );

	DNEWPTR( rapidxml::xml_node<>, rootNode);
	rootNode = doc.first_node("sprites");
	DASSERT( rootNode );

	DNEWPTR( const char, s );
	s = rootNode->first_attribute("format")->value();
	DASSERT( s );

	DNEWPTR( char,  _totalSpritesNum );
	_totalSpritesNum = rootNode->first_attribute("totalSprites")->value();
	DASSERT( _totalSpritesNum );

	byte totalSpritesNum = atoi( _totalSpritesNum );
	DASSERT( totalSpritesNum > 0 );

	DNEWPTR( char, _bitmapName );
	_bitmapName = rootNode->first_attribute("bitmap")->value();
	DASSERT(_bitmapName);

	bitmapName = std::string( _bitmapName );

	using namespace SpriteParserSpecifications;

	byte spritesSize;
	if(!strcmp(s, strSpritesSize[ EnumToInt( spritesSize_sixteen ) ])){
		spritesSize = EnumToInt( spritesSize_sixteen );
	}else
	if(!strcmp(s, strSpritesSize[ EnumToInt( spritesSize_thirtytwo ) ])){
		spritesSize = EnumToInt( spritesSize_thirtytwo );
	}else
	if(!strcmp(s, strSpritesSize[ EnumToInt( spritesSize_sixtyfour ) ])){
		spritesSize = EnumToInt( spritesSize_sixtyfour );
	}else
		DASSERT(false);

	for(rapidxml::xml_node<>* iterate = rootNode->first_node(); iterate; iterate = iterate->next_sibling()){
		std::vector<Rect> currBbox = GetCurrentSprite(iterate, spritesSize);
		DASSERT( !currBbox.empty() );
		SpritesName.push_back( iterate->name() );
		map[ iterate->name() ] = currBbox;
	}

	DASSERT( SpritesName.size() == totalSpritesNum && map.size() == totalSpritesNum );
}

SpriteParser::~SpriteParser(void){
	DASSERT( !bitmapName.empty() && !SpritesName.empty() && !map.empty() && xmlFilePath );

	unullify( xmlFilePath );
	bitmapName.clear();
	SpritesName.clear();
	map.clear();
}

std::string SpriteParser::GetBitmapName(const std::string & id){
	return 	bitmapName;
}

std::vector<Rect> SpriteParser::GetSprite(const std::string & id){
	SpriteParser::spritesMap::const_iterator i = map.find(id);
	DASSERT( i!=map.end() );
	return i->second;
}


int SpriteParser::GetTotalSprites(){
	DASSERT( SpritesName.size()>0 );
	return SpritesName.size();
}

SpriteParser::spritesName::const_iterator SpriteParser::GetSpritesNameIteratorBegin(){
	return SpritesName.begin();
}

SpriteParser::spritesName::const_iterator SpriteParser::GetSpritesNameIteratorEnd(){
	return SpritesName.end();
}