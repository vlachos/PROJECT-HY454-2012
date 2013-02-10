#ifndef	TILELAYER_H
#define	TILELAYER_H

#include "TerrainUtilities.h"
#include "TileBitmap.h"
#include "Metrics.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

enum HorizScroll {Left = -1, HorizIntact = 0, Right = +1 };
enum VertScroll {Up = -1, VertIntact = 0, Down = +1 };

enum BBMovement {BBLeft = -1, BBUp = 0, BBRight = +1, BBDown = +2};
#define BB_MOVEMENTS 4

#define TILE_LAYER_WIDTH 32
#define TILE_LAYER_HEIGHT 64

#define TILE_LAYER_STAGE_WIDTH 32
#define TILE_LAYER_STAGE_HEIGHT 32

#define SCREEN_WINDOW_WIDTH 512
#define SCREEN_WINDOW_HEIGHT 448
#define VIEW_WINDOW_START_X 0
#define VIEW_WINDOW_START_Y 2
#define VIEW_WINDOW_TILE_WIDTH 32
#define VIEW_WINDOW_TILE_HEIGHT 28

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
		bool ReadStage (unsigned int stageNum);
		void WriteMap (std::string testIndexPath, std::string testSldtyPath);

		void Display (Bitmap at);

		void SetTile (Dim row, Dim col, Index indx);
		Index GetTileIndex (Dim row, Dim col);
		const bool GetTileSolidity (int row, int col, BBMovement move) const;
		const Coordinates GetTileCoordinates (int x, int y) const;
		const Coordinates GetXYCoordinates (Dim row, Dim col) const;
		const bool isSolid(int x, int y, BBMovement move) const;

		void SetViewWindow (const Rect&);
		const Rect	GetViewWindow (void) const;

		void Scroll (HorizScroll h, VertScroll v);
		bool CanScroll (HorizScroll h) const;
		bool CanScroll (VertScroll v) const;
};

#endif