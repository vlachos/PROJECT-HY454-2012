#include "SpritesParser.h"

#include <algorithm>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "MemoryManage.h"

#define ALIGN_SIZE(a, s) ( (a) << (s) )

const char *				SpriteParser::xmlFilePath;
SpriteParser *				SpriteParser::singletonPtr;
std::string					SpriteParser::bitmapName;
SpriteParser::spritesMap	SpriteParser::map;
SpriteParser::spritesName	SpriteParser::SpritesName;

static int GetGetIntAtrr(rapidxml::xml_node<>* anim, const char * atrr ){				
	rapidxml::xml_attribute<>* getter = anim->first_attribute(atrr);	
	DASSERT( getter );						
	return atoi( getter->value() );
}

static char * GetGetStringAtrr(rapidxml::xml_node<>* anim, const char * atrr ){				
	rapidxml::xml_attribute<>* getter = anim->first_attribute(atrr);	
	DASSERT( getter );
	char * getVal = getter->value();
	DASSERT( getVal );
	return getVal;
}

static std::vector<Rect> GetCurrentSprite(rapidxml::xml_node<>* current, byte spritesSize){
	DASSERT( current && spritesSize>=0 );
	std::vector<Rect> rects;

	int StandarH = GetGetIntAtrr(current, "h");
	int StandarW = GetGetIntAtrr(current, "w");
	for ( rapidxml::xml_node<> * bbox = current->first_node("bbox"); bbox; bbox = bbox->next_sibling()) {

		int x = GetGetIntAtrr(bbox, "x");
		int y = GetGetIntAtrr(bbox, "y");

		DNEWPTR(rapidxml::xml_attribute<>, attrh);
		attrh = bbox->first_attribute("h");
		int h = ( attrh ? atoi( attrh->value() ) : StandarH );

		DNEWPTR(rapidxml::xml_attribute<>, attrw);
		attrw = bbox->first_attribute("w");
		int w = ( attrw ? atoi( attrw->value() ) : StandarW );

		Rect rect( ALIGN_SIZE( x, spritesSize ), ALIGN_SIZE( y, spritesSize ), 
					ALIGN_SIZE( w, spritesSize ), ALIGN_SIZE( h, spritesSize ) );
		rects.push_back( rect );
	}
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
	s = GetGetStringAtrr(rootNode, "format");

	bitmapName = std::string( GetGetStringAtrr(rootNode, "bitmap") );

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