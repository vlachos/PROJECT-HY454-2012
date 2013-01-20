#include "AnimationFilmHolder.h"

#include <algorithm>
#include "MemoryManage.h"
#include "SpritesParser.h"
#include "MemoryManage.h"
#include "BitmapLoader.h"

namespace AnimationHolderDelete{

	struct DeleteAnimation{
		void operator()(std::pair<std::string, AnimationFilm*> _pair){
			udelete( _pair.second );
		}
	};

}

// Decoder constructor.
AnimationFilmHolder :: AnimationFilmHolder (const char* path){
	DASSERT(path);
	
	SpriteParser::SingletonCreate( path );
	BitmapLoader::SingletonCreate();

	int SpritesNum = SpriteParser::GetTotalSprites();
	DASSERT( SpritesNum>0 );
	filmMem = std::vector <AnimationFilm>(SpritesNum);

	SpriteParser::SpriteParserIterator::StartIterator();
	int i = 0;
	while( SpriteParser::SpriteParserIterator::HasNext() ){
		std::string id = SpriteParser::SpriteParserIterator::GetNext();
		Bitmap bitmap = BitmapLoader::Load( SpriteParser::GetBitmapName( id ) );
		DASSERT( bitmap );
		std::vector<Rect> bx = SpriteParser::GetSprite(id);
		AnimationFilm* a =	DNEWCLASS( AnimationFilm, (bitmap, bx, id ) );
		filmMap[id] = a;
		filmMem[i++] = *a;
	}
	DASSERT( i==SpritesNum );
	
	SpriteParser::SingletonDestroy();
} 
    
AnimationFilmHolder :: ~AnimationFilmHolder(){ 
	DASSERT(!filmMap.empty());
	DASSERT(!filmMem.empty());
	
	filmMem.clear();

	std::for_each( filmMap.begin(),
         filmMap.end(),
         AnimationHolderDelete::DeleteAnimation() );

	filmMap.clear(); 
	BitmapLoader::SingletonDestroy();
}
    
const AnimationFilm* AnimationFilmHolder :: GetFilm (const std::string id) const{
	DASSERT(!(filmMap.empty()));
	DASSERT(!(id.empty()));

	FilmMap::const_iterator i = filmMap.find(id);

	DASSERT(i!=filmMap.end());
	return i->second;
}