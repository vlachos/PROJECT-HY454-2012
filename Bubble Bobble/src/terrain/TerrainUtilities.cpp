#include <TerrainUtilities.h>

Index MakeIndex (Dim x, Dim y){
	return MUL_TILE_SIZE(y) | x;
}

Dim GetCol (Index indx){
	return DIV_TILE_SIZE(indx);
}
Dim GetRow (Index indx){
	return indx & ROW_MASK;
}

Dim TileX (Index indx){
	return MUL_TILE_SIZE(GetCol(indx));
}
Dim TileY (Index indx){
	return MUL_TILE_SIZE(GetRow(indx));
}
