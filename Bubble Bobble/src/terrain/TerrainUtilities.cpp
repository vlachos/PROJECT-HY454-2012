#include <TerrainUtilities.h>

Index MakeIndex (Dim x, Dim y){
	return (y<<COL_SHIFT) | x;
}

Dim GetCol (Index indx){
	return indx >> COL_SHIFT;
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


/*index points to pixels*/
Index MakeIndex2 (byte row, byte col){
	return (MUL_TILE_SIZE(col) << TILEX_SHIFT) | MUL_TILE_SIZE(row);
}
Dim TileX2 (Index2 index){
	return index >> TILEX_SHIFT;
}
Dim TileY2 (Index2 index){
	return index & TILEY_MASK;
}