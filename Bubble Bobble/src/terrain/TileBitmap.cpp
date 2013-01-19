#include <TileBitmap.h>
#include "MemoryManage.h"

	/*public*/
	TileBitmap::TileBitmap(){
		LoadTiles (GetTilesBitmap() );
		DASSERT(tiles );
	}

	TileBitmap::~TileBitmap(){
		DDELETE(tiles);
//		DDELARR(tileTransparency);
	}

	/*private*/
	bool TileBitmap::LoadTiles (const std::string& aPath ){
		DASSERT(GetFileAttributesA(aPath.c_str()) != INVALID_FILE_ATTRIBUTES );

		if (tiles = al_load_bitmap((char*) aPath.c_str()) )
			return true;
		else
			return false;
	}

	/*public*/
	void TileBitmap::SetTargetBitmapAndClear(Bitmap aTargetBitmap, unsigned int R, unsigned int B, unsigned int G){
		DASSERT(aTargetBitmap);
		DASSERT((R>=0 && R<256 ) && (G>=0 && G<256 ) && (B>=0 && B<256 ) );

		al_set_target_bitmap(aTargetBitmap);
		al_clear_to_color(al_map_rgb(R, G, B));
	}

	void TileBitmap::PutTile (Bitmap aBitmap, Dim sourceX, Dim sourceY, Index tileIndx) const{
		DASSERT(aBitmap == al_get_target_bitmap() );
		DASSERT((sourceX>=0 && sourceY>=0) && (sourceX<=MAX_WIDTH-TILE_SIZE  && sourceY<=MAX_HEIGHT-TILE_SIZE) );
		DASSERT(tileIndx>=0 && tileIndx<256 );

		if (tileIndx){
			al_draw_bitmap_region(aBitmap, sourceX, sourceY, TILE_SIZE, TILE_SIZE,
											TileX(tileIndx), TileY(tileIndx), NULL);
		}
	}

	Index TileBitmap::GetPointedTile (Dim x, Dim y) const{
		return MakeIndex(x,y);
	}

	/*private*/
	bool TileBitmap::IsTileTransparent (Dim row, Dim col) const{
		return false;
	}

	/*not needed for now, probably will also not be needed later*/

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