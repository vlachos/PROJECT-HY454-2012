#ifndef	TILELAYER_H
#define	TILELAYER_H

#include "TerrainUtilities.h"
#include "TileBitmap.h"
#include "Metrics.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

enum HorizScroll {Left = -1, HorizIntact = 0, Right = +1 };
enum VertScroll {Up = -1, VertIntact = 0, Down = +1 };

typedef std::pair<Dim, Dim> Coordinates;

enum BBMovement {BBLeft = -1, BBUp = 0, BBRight = +1};
#define BB_MOVEMENTS 3

#define TILE_LAYER_WIDTH 32
#define TILE_LAYER_HEIGHT 26
#define VIEW_WINDOW_WIDTH 512
#define VIEW_WINDOW_HEIGHT 416
#define VIEW_WINDOW_TILE_WIDTH 32
#define VIEW_WINDOW_TILE_HEIGHT 26

#define SMALL_BRICK_THRESHOLD 16
#define BIG_BRICK_THRESHOLD 64

class TileLayer{

	public:
		TileLayer();
		TileLayer(TileBitmap* aTileBitmap);
		~TileLayer();

	private:
		TileBitmap* tilesBitmap;
		Index map[TILE_LAYER_HEIGHT][TILE_LAYER_WIDTH];
		bool tilesSolidity[TILE_LAYER_HEIGHT][TILE_LAYER_WIDTH][BB_MOVEMENTS];
		Rect viewWindow;

	public:
		bool ReadMap (std::string aPath);
		bool ReadStage (std::string aPath);
		void WriteMap (std::string aPath);

		void Display (Bitmap at);

		void SetTile (Dim row, Dim col, Index indx);
		Index GetTile (Dim row, Dim col);
		const Coordinates GetTileCoordinates (Dim x, Dim y) const;
		const Coordinates GetXYCoordinates (Dim row, Dim col) const;
		const bool isSolid(Dim x, Dim y, BBMovement move) const;

		void SetViewWindow (const Rect&);
		const Rect	GetViewWindow (void) const;

		void Scroll (HorizScroll h, VertScroll v);
		bool CanScroll (HorizScroll h) const;
		bool CanScroll (VertScroll v) const;
};

#endif