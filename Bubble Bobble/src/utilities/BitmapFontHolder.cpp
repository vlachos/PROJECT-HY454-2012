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
		fontsBitmap = BitmapLoader::Load(PathNames::GetSpritesBitmap() );

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
	Rect BitmapFontHolder::GetLetterRect(unsigned char c, FontColor_t color){
		Coordinates coord = fontsMap.find(color)->second.find(c)->second;
		return Rect(coord.first, coord.second, LETTER_W, LETTER_H);
	}

	Coordinates BitmapFontHolder::GetLetterXY(unsigned char c, FontColor_t color){
		DASSERT( FONT_START <= c  && c <= FONT_END );
		return fontsMap.find(color)->second.find(c)->second;
	}

	Bitmap BitmapFontHolder::GetFontsBitmap(void) { return fontsBitmap; }


	//////////// display
	void BitmapFontHolder::DisplayLetter (Dim destX, Dim destY, FontColor_t color, char letter){

		Coordinates coord = fontsMap.find(color)->second.find(letter)->second;

		al_draw_bitmap_region(fontsBitmap, coord.first, coord.second, LETTER_W, LETTER_H,
										destX, destY, NULL);
	}

	Bitmap BitmapFontHolder::GetWordBitmap(std::string str, FontColor_t color){
		DASSERT( !str.empty() );

		Bitmap prevAt = al_get_target_bitmap();
		Bitmap wordBitmap;
		al_set_target_bitmap(wordBitmap);

		for (unsigned int i = 0; i < str.length() ; ++i){
			DisplayLetter (i*LETTER_W, 0, color, (unsigned char)str[i]);
		}
		al_set_target_bitmap(prevAt);

		return wordBitmap;
	}

	std::vector<Rect> BitmapFontHolder::GetWordRects(std::string str, FontColor_t color){
		DASSERT( !str.empty() );

		std::vector<Rect> v;
		for (unsigned int i = 0; i<str.length(); ++i){
			DASSERT( FONT_START <= (unsigned char)str[i] &&  (unsigned char)str[i] <= FONT_END );
			v.push_back( GetLetterRect( (unsigned char)str[i], color) );
		}
		return v;
	}

	void BitmapFontHolder::DisplayString (Bitmap at, Dim destX, Dim destY, FontColor_t color, std::string str){
		DASSERT(at == al_get_target_bitmap() );
		for (unsigned int i = 0; i < str.length(); ++i){
			DisplayLetter (destX+i*LETTER_W, destY, color, str.at(i) );
		}
	}


	//////////// Destruction
	void BitmapFontHolder::SingletonCleanUp() {  }