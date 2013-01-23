#include <Terrain.h>

Terrain* Terrain::terrain;
TileLayer* Terrain::actionLayer;

/*constructor and destructor*/
Terrain::Terrain(){
	actionLayer = DNEWCLASS(TileLayer,() );
	DASSERT(actionLayer);
}
Terrain::~Terrain(){
	delete actionLayer;
}

void Terrain::SingeltonCreate(){
	terrain = DNEWCLASS(Terrain,() );

	DNEWPTR(TileBitmap, tilesBitmap);
	tilesBitmap = DNEW(TileBitmap);
	actionLayer = DNEWCLASS(TileLayer, (tilesBitmap) );

	actionLayer->ReadStage(BubblePathnames::GetStageInfo(1));
	actionLayer->WriteMap(BubblePathnames::GetTestActionLayerInfo() );
}

TileLayer* Terrain::GetActionLayer(){
	return Terrain::actionLayer;
}

void Terrain::DisplayTerrain(Bitmap at){
	actionLayer->Display(at);
}

void Terrain::SingeltonCleanUp(){
	delete terrain;
}