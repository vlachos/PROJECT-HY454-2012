#include "AnimationFilmHolder.h"
#include <assert.h>

AnimationFilmHolder :: AnimationFilmHolder (const char* path){
	assert(path);
} // Decoder constructor.
    
AnimationFilmHolder :: ~AnimationFilmHolder(){ 
	assert(!(filmMap.empty()));
	assert(filmMem);

	filmMap.clear(); 
	delete [] filmMem; 
}
    
const AnimationFilm& AnimationFilmHolder :: GetFilm (const std::string id) const{
	assert(!(filmMap.empty()));
	assert(!(id.empty()));

	FilmMap::const_iterator i = filmMap.find(id);

	assert(i!=filmMap.end());
	return *i->second;
}