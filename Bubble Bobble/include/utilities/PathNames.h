#ifndef	PATHNAMES_H
#define	PATHNAMES_H

#include <string>

#define BUBBLE_PATH ".."
	#define DATA_FOLDER "data"
		#define SOUNDTRACK_FOLDER "soundtrack"

		#define BITMAPS_FOLDER "bitmaps"
			#define SPRITES_FOLDER "sprites"
			#define TERRAIN_FOLDER "terrain"

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

#endif