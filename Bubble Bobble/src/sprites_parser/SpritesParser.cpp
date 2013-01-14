#include "SpritesParser.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "MemoryManage.h"
#include "Metrics.h"

#define ALIGN_SIZE(a) ( (a) << spritesSize )

static char * xmlFilePath = "..\\data\\bitmaps\\sprites\\data.xml";
SpriteParser * SpriteParser::singletonPtr = (SpriteParser*) 0;
rapidxml::xml_node<> * SpriteParser::rootNode = (rapidxml::xml_node<> *) 0;
std::vector<char> SpriteParser::buffer;
char * SpriteParser::bitmapName = ( char *) 0;
int SpriteParser::spritesSize = -1;

SpriteParser::SpriteParser(void){
	rapidxml::xml_document<> doc;
	//open path and read
	std::ifstream theFile (xmlFilePath);
	buffer = std::vector<char>((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	//parse
	doc.parse<0>( &buffer[0] );
	rootNode = doc.first_node("sprites");
	DASSERT( rootNode );
	DNEWPTR( const char, s);
	s = rootNode->first_attribute("format")->value();
	DASSERT( s );

	bitmapName = rootNode->first_attribute("bitmap")->value();
	DASSERT(bitmapName);

	using namespace SpriteParserSpecifications;

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
}

/**
*	root_node is not needed to delete because it is just pointing to the buffer.
*/

SpriteParser::~SpriteParser(void){
	spritesSize = -1;
	unullify( rootNode );
	buffer.clear();
}

char * SpriteParser::GetBitmapName(void){
	DASSERT(bitmapName);
	return bitmapName;
}

std::vector<Rect> SpriteParser::GetSprite(const char * id){
	DNEWPTR(rapidxml::xml_node<>, spriteNode);
	int totalFrames;

	DASSERT(rootNode);
	spriteNode = rootNode->first_node(id);

	std::vector<Rect> rects;

	if(spriteNode){
		DNEWPTR( char,  _totalFrames);
		_totalFrames = spriteNode->first_attribute("frames")->value();
		DASSERT( _totalFrames );

		totalFrames = atoi( _totalFrames );
		DASSERT( totalFrames > 0 );

		int index=0;
		for ( rapidxml::xml_node<> * bbox = spriteNode->first_node("bbox"); bbox; bbox = bbox->next_sibling(), ++index ) {

			DNEWPTR(rapidxml::xml_node<>, dx);
			dx = bbox->first_node("dx");

			DNEWPTR(rapidxml::xml_node<>, dy);
			dy = bbox->first_node("dy");

			DNEWPTR(rapidxml::xml_node<>, h);
			h = bbox->first_node("h");

			DNEWPTR(rapidxml::xml_node<>, w);
			w = bbox->first_node("w");

			DASSERT( dx && dx->value() && dy && dy->value() && h && h->value() && w && w->value() );
			Rect rect( ALIGN_SIZE( StringToDim( dx->value() ) ), ALIGN_SIZE( StringToDim( dy->value()) ), 
						ALIGN_SIZE( StringToDim( h->value() ) ), ALIGN_SIZE(  StringToDim( w->value()) ) );
			rects.push_back( rect );
		}
		DASSERT( index == totalFrames && rects.size() == index);
	}

	return rects;
}