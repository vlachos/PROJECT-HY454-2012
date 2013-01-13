#include "TileBitmap.h"

	/*public*/
	TileBitmap::TileBitmap(){
	}

	/*private*/
	bool TileBitmap::IsTileTransparent (Dim row, Dim col) const{
		return false;
	}
	bool TileBitmap::LoadTransparencyInfo (const std::string& path){
		return false;
	}
	void TileBitmap::ProduceTransparencyInfo (void){
	}
	bool TileBitmap::WriteTransparencyInfo (const std::string& path){
		return false;
	}
	bool TileBitmap::LoadTiles (const std::string& path){
		return false;
	}

	/*public*/
	void TileBitmap::PutTile (Bitmap bubbleBitmap, Dim x, Dim y, Index tile) const{
	}
	Index TileBitmap::GetPointedTile (Dim x, Dim y) const{
		return 0;
	}
