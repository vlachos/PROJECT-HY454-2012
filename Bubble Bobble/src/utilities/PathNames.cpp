#include <PathNames.h>
#include <sstream>
#include "MemoryManage.h"


void SingletonCreate (void){}

std::string PathNames::AppendToPath(std::string aPath, std::string aFile){
	return aPath.append("\\").append(aFile);
}

std::string PathNames::GetDataPath(){
	return AppendToPath(BUBBLE_PATH, DATA_FOLDER);
}
std::string PathNames::GetSoundtrackDataPath(){
	return AppendToPath(GetDataPath(), SOUNDTRACK_FOLDER);
}
std::string PathNames::GetBitmapDataPath(){
	return AppendToPath(GetDataPath(), BITMAPS_FOLDER);
}

/*sprites*/
std::string PathNames::GetSpritesBitmapDataPath(){
	return AppendToPath(GetBitmapDataPath(), SPRITES_FOLDER);
}
std::string PathNames::GetSpritesInfoDataPath(){
	return AppendToPath(GetSpritesBitmapDataPath(), INFO_FOLDER);
}

std::string PathNames::GetSpritesBitmap(){
	return AppendToPath(GetSpritesBitmapDataPath(), SPRITES_BITMAP);
}
std::string PathNames::GetAnimationXML(){
	return AppendToPath(GetSpritesInfoDataPath(), ANIMATION_XML);
}
std::string PathNames::GetSpritesXML(){
	return AppendToPath(GetSpritesInfoDataPath(), SPRITE_XML);
}

/*terrain*/
std::string PathNames::GetTerrainBitmapDataPath(){
	return AppendToPath(GetBitmapDataPath(), TERRAIN_FOLDER);
}
std::string PathNames::GetTerrainInfoDataPath(){
	return AppendToPath(GetTerrainBitmapDataPath(), INFO_FOLDER);
}

std::string PathNames::GetTerrainStageIndexInfoDataPath(){
	return AppendToPath(GetTerrainInfoDataPath(), STAGE_INDEX_FOLDER);
}

std::string PathNames::GetTerrainStageSolidityInfoDataPath(){
	return AppendToPath(GetTerrainInfoDataPath(), STAGE_SOLIDITY_FOLDER);
}

std::string PathNames::GetTilesBitmap(){
	return AppendToPath(GetTerrainBitmapDataPath(), TILES_BITMAP_16);
}
std::string PathNames::GetActionLayerInfo(){
	return AppendToPath(GetTerrainInfoDataPath(), ACTION_LAYER_INFO);
}
std::string PathNames::GetStageIndexInfo(unsigned int stageLevel){
	DASSERT(stageLevel >= 0 && stageLevel <=11);

	std::stringstream ss;
	ss << stageLevel;
	return AppendToPath(GetTerrainStageIndexInfoDataPath(), stagePrefix + ss.str() + stageIndexPostfix);
}

std::string PathNames::GetStageSldtyInfo(unsigned int stageLevel){
	DASSERT(stageLevel >= 0 && stageLevel <=11);

	std::stringstream ss;
	ss << stageLevel;
	return AppendToPath(GetTerrainStageSolidityInfoDataPath(), stagePrefix + ss.str() + stageSldtyPostfix);
}

std::string PathNames::GetTestActionLayerIndexInfo(){
	return AppendToPath(GetTerrainInfoDataPath(), TEST_INDEX_INFO);
}
std::string PathNames::GetTestActionLayerSldtyInfo(){
	return AppendToPath(GetTerrainInfoDataPath(), TEST_SLDTY_INFO);
}

void SingletonCleanUp (void){}

