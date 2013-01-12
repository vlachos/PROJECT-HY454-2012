#ifndef	SPRITESPARSER_H
#define	SPRITESPARSER_H

#include <string>
#include <allegro5\allegro.h>

#define MAX_WIDTH 6
#define MAX_HEIGHT 2

typedef ALLEGRO_BITMAP* Bitmap;
typedef unsigned char Index;
typedef unsigned int Dim;

class Tile_Bitmap {

	public:
		Tile_Bitmap();

	private:
		Bitmap tiles;
		bool tileTransparency[MAX_WIDTH * MAX_HEIGHT / 32 + 1];
	

		bool IsTileTransparent (Dim row, Dim col) const;
		bool LoadTransparencyInfo (const std::string& path);
		void ProduceTransparencyInfo (void);
		bool WriteTransparencyInfo (const std::string& path);
		bool LoadTiles (const std::string& path);

	public:
		void PutTile (Bitmap bubble_bitmap, Dim x, Dim y, Index tile) const;
		Index GetPointedTile (Dim x, Dim y) const;
};

#endif