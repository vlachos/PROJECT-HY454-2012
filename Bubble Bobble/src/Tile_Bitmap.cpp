#include "Tile_Bitmap.h"

	/*public*/
	Tile_Bitmap::Tile_Bitmap(){
	}

	/*private*/
	bool Tile_Bitmap::IsTileTransparent (Dim row, Dim col) const{
	}
	bool Tile_Bitmap::LoadTransparencyInfo (const std::string& path){
	}
	void Tile_Bitmap::ProduceTransparencyInfo (void){
	}
	bool Tile_Bitmap::WriteTransparencyInfo (const std::string& path){
	}
	bool Tile_Bitmap::LoadTiles (const std::string& path){
	}

	/*public*/
	void Tile_Bitmap::PutTile (Bitmap bubble_bitmap, Dim x, Dim y, Index tile) const{
	}
	Index Tile_Bitmap::GetPointedTile (Dim x, Dim y) const{
	}
