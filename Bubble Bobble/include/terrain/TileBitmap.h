#ifndef	TILEBITMAP_H
#define	TILEBITMAP_H

#include <TerrainUtilities.h>
#include <Metrics.h>
#include <PathNames.h>
#include <allegro5\allegro.h>

#define TILE_BITMAP_WIDTH 16
#define TILE_BITMAP_HEIGHT 16

class TileBitmap {

	public:
		TileBitmap();
		~TileBitmap();

	private:
		Bitmap tiles;
	
	private:
		bool LoadTiles (const std::string& aPath);
	public:
		void SetTargetBitmapAndClear(Bitmap aTargetBitmap, unsigned int R, unsigned int B, unsigned int G);
		void PutTile (Bitmap aBitmap, Dim sourceX, Dim sourceY, Index tileIndx) const;
		Index GetPointedTile (Dim x, Dim y) const;

	private:
		bool IsTileTransparent (Dim row, Dim col) const;
		bool LoadTransparencyInfo (const std::string& aPath);
		void ProduceTransparencyInfo (void);
		bool WriteTransparencyInfo (const std::string& aPath);
};

#endif