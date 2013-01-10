#include <stdio.h>
#include <iostream>
#include <allegro5\allegro.h>

#define MAX_WIDTH 32
#define MAX_HEIGHT 26

typedef unsigned char Index;
typedef unsigned int Dim;
typedef std::pair<Dim, Dim> Tile_Coordinates;

class Tile_Layer {

	public:
		Tile_Layer();

	private:
		Index map[MAX_HEIGHT][MAX_WIDTH];

	public:

		void SetTile (Dim col, Dim row, Index index);
		Index GetTile (Dim col, Dim row);
		const Tile_Coordinates GetTileCoordinates (Dim mx, Dim my) const;

		void WriteMap (FILE* fp);
		bool ReadMap (FILE* fp);
};