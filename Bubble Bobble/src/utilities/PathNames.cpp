#include <PathNames.h>
#include <sstream>
#include "MemoryManage.h"



std::string BubblePathnames::AppendToPath(std::string aPath, std::string aFile){
	return aPath.append("\\").append(aFile);
}

std::string BubblePathnames::GetDataPath(){
	return AppendToPath(BUBBLE_PATH, DATA_FOLDER);
}
std::string BubblePathnames::GetSoundtrackDataPath(){
	return AppendToPath(GetDataPath(), SOUNDTRACK_FOLDER);
}
std::string BubblePathnames::GetBitmapDataPath(){
	return AppendToPath(GetDataPath(), BITMAPS_FOLDER);
}

std::string BubblePathnames::GetSpritesBitmapDataPath(){
	return AppendToPath(GetBitmapDataPath(), SPRITES_FOLDER);
}

std::string BubblePathnames::GetTerrainBitmapDataPath(){
	return AppendToPath(GetBitmapDataPath(), TERRAIN_FOLDER);
}

std::string BubblePathnames::GetTilesBitmap(){
	return AppendToPath(GetTerrainBitmapDataPath(), TILES_BITMAP_16);
}

std::string BubblePathnames::GetActionLayerInfo(){
	return AppendToPath(GetTerrainBitmapDataPath(), ACTION_LAYER_INFO);
}

std::string BubblePathnames::GetTestActionLayerInfo(){
	return AppendToPath(GetTerrainBitmapDataPath(), TEST_INFO);
}

std::string BubblePathnames::GetStageInfo(unsigned int stageLevel){
	DASSERT(stageLevel > 0 && stageLevel <=11);

	std::stringstream ss;
	ss << stageLevel;
	return BubblePathnames::AppendToPath(BubblePathnames::GetTerrainBitmapDataPath(), stagePrefix + ss.str() + stagePostfix);
}

