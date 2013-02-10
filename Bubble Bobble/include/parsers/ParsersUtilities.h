#ifndef PARSERUTILITIES_H
#define PARSERUTILITIES_H

#include "rapidxml.hpp"
#include "MemoryManage.h"

static int GetGetIntAtrr(rapidxml::xml_node<>* anim, const char * atrr ){				
	rapidxml::xml_attribute<>* getter = anim->first_attribute(atrr);	
	DASSERT( getter && getter->value() );						
	return atoi( getter->value() )	;
}

static char * GetGetStringAtrr(rapidxml::xml_node<>* anim, const char * atrr ){				
	rapidxml::xml_attribute<>* getter = anim->first_attribute(atrr);	
	DASSERT( getter );
	char * getVal = getter->value();
	DASSERT( getVal );
	return getVal;
}

static bool GetGetBoolAtrr(rapidxml::xml_node<>* anim, const char * atrr ){							
		rapidxml::xml_attribute<>* getter = (anim)->first_attribute(atrr);
		DASSERT( getter && getter->value() );	

		bool cont;
		if( !strcmp( getter->value(), "true" ) ){
			cont = true;
		}else 
		if( !strcmp( getter->value(), "false" ) ){
			cont = false;
		}else
			DASSERT(false);

		return cont;
}

#endif