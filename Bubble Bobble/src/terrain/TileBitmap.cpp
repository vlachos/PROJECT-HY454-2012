#include <TileBitmap.h>
#include <assert.h>

	/*public*/
	TileBitmap::TileBitmap(){
		tiles = 0;
	}

	/*private*/
	bool TileBitmap::IsTileTransparent (Dim row, Dim col) const{
		return false;
	}
	bool TileBitmap::LoadTransparencyInfo (const std::string& path){
		assert( GetFileAttributesA(path.c_str()) != INVALID_FILE_ATTRIBUTES );
		return false;
	}
	void TileBitmap::ProduceTransparencyInfo (void){
	}
	bool TileBitmap::WriteTransparencyInfo (const std::string& path){
		assert( GetFileAttributesA(path.c_str()) != INVALID_FILE_ATTRIBUTES );
		return false;
	}
	bool TileBitmap::LoadTiles (const std::string& path){
		assert( GetFileAttributesA(path.c_str()) != INVALID_FILE_ATTRIBUTES );

		if (tiles = al_load_bitmap((char*) path.c_str()) )
			return true;
		else
			return false;
	}

	/*public*/
	void TileBitmap::PutTile (Bitmap bubbleBitmap, Dim source_x, Dim source_y, Index tileIndex) const{
		if (false){
			al_draw_bitmap_region(bubbleBitmap, source_x, source_y, TILE_SIZE, TILE_SIZE,
										  TileX(tileIndex), TileY(tileIndex), NULL);
		}
	}

	Index TileBitmap::GetPointedTile (Dim x, Dim y) const{
		return MakeIndex(x,y);
	}

