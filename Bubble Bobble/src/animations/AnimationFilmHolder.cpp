#include "AnimationFilmHolder.h"
#include "MemoryManage.h"
#include "SpritesParser.h"
#include "MemoryManage.h"
#include "BitmapLoader.h"

AnimationFilmHolder :: AnimationFilmHolder (const char* path){
	DASSERT(path);

	SpriteParser::SingletonCreate();//orisma to path
	BitmapLoader::SingletonCreate();
	Bitmap bitmap;
	char* id;
	int SpritesNum=SpriteParser::GetTotalSprites();
	int i=0;

	filmMem=DNEWARR(AnimationFilm,SpritesNum);

	while((id=SpriteParser::GetNext())!=NULL){
		bitmap=BitmapLoader::Load(path);
		AnimationFilm* film = DNEW(AnimationFilm(bitmap,SpriteParser::GetSprite(id),std::string(id)));
		filmMem[i++] = *film;
		filmMap[id] = film;
	}
	DASSERT( i==SpritesNum );

} // Decoder constructor.
    
AnimationFilmHolder :: ~AnimationFilmHolder(){ 
	DASSERT(!(filmMap.empty()));
	DASSERT(filmMem);

	SpriteParser::SingletonDestroy();
	BitmapLoader::SingletonDestroy();
	filmMap.clear(); 
	delete [] filmMem; 
}
    
const AnimationFilm& AnimationFilmHolder :: GetFilm (const std::string id) const{
	DASSERT(!(filmMap.empty()));
	DASSERT(!(id.empty()));

	FilmMap::const_iterator i = filmMap.find(id);

	DASSERT(i!=filmMap.end());
	return *i->second;
}