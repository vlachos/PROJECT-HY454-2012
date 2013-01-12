#include "Tile_Layer.h"

	/*public*/
	Tile_Layer::Tile_Layer(){
	}

	/*private*/
	void Tile_Layer::SetTile (Dim col, Dim row, Index index){
	}
	Index Tile_Layer::GetTile (Dim col, Dim row){
		return 0;
	}
	const Tile_Coordinates Tile_Layer::GetTileCoordinates (Dim mx, Dim my) const{
		Tile_Coordinates a_pair;
		a_pair = std::make_pair(0,0);
		return a_pair;
	}

	/*public*/
	void Tile_Layer::WriteMap (FILE* fp){
	}
	bool Tile_Layer::ReadMap (FILE* fp){
		return 0;
	}
