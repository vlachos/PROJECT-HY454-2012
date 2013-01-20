#include <TerrainUtilities.h>

Index TerrainU::MakeIndex (Dim x, Dim y){
	return MUL_TILE_SIZE(y) | x;
}

Dim TerrainU::GetCol (Index indx){
	return indx & ROW_MASK;
}
Dim TerrainU::GetRow (Index indx){
	return DIV_TILE_SIZE(indx);
}

Dim TerrainU::TileX (Index indx){
	return MUL_TILE_SIZE(GetCol(indx));
}
Dim TerrainU::TileY (Index indx){
	return MUL_TILE_SIZE(GetRow(indx));
}
