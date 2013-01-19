#include <Terrain.h>

	/*constructor and destructor*/
	Terrain::Terrain(){
		DNEWPTR(TileBitmap, tiles);
		tiles = DNEWCLASS(TileBitmap,() );
		DNEWPTR(TileLayer, actionLayer);
		actionLayer = DNEWCLASS(TileLayer,() );

		DASSERT(tiles);
		DASSERT(actionLayer);
	}
	Terrain::~Terrain(){
		tiles->~TileBitmap();
		actionLayer->~TileLayer();
	}

	void Terrain::InitializeTerrain(){
		actionLayer->ReadStage("");
		actionLayer->WriteMap("");
		//actionLayer->Display();
	}