#include <TerrainUtilities.h>

Index MakeIndex (Dim x, Dim y){
	return (y<<COL_SHIFT) | x;
}

byte GetCol (Index indx){
	return indx >> COL_SHIFT;
}
byte GetRow (Index indx){
	return indx & ROW_MASK;
}

Dim TileX (Index indx){
	return MUL_TILE_WIDTH(GetCol(indx));
}
Dim TileY (Index indx){
	return MUL_TILE_HEIGHT(GetRow(indx));
}