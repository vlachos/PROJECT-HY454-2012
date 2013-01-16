#ifndef	TILEBITMAP_H
#define	TILEBITMAP_H

#include <TerrainUtilities.h>
#include <Metrics.h>
#include <PathNames.h>
#include <allegro5\allegro.h>

#define MAX_WIDTH 11
#define MAX_HEIGHT 1


class TileBitmap {

	public:
		TileBitmap();

	private:
		Bitmap tiles;
		bool tileTransparency[MAX_WIDTH * MAX_HEIGHT / 32 + 1];
	
	private:
		bool IsTileTransparent (Dim row, Dim col) const;
		bool LoadTransparencyInfo (const std::string& path);
		void ProduceTransparencyInfo (void);
		bool WriteTransparencyInfo (const std::string& path);
		bool LoadTiles (const std::string& path);

	public:
		void PutTile (Bitmap BubbleBitmap, Dim x, Dim y, Index tile) const;
		Index GetPointedTile (Dim x, Dim y) const;
};

#endif