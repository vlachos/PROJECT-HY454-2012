#include "Sprites_Parser.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

static char * xmlFilePath = "..\\data\\bitmaps\\sprites\\data.xml";
SpriteParser * SpriteParser::singletonPtr = (SpriteParser*) 0;
rapidxml::xml_node<> * SpriteParser::root_node = (rapidxml::xml_node<> *) 0;
std::vector<char> SpriteParser::buffer;
int SpriteParser::spritesSize = -1;

SpriteParser::SpriteParser(void){
	rapidxml::xml_document<> doc;
	//open path and read
	std::ifstream theFile (xmlFilePath);
	buffer = std::vector<char>((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	//parse
	doc.parse<0>( &buffer[0] );
	root_node = doc.first_node("sprites");
	assert( root_node );
	const char * s = root_node->first_attribute("format")->value();
	assert( s );

	if(!strcmp(s, spriteParserSpecifications::strspritesSize[ (int) spriteParserSpecifications::spritesSize_sixteen ])){
		spritesSize = (int) spriteParserSpecifications::spritesSize_sixteen;
	}else
	if(!strcmp(s, spriteParserSpecifications::strspritesSize[ (int) spriteParserSpecifications::spritesSize_thirtytwo ])){
		spritesSize = (int) spriteParserSpecifications::spritesSize_thirtytwo;
	}else
	if(!strcmp(s, spriteParserSpecifications::strspritesSize[ (int) spriteParserSpecifications::spritesSize_sixtyfour ])){
		spritesSize = (int) spriteParserSpecifications::spritesSize_sixtyfour;
	}else
		assert(false);
}

/**
*	root_node is not needed to delete because it is just pointing to the buffer.
*/

SpriteParser::~SpriteParser(void){
	spritesSize = -1;
	root_node = (rapidxml::xml_node<> *) 0;
	buffer.clear();
}

/**
* i will do it std::vector<Rect>, when we create Rect!
* now i just print for testing
*/

std::vector<char> * SpriteParser::getSprite(const std::string& id){
	rapidxml::xml_node<> * spriteNode;
	std::vector<char> * bboxies = (std::vector<char> *) 0;
	int totalFrames;

	assert(root_node);
	spriteNode = root_node->first_node(id.c_str());

	if(spriteNode){
		char * _totalFrames = spriteNode->first_attribute("frames")->value();
		assert( _totalFrames );

		totalFrames = atoi( _totalFrames );
		assert( totalFrames > 0 );

		int index=0;
		for ( rapidxml::xml_node<> * bbox = spriteNode->first_node("bbox"); bbox; bbox = bbox->next_sibling(), ++index ) {
			std::cout << "\n========";
			rapidxml::xml_node<> * dx = bbox->first_node("dx");
			std::cout << dx->value();
			rapidxml::xml_node<> * dy = bbox->first_node("dy");
			std::cout << dy->value();
			rapidxml::xml_node<> * h = bbox->first_node("h");
			std::cout << h->value();
			rapidxml::xml_node<> * w = bbox->first_node("w");
			std::cout << w->value();
		}
		assert( index > 0 );
	}

	return bboxies;
}