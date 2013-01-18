#ifndef	TILELAYER_H
#define	TILELAYER_H

#include <TerrainUtilities.h>
#include <Metrics.h>
#include <allegro5\allegro.h>

#define MAX_WIDTH 32
#define MAX_HEIGHT 26

typedef std::pair<Dim, Dim> Coordinates;

enum HorizScroll { Left = -1, HorizIntact = 0, Right = +1 };
enum VertScroll  { Up = -1, VertIntact = 0, Down = +1 };

class TileLayer {

	public:
		TileLayer();
		~TileLayer();

	private:
		Index map[MAX_HEIGHT][MAX_WIDTH];

	public:
		void SetTile (Dim col, Dim row, Index index);
		Index GetTile (Dim col, Dim row);
		const Coordinates GetTileCoordinates (Dim mx, Dim my) const;

		void SetViewWindow (const Rect&);
		const Rect	GetViewWindow (void) const;

		void Display (Bitmap at, const Rect& displayArea);

		void Scroll (HorizScroll h, VertScroll v);
		bool CanScroll (HorizScroll h) const;
		bool CanScroll (VertScroll v) const;

		void WriteMap (FILE* fp);
		bool ReadMap (FILE* fp);
};

#endif