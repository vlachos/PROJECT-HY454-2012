#include <stdio.h>
#include <iostream>
#include <allegro5\allegro.h>

#define MAX_WIDTH 32
#define MAX_HEIGHT 28
typedef unsigned char Index;
typedef unsigned int Dim;

class TileLayer {
	private:
	Index	map[MAX_HEIGHT][MAX_WIDTH];

	public:
	void	SetTile (Dim col, Dim row, Index index);
	Index	GetTile (Dim col, Dim row);
	const std::pair<Dim, Dim> GetTileCoordinates (Dim mx, Dim my) const;

	void	WriteMap (FILE* fp);
	bool	ReadMap (FILE* fp);
};