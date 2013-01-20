#include <algorithm>
#include "BitmapLoader.h"
#include <allegro5\allegro_image.h>

BitmapLoader*				BitmapLoader::singletonPtr = ( BitmapLoader* ) 0;
BitmapLoader::BitmapMap		BitmapLoader::bitmaps;

namespace BitmapLoaderDelete{

	struct DeleteBitmap{
		void operator()(std::pair<std::string, Bitmap> _pair){
			al_destroy_bitmap( _pair.second );
		}
	};

}

BitmapLoader::~BitmapLoader(void){
	std::for_each( bitmaps.begin(),
         bitmaps.end(),
         BitmapLoaderDelete::DeleteBitmap() );

	bitmaps.clear();
}

Bitmap BitmapLoader::Load(const std::string & path){
	Bitmap b = GetBitmap(path);
	if(!b){
		bitmaps[path] = ( b = LoadBitmap(path) );
		DASSERT(b);
	}
	return b;
}
		
Bitmap BitmapLoader::GetBitmap(const std::string & path){
	BitmapMap::const_iterator i = bitmaps.find( path );
	return (  (i != bitmaps.end() ) ? i->second : (Bitmap) 0 );
}

Bitmap BitmapLoader::LoadBitmap(const std::string & path){
	Bitmap b;
	b = al_load_bitmap( path.c_str() );
	al_convert_mask_to_alpha(b, BB_ELECTRIC_BLUE);
	DASSERT( b );
	return b;
}
