#ifndef	TERRAIN_H
#define	TERRAIN_H

#include <TileBitmap.h>
#include <TileLayer.h>

class Terrain {

	public:
		Terrain();
		~Terrain();

	private:
		TileBitmap* tiles;
		TileLayer* actionLayer;

	public:
		void InitializeTerrain();
};

#endif