#include <PathNames.h>
#include <sstream>
#include "MemoryManage.h"


void SingletonCreate (void){}

std::string BubblePathnames::AppendToPath(std::string aPath, std::string aFile){
	return aPath.append("\\").append(aFile);
}

std::string BubblePathnames::GetDataPath(){
	return BubblePathnames::AppendToPath(BUBBLE_PATH, DATA_FOLDER);
}
std::string BubblePathnames::GetSoundtrackDataPath(){
	return BubblePathnames::AppendToPath(GetDataPath(), SOUNDTRACK_FOLDER);
}
std::string BubblePathnames::GetBitmapDataPath(){
	return BubblePathnames::AppendToPath(GetDataPath(), BITMAPS_FOLDER);
}

/*sprites*/
std::string BubblePathnames::GetSpritesBitmapDataPath(){
	return BubblePathnames::AppendToPath(GetBitmapDataPath(), SPRITES_FOLDER);
}
std::string BubblePathnames::GetSpritesInfoDataPath(){
	return BubblePathnames::AppendToPath(GetSpritesBitmapDataPath(), INFO_FOLDER);
}

std::string BubblePathnames::GetSpritesBitmap(){
	return BubblePathnames::AppendToPath(GetSpritesBitmapDataPath(), SPRITES_BITMAP);
}
std::string BubblePathnames::GetAnimationXML(){
	return BubblePathnames::AppendToPath(GetSpritesInfoDataPath(), ANIMATION_XML);
}
std::string BubblePathnames::GetSpritesXML(){
	return BubblePathnames::AppendToPath(GetSpritesInfoDataPath(), SPRITE_XML);
}

/*terrain*/
std::string BubblePathnames::GetTerrainBitmapDataPath(){
	return BubblePathnames::AppendToPath(GetBitmapDataPath(), TERRAIN_FOLDER);
}
std::string BubblePathnames::GetTerrainInfoDataPath(){
	return BubblePathnames::AppendToPath(GetTerrainBitmapDataPath(), INFO_FOLDER);
}

std::string BubblePathnames::GetTilesBitmap(){
	return BubblePathnames::AppendToPath(GetTerrainBitmapDataPath(), TILES_BITMAP_16);
}
std::string BubblePathnames::GetActionLayerInfo(){
	return BubblePathnames::AppendToPath(GetTerrainInfoDataPath(), ACTION_LAYER_INFO);
}
std::string BubblePathnames::GetStageInfo(unsigned int stageLevel){
	DASSERT(stageLevel > 0 && stageLevel <=11);

	std::stringstream ss;
	ss << stageLevel;
	return BubblePathnames::AppendToPath(BubblePathnames::GetTerrainInfoDataPath(), stagePrefix + ss.str() + stagePostfix);
}
std::string BubblePathnames::GetTestActionLayerInfo(){
	return BubblePathnames::AppendToPath(GetTerrainInfoDataPath(), TEST_INFO);
}

void SingletonCleanUp (void){}

