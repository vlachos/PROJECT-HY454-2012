#include <string>
#include <iostream>
#include <allegro5\allegro.h>

#define MAX_WIDTH 8
#define MAX_HEIGHT 8
typedef ALLEGRO_BITMAP Bitmap;
typedef unsigned char Index;
typedef unsigned int Dim;

class Tile {
	private:
	unsigned int	tileTransparency[MAX_WIDTH * MAX_HEIGHT / 32 + 1];
	Bitmap tiles;

	bool	IsTileTransparent (Dim row, Dim col) const;
	bool	LoadTransparencyInfo (const std::string & path);
	void	ProduceTransparencyInfo (void);
	bool	WriteTransparencyInfo (const std::string & path);
	bool	LoadTiles (const std::string & path);

	public:
	void	PutTile (Bitmap bubble_bitmap, Dim x, Dim y, Index tile) const;
	Index	GetPointedTile (Dim x, Dim y) const;
};