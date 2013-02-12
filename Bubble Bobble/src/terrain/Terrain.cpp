#include "Terrain.h"
#include "BubbleLogic.h"

#define SCOREBOARD_DELAY 2000

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
	DDELETE( actionLayer);
	DDELETE( scores);
}

void Terrain::SingeltonCreate(){
	terrain = DNEWCLASS(Terrain,() );

	DNEWPTR(TileBitmap, tilesBitmap);
	tilesBitmap = DNEW(TileBitmap);
	actionLayer = DNEWCLASS(TileLayer, (tilesBitmap) );

	actionLayer->ReadMap(PathNames::GetActionLayerInfo());
	actionLayer->WriteMap(PathNames::GetTestActionLayerIndexInfo(),  PathNames::GetTestActionLayerSldtyInfo());
}

TileLayer* Terrain::GetActionLayer(){
	return Terrain::actionLayer;
}

void Terrain::DisplayTerrain(Bitmap at, timestamp_t nowTime){
	actionLayer->Display(at);

	static timestamp_t oldTime = -1;
//	if ( nowTime > oldTime + SCOREBOARD_DELAY ){
	//	oldTime = nowTime;
		scores->GenerateScoreBoardInfo(BubbleLogic::GetBubProfile()->GetScore(),
										BubbleLogic::GetHighScore(),
										BubbleLogic::GetBobProfile()->GetScore() );
	//}

	if (BubbleLogic::GetBubProfile()->GetScore() != -1)
		scores->DisplayScoreBoard(at,	BubbleLogic::GetBubProfile()->GetScore(),
										BubbleLogic::GetHighScore(),
										BubbleLogic::GetBobProfile()->GetScore() );
}

void Terrain::SingeltonCleanUp(){
	delete terrain;
}