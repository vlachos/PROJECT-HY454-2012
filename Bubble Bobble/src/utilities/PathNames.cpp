#include <PathNames.h>

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
std::string GetTerrainBitmapDataPath(){
	return AppendToPath(GetBitmapDataPath(), TERRAIN_FOLDER);
}
std::string GetSpritesBitmapDataPath(){
	return AppendToPath(GetBitmapDataPath(), SPRITES_FOLDER);
}