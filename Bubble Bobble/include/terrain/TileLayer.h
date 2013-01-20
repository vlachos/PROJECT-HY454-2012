#ifndef	TILELAYER_H
#define	TILELAYER_H

#include <TerrainUtilities.h>
#include <TileBitmap.h>
#include <Metrics.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

typedef std::pair<Dim, Dim> Coordinates;

enum HorizScroll { Left = -1, HorizIntact = 0, Right = +1 };
enum VertScroll  { Up = -1, VertIntact = 0, Down = +1 };

#define TILE_LAYER_WIDTH 32
#define TILE_LAYER_HEIGHT 26
#define VIEW_WINDOW_WIDTH 512
#define VIEW_WINDOW_HEIGHT 416
#define VIEW_WINDOW_TILE_WIDTH 32
#define VIEW_WINDOW_TILE_HEIGHT 26

class TileLayer{

	public:
		TileLayer();
		TileLayer(TileBitmap* aTileBitmap);
		~TileLayer();

	private:
		TileBitmap* tiles;
		Index map[TILE_LAYER_HEIGHT][TILE_LAYER_WIDTH];
		bool tilesSolidity[TILE_LAYER_HEIGHT][TILE_LAYER_WIDTH];
		Rect viewWindow;

	public:
		bool ReadMap (std::string aPath);
		bool ReadStage (std::string aPath);
		void WriteMap (std::string aPath);

		void Display (Bitmap at);

		void SetTile (Dim col, Dim row, Index indx);
		Index GetTile (Dim col, Dim row);
		const Coordinates GetTileCoordinates (Dim mx, Dim my) const;
		const bool isSolid(Dim x, Dim y) const;

		void SetViewWindow (const Rect&);
		const Rect	GetViewWindow (void) const;

		void Scroll (HorizScroll h, VertScroll v);
		bool CanScroll (HorizScroll h) const;
		bool CanScroll (VertScroll v) const;
};

#endif