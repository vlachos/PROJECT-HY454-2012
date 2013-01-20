#ifndef ANIMATIONFILMHOLDER_H
#define ANIMATIONFILMHOLDER_H

#include "AnimationFilm.h"
#include <string>
#include <vector>
#include <map>

class AnimationFilmHolder{
	typedef std::map<std::string, AnimationFilm*> FilmMap;
    
	FilmMap	filmMap;
    std::vector <AnimationFilm>	filmMem; // Мыс єс films allocated as array
    
public:
	AnimationFilmHolder (const char* path); // Decoder constructor.
    ~AnimationFilmHolder();
    const AnimationFilm* GetFilm (const std::string id) const;
};

#endif