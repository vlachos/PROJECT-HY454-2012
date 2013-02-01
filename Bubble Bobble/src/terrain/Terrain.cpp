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

	//actionLayer->ReadMap(BubblePathnames::GetActionLayerInfo());
	actionLayer->ReadStage(BubblePathnames::GetStageIndexInfo(1), BubblePathnames::GetStageSldtyInfo(1));
	actionLayer->WriteMap(BubblePathnames::GetTestActionLayerIndexInfo(),  BubblePathnames::GetTestActionLayerSldtyInfo());
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