#include "BitmapFontHolder.h"
#include "BitmapLoader.h"
#include "PathNames.h"

typedef std::pair<unsigned char, Coordinates> BitLetterPair;
typedef std::pair<FontColor_t, FontMap_t> FontPair;


	Bitmap BitmapFontHolder::fontsBitmap;
	FontColorMap_t BitmapFontHolder::fontsMap;
	FontMap_t BitmapFontHolder::whiteLettersMap;
	FontMap_t BitmapFontHolder::greenLettersMap;
	FontMap_t BitmapFontHolder::blueLettersMap;
	FontMap_t BitmapFontHolder::redLettersMap;
	FontMap_t BitmapFontHolder::yellowLettersMap;


	//////////// Initialization
	void BitmapFontHolder::SingletonCreate() {
		fontsBitmap = BitmapLoader::Load(BubblePathnames::GetSpritesBitmap() );

		InitAFont(whiteLettersMap, AnimationFilmHolder::GetFilm("WhiteLettersFont"));
		InitAFont(greenLettersMap, AnimationFilmHolder::GetFilm("GreenLettersFont"));
		InitAFont(blueLettersMap, AnimationFilmHolder::GetFilm("BlueLettersFont"));
		InitAFont(redLettersMap, AnimationFilmHolder::GetFilm("RedLettersFont"));
		InitAFont(yellowLettersMap, AnimationFilmHolder::GetFilm("YellowLettersFont"));

		fontsMap.insert( FontPair(white, whiteLettersMap) );
		fontsMap.insert( FontPair(green, greenLettersMap) );
		fontsMap.insert( FontPair(blue, blueLettersMap) );
		fontsMap.insert( FontPair(red, redLettersMap) );
		fontsMap.insert( FontPair(yellow, yellowLettersMap) );
	}

	void BitmapFontHolder::InitAFont(FontMap_t& aLettersMap, const AnimationFilm* animFilm) {
		Dim _x = animFilm->GetFrameBox(FONT_FRAME_BOX).GetX();
		Dim _y = animFilm->GetFrameBox(FONT_FRAME_BOX).GetY();

		for (unsigned int i=FONT_START; i<=FONT_END; ++i){
			aLettersMap.insert(BitLetterPair((unsigned char)i, Coordinates(_x+LETTER_OFFSET(i), _y)) );
		}
	}


	//////////// accessors
	Coordinates BitmapFontHolder::GetLetterXY(unsigned char c, FontColor_t color){
		return fontsMap.find(color)->second.find(c)->second;
	}

	Bitmap BitmapFontHolder::GetFontsBitmap(void) { return fontsBitmap; }


	//////////// display
	void BitmapFontHolder::DisplayLetter (Dim destX, Dim destY, FontColor_t color, char letter){

		Coordinates coord = fontsMap.find(color)->second.find(letter)->second;

		al_draw_bitmap_region(fontsBitmap, coord.first, coord.second, LETTER_W, LETTER_H,
										destX, destY, NULL);
	}

	void BitmapFontHolder::DisplayString (Bitmap at, Dim destX, Dim destY, FontColor_t color, std::string str){
		DASSERT(at == al_get_target_bitmap() );
		for (unsigned int i = 0; i < str.length(); ++i){
			DisplayLetter (destX*i, destY, color, str.at(i) );
		}
	}


	//////////// Destruction
	void BitmapFontHolder::SingletonCleanUp() {  }