#ifndef	TERRAIN_H
#define	TERRAIN_H

#include "TileBitmap.h"
#include "TileLayer.h"
#include "ScoreBoard.h"

class Terrain {

	private:
		Terrain();
		~Terrain();

	private:
		static Terrain* terrain;
		static TileLayer* actionLayer;
		static ScoreBoard* scores;

	public:
		static void SingeltonCreate();

	public:
		static TileLayer* GetActionLayer();
		static void DisplayTerrain(Bitmap at);

	public:
		static void SingeltonCleanUp(); 

};

#endif