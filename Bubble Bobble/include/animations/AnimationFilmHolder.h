#ifndef ANIMATIONFILMHOLDER_H
#define ANIMATIONFILMHOLDER_H

#include "AnimationFilm.h"
#include <string>
#include <vector>
#include <map>

class AnimationFilmHolder{
private:
	typedef std::map<std::string, AnimationFilm*> FilmMap;
    
	static FilmMap	filmMap;
    static std::vector <AnimationFilm>	filmMem; // Мыс єс films allocated as array
	static AnimationFilmHolder * singletonPtr;
	AnimationFilmHolder (const char* path); // Decoder constructor.
    ~AnimationFilmHolder();
public:
	static void				SingletonCreate (const char * path) 
			{ singletonPtr = new AnimationFilmHolder(path); }
	static void				SingletonDestroy (void) 
			{ delete singletonPtr; singletonPtr = 0; }

    static const AnimationFilm* GetFilm (const std::string id);
};

#endif