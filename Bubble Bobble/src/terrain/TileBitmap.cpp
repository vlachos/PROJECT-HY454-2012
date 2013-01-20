#include <TileBitmap.h>
#include "MemoryManage.h"

	/*constructor and destructor*/
	TileBitmap::TileBitmap(){
		LoadTiles (BubblePathnames::GetTilesBitmap() );
		DASSERT(tiles );
	}

	TileBitmap::~TileBitmap(){
		al_destroy_bitmap(tiles);
	}

	/*tiles Bitmap*/
	bool TileBitmap::LoadTiles (const std::string& aPath ){
		DASSERT(GetFileAttributesA(aPath.c_str()) != INVALID_FILE_ATTRIBUTES );

		if (tiles = al_load_bitmap((char*)aPath.c_str()) )
			return true;
		else
			return false;
	}

	void TileBitmap::SetTargetBitmapAndClear(Bitmap aTargetBitmap, unsigned int R, unsigned int B, unsigned int G){
		DASSERT(aTargetBitmap);
		DASSERT((R>=0 && R<256 ) && (G>=0 && G<256 ) && (B>=0 && B<256 ) );

		al_set_target_bitmap(aTargetBitmap);
		al_clear_to_color(al_map_rgb(R, G, B));
	}

	void TileBitmap::PutTile (Bitmap aBitmap, Dim destX, Dim destY, Index tileIndx) const{
		DASSERT(aBitmap == al_get_target_bitmap() );
		DASSERT(tileIndx>=0 && tileIndx<256 );

		if (tileIndx != 0){
			al_draw_bitmap_region(tiles, TerrainU::TileX(tileIndx), TerrainU::TileY(tileIndx), TILE_SIZE, TILE_SIZE,
											destX, destY, NULL);
		}
	}

	Index TileBitmap::GetPointedTile (Dim x, Dim y) const{
		return TerrainU::MakeIndex(x,y);
	}

	/*tiles Transparency*/
	bool TileBitmap::IsTileTransparent (Dim row, Dim col) const{
		return false;
	}

	bool TileBitmap::LoadTransparencyInfo (const std::string& aPath){
		DASSERT(GetFileAttributesA(aPath.c_str()) != INVALID_FILE_ATTRIBUTES );
		return false;
	}

	void TileBitmap::ProduceTransparencyInfo (void){
	}

	bool TileBitmap::WriteTransparencyInfo (const std::string& aPath){
		DASSERT(GetFileAttributesA(aPath.c_str()) != INVALID_FILE_ATTRIBUTES );
		return false;
	}