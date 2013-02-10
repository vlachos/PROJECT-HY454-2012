#include "SpritesAttributeParser.h"

#include <algorithm>
#include <fstream>
#include <list>
#include <string.h>
#include <stdlib.h>

#include "ParsersUtilities.h"

SpritesAttributeParser::attributeMap	SpritesAttributeParser::attributes;
SpritesAttributeParser*					SpritesAttributeParser::singletonPtr;
const char *							SpritesAttributeParser::xmlFilePath;

namespace SpritesAttributeLoaderDelete{
	struct DeleteAttribute{
		void operator()(std::pair<std::string, int> _pair){
			_pair.first.clear();
		}
	};
}

SpritesAttributeParser::SpritesAttributeParser(const char * path){
	xmlFilePath = path;
	rapidxml::xml_document<> doc;
	//open path and read
	std::ifstream theFile (xmlFilePath);
	std::vector<char> buffer = std::vector<char>((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	//parse
	doc.parse<0>( &buffer[0] );

	DNEWPTR( rapidxml::xml_node<>, rootNode);
	rootNode = doc.first_node("Attributes");
	DASSERT( rootNode );

	for(rapidxml::xml_node<>* iterate = rootNode->first_node(); iterate; iterate = iterate->next_sibling()){
		attributes[ std::string(iterate->name()) ] = GetGetIntAtrr( iterate, "v" );
	}
}

SpritesAttributeParser::~SpritesAttributeParser(){
	std::for_each(	
					attributes.begin(),
					attributes.end(),
					SpritesAttributeLoaderDelete::DeleteAttribute() 
				);

	attributes.clear();
	unullify( xmlFilePath );
}

int SpritesAttributeParser::GetAttribute(const char* id){
	DASSERT(id);
	return attributes[ std::string(id) ];
}