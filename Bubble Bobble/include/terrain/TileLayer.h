#ifndef	TILELAYER_H
#define	TILELAYER_H

#include <TerrainUtilities.h>
#include <Metrics.h>
#include <allegro5\allegro.h>

typedef std::pair<Dim, Dim> Coordinates;

enum HorizScroll { Left = -1, HorizIntact = 0, Right = +1 };
enum VertScroll  { Up = -1, VertIntact = 0, Down = +1 };

#define TILE_LAYER_WIDTH 32
#define TILE_LAYER_HEIGHT 26
#define VIEW_WINDOW_WIDTH 512
#define VIEW_WINDOW_HEIGHT 416

class TileLayer {

	public:
		TileLayer();
		~TileLayer();

	private:
		Index map[TILE_LAYER_HEIGHT][TILE_LAYER_WIDTH];
		Bitmap layer;
		Rect viewWindow;

	public:
		bool ReadMap (std::string aPath);
		bool ReadStage (std::string aPath);
		void WriteMap (std::string aPath);

		void Display (Display_t at, const Rect& displayArea);

		void SetTile (Dim col, Dim row, Index indx);
		Index GetTile (Dim col, Dim row);
		const Coordinates GetTileCoordinates (Dim mx, Dim my) const;

		void SetViewWindow (const Rect&);
		const Rect	GetViewWindow (void) const;

		void Scroll (HorizScroll h, VertScroll v);
		bool CanScroll (HorizScroll h) const;
		bool CanScroll (VertScroll v) const;
};

#endif