#include <Terrain.h>

Terrain* Terrain::terrain;
TileLayer* Terrain::actionLayer;
ScoreBoard* Terrain::scores;

/*constructor and destructor*/
Terrain::Terrain(){
	actionLayer = DNEWCLASS(TileLayer,() );
	scores = DNEWCLASS(ScoreBoard,() );
	DASSERT(actionLayer);
	DASSERT(scores);
}
Terrain::~Terrain(){
	delete actionLayer;
	delete scores;
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
	scores->DisplayScoreBoard(at, 12345, 99999999, 906);
}

void Terrain::SingeltonCleanUp(){
	delete terrain;
}