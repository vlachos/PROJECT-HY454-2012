#include "Tile_Bitmap.h"

	/*public*/
	Tile_Bitmap::Tile_Bitmap(){
	}

	/*private*/
	bool Tile_Bitmap::IsTileTransparent (Dim row, Dim col) const{
		return 0;
	}
	bool Tile_Bitmap::LoadTransparencyInfo (const std::string& path){
		return 0;
	}
	void Tile_Bitmap::ProduceTransparencyInfo (void){
	}
	bool Tile_Bitmap::WriteTransparencyInfo (const std::string& path){
		return 0;
	}
	bool Tile_Bitmap::LoadTiles (const std::string& path){
		return 0;
	}

	/*public*/
	void Tile_Bitmap::PutTile (Bitmap bubble_bitmap, Dim x, Dim y, Index tile) const{
	}
	Index Tile_Bitmap::GetPointedTile (Dim x, Dim y) const{
		return 0;
	}
