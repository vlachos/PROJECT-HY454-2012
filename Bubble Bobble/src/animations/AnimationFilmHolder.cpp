#include "AnimationFilmHolder.h"

AnimationFilmHolder :: AnimationFilmHolder (const char* path){} // Decoder constructor.
    
AnimationFilmHolder :: ~AnimationFilmHolder(){ 
	filmMap.clear(); delete [] filmMem; 
}
    
const AnimationFilm& AnimationFilmHolder :: GetFilm (const std::string id) const {
	FilmMap::const_iterator i = filmMap.find(id);
	assert(i!=filmMap.end());
	return *i->second;
}