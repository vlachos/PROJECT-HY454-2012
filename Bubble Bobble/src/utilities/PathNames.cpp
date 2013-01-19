#include <PathNames.h>
#include <sstream>
#include "MemoryManage.h"

std::string AppendToPath(std::string aPath, std::string aFile){
	return aPath.append("\\").append(aFile);
}

std::string GetDataPath(){
	return AppendToPath(BUBBLE_PATH, DATA_FOLDER);
}
std::string GetSoundtrackDataPath(){
	return AppendToPath(GetDataPath(), SOUNDTRACK_FOLDER);
}
std::string GetBitmapDataPath(){
	return AppendToPath(GetDataPath(), BITMAPS_FOLDER);
}

std::string GetSpritesBitmapDataPath(){
	return AppendToPath(GetBitmapDataPath(), SPRITES_FOLDER);
}

std::string GetTerrainBitmapDataPath(){
	return AppendToPath(GetBitmapDataPath(), TERRAIN_FOLDER);
}

std::string GetTilesBitmap(){
	return AppendToPath(GetTerrainBitmapDataPath(), TILES_BITMAP_16);
}

std::string GetActionLayerInfo(unsigned int stageLevel){
	return AppendToPath(GetTerrainBitmapDataPath(), ACTION_LAYER_INFO);
}

std::string GetStageInfo(unsigned int stageLevel){
	DASSERT(stageLevel > 0 && stageLevel <=11);

	std::stringstream ss;
	ss << stageLevel;
	return AppendToPath(GetTerrainBitmapDataPath(), stagePrefix + ss.str() + stagePostfix);
}

