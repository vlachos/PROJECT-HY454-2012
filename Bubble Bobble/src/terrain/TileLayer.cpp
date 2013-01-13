#include "TileLayer.h"

	/*public*/
	TileLayer::TileLayer(){
	}

	/*private*/
	void TileLayer::SetTile (Dim col, Dim row, Index index){
	}
	Index TileLayer::GetTile (Dim col, Dim row){
		return 0;
	}
	const TileCoordinates TileLayer::GetTileCoordinates (Dim mx, Dim my) const{
		TileCoordinates a_pair;
		a_pair = std::make_pair(0,0);
		return a_pair;
	}

	/*public*/
	void TileLayer::WriteMap (FILE* fp){
	}
	bool TileLayer::ReadMap (FILE* fp){
		return false;
	}
