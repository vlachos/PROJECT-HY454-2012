#include "SpritesParser.h"

#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "MemoryManage.h"
#include "Metrics.h"

#define ALIGN_SIZE(a) ( (a) << spritesSize )

//static char * xmlFilePath = "..\\data\\bitmaps\\sprites\\data.xml";
//SpriteParser * SpriteParser::singletonPtr = (SpriteParser*) 0;
const char * SpriteParser::xmlFilePath;
SpriteParser * SpriteParser::singletonPtr;
rapidxml::xml_node<> * SpriteParser::rootNode = (rapidxml::xml_node<> *) 0;
std::vector<char> SpriteParser::buffer;
std::string SpriteParser::bitmapName("..\\data\\bitmaps\\sprites\\");
int SpriteParser::spritesSize = -1;
int SpriteParser::totalSprites = -1;

SpriteParser::SpriteParser(const char * path){
	
	xmlFilePath=path;
	rapidxml::xml_document<> doc;
	//open path and read
	std::ifstream theFile (xmlFilePath);
	buffer = std::vector<char>((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	//parse
	doc.parse<0>( &buffer[0] );
	rootNode = doc.first_node("sprites");
	DASSERT( rootNode );

	DNEWPTR( const char, s );
	s = rootNode->first_attribute("format")->value();
	DASSERT( s );

	DNEWPTR( char,  _totalSprites );
	_totalSprites = rootNode->first_attribute("totalSprites")->value();
	DASSERT( _totalSprites );

	totalSprites = atoi( _totalSprites );
	DASSERT( totalSprites > 0 );

	char * _bitmapName = rootNode->first_attribute("bitmap")->value();
	DASSERT(_bitmapName);

	bitmapName += std::string(_bitmapName);

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


//	root_node is not needed to delete because it is just pointing to the buffer.

SpriteParser::~SpriteParser(void){
	spritesSize = -1;
	unullify( rootNode );
	buffer.clear();
}

std::string SpriteParser::GetBitmapName(const std::string & id){
	return 	bitmapName;
}

std::vector<Rect> SpriteParser::GetSprite(const std::string & id){
	DNEWPTR(rapidxml::xml_node<>, spriteNode);
	int totalFrames;

	DASSERT(rootNode);
	spriteNode = rootNode->first_node(id.c_str());
	
	std::vector<Rect> rects;

	if(spriteNode){
		DNEWPTR( char,  _totalFrames);
		_totalFrames = spriteNode->first_attribute("frames")->value();
		DASSERT( _totalFrames );
		
		totalFrames = atoi( _totalFrames );
		DASSERT( totalFrames > 0 );

		int index=0;
		for ( rapidxml::xml_node<> * bbox = spriteNode->first_node("bbox"); bbox; bbox = bbox->next_sibling(), ++index ) {

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
			Rect rect( ALIGN_SIZE( StringToDim( dx->value() ) ), ALIGN_SIZE( StringToDim( dy->value()) ), 
						ALIGN_SIZE( StringToDim( h->value() ) ), ALIGN_SIZE(  StringToDim( w->value()) ) );
			rects.push_back( rect );
		}
		DASSERT( index == totalFrames && rects.size() == index);
	}

	return rects;
}


int SpriteParser :: GetTotalSprites(){
	DASSERT( totalSprites>0 );
	return totalSprites;
}

rapidxml::xml_node<> * SpriteParser::SpriteParserIterator::iteratorSpriteNode = ( rapidxml::xml_node<> * )0;
int SpriteParser::SpriteParserIterator::remainningSprites = -1;

void SpriteParser::SpriteParserIterator::StartIterator() { 
	DASSERT(rootNode && rootNode->first_node() && totalSprites>0);
	iteratorSpriteNode = rootNode->first_node(); 
	remainningSprites = totalSprites; 
}

bool SpriteParser::SpriteParserIterator::HasNext(void) { 
	DASSERT( ( remainningSprites>1 && iteratorSpriteNode->next_sibling() ) ||
			 ( remainningSprites==1 && !iteratorSpriteNode->next_sibling() ) ||
			   remainningSprites==0 && !iteratorSpriteNode	);
	return remainningSprites!=0; 
}

char * SpriteParser::SpriteParserIterator::GetNext(void) { 
	DASSERT( HasNext() );
	char * name = iteratorSpriteNode->name();  
	DASSERT( name );
	iteratorSpriteNode = iteratorSpriteNode->next_sibling(); 
	--remainningSprites;

	return name;
}