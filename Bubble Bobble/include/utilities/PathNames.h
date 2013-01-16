#ifndef	PATHNAMES_H
#define	PATHNAMES_H

#include <string>

#define BUBBLE_PATH ".."
#define DATA_FOLDER "data"

#define SOUNDTRACK_FOLDER "soundtrack"

#define BITMAPS_FOLDER "bitmaps"
#define SPRITES_FOLDER "sprites"
#define TERRAIN_FOLDER "terrain"

std::string AppendToPath(std::string aPath, std::string aFile);

std::string GetDataPath();
std::string GetSoundtrackDataPath();
std::string GetBitmapDataPath();
std::string GetTerrainBitmapDataPath();
std::string GetSpritesBitmapDataPath();

#endif