#include "Tile_Layer.h"

	/*public*/
	Tile_Layer::Tile_Layer(){
	}

	/*private*/
	void Tile_Layer::SetTile (Dim col, Dim row, Index index){
	}
	Index Tile_Layer::GetTile (Dim col, Dim row){
	}
	const Tile_Coordinates Tile_Layer::GetTileCoordinates (Dim mx, Dim my) const{
	}

	/*public*/
	void Tile_Layer::WriteMap (FILE* fp){
	}
	bool Tile_Layer::ReadMap (FILE* fp){
	}
