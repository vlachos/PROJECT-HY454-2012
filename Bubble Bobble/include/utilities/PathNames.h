#ifndef	PATHNAMES_H
#define	PATHNAMES_H

#include <string>

#define BUBBLE_PATH ".."
#define DATA_FOLDER "data"

#define SOUNDTRACK_FOLDER "soundtrack"

#define BITMAPS_FOLDER "bitmaps"
#define SPRITES_FOLDER "sprites"
#define TERRAIN_FOLDER "terrain"

#define TILES_BITMAP_16 "tiles_bitmap_16x16.png"
#define ACTION_LAYER_INFO "action_layer_info.txt"
const std::string stagePrefix = "stage";
const std::string stagePostfix = "_info.txt";

namespace BubblePathnames{

	extern std::string AppendToPath(std::string aPath, std::string aFile);

	extern std::string GetDataPath();
	extern std::string GetSoundtrackDataPath();
	extern std::string GetBitmapDataPath();
	extern std::string GetSpritesBitmapDataPath();
	extern std::string GetTerrainBitmapDataPath();
	extern std::string GetTilesBitmap();
	extern std::string GetActionLayerInfo();
	extern std::string GetStageInfo(unsigned int stageLevel);

}

#endif