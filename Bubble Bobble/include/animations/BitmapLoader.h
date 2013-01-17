#ifndef BITMAPLOADER_H
#define BITMAPLOADER_H

#include <map>
#include <string>
#include "MemoryManage.h"
#include "utilities.h"

class BitmapLoader{
	public:
		static void				SingletonCreate (void) { singletonPtr = new BitmapLoader; }
		static void				SingletonDestroy (void) { DASSERT( singletonPtr ); delete singletonPtr; singletonPtr = 0; }
		
		static Bitmap			Load(const std::string & path);

	private:
		typedef std::map< std::string, Bitmap > BitmapMap;
		static BitmapMap						bitmaps;
		static BitmapLoader*					singletonPtr;
		
		static Bitmap GetBitmap(const std::string & path);
		static Bitmap LoadBitmap(const std::string & path);
		static void DestroyBitmap(Bitmap bitmap);

		BitmapLoader(void) {}
		~BitmapLoader(void);
};

#endif