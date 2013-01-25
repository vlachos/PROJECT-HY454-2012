#ifndef	PATHNAMES_H
#define	PATHNAMES_H

#include <string>

#define BUBBLE_PATH ".."
#define DATA_FOLDER "data"

#define SOUNDTRACK_FOLDER "soundtrack"

#define BITMAPS_FOLDER "bitmaps"
#define INFO_FOLDER "info"
#define SPRITES_FOLDER "sprites"

#define SPRITES_BITMAP "sprites.png"
#define ANIMATION_XML "animation_data.xml"
#define SPRITE_XML "sprites_data.xml"

#define TERRAIN_FOLDER "terrain"

#define TILES_BITMAP_16 "tiles_bitmap_16x16.png"
#define ACTION_LAYER_INFO "action_layer_info.txt"
#define TEST_INFO "test_terrain_info.txt"
const std::string stagePrefix = "stage";
const std::string stagePostfix = "_info.txt";


class BubblePathnames{

	public:
		static void	SingletonCreate (void);

	private:
		static std::string AppendToPath(std::string aPath, std::string aFile);

	public:
		static std::string GetDataPath();
		static std::string GetSoundtrackDataPath();
		static std::string GetBitmapDataPath();

		static std::string GetSpritesBitmapDataPath();
		static std::string GetSpritesInfoDataPath();
		static std::string GetSpritesBitmap();
		static std::string GetAnimationXML();
		static std::string GetSpritesXML();

		static std::string GetTerrainBitmapDataPath();
		static std::string GetTerrainInfoDataPath();
		static std::string GetTilesBitmap();
		static std::string GetActionLayerInfo();
		static std::string GetStageInfo(unsigned int stageLevel);
		static std::string GetTestActionLayerInfo();

	public:
		static void	SingletonCleanUp (void);
};

#endif