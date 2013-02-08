#ifndef	BITMAPFONTHOLDER_H
#define	BITMAPFONTHOLDER_H

#include "AnimationFilmHolder.h"
#include "Metrics.h"
#include "utilities.h"
#include <map>

#define LETTER_W 16
#define LETTER_H 16

#define FONT_FRAME_BOX 0

#define FONT_START 32 // ' '
#define FONT_END 90// 'Z'

#define DISTANCE_BETWEEN_LETTERS_W 18
#define LETTER_OFFSET(c) DISTANCE_BETWEEN_LETTERS_W*(c - FONT_START)

typedef std::map<unsigned char, Coordinates> FontMap_t;// key=letter , value= x,y in sprite bitmap

enum FontColor_t{white, green, blue, red, yellow };
typedef std::map<FontColor_t, FontMap_t> FontColorMap_t; 

class BitmapFontHolder {

	public:
		static void SingletonCreate(void);
	private:
		static void InitAFont(FontMap_t& aLettersMap, const AnimationFilm* animFilm);

	private:
		static Bitmap fontsBitmap;
		static FontColorMap_t fontsMap;
		static FontMap_t whiteLettersMap;
		static FontMap_t greenLettersMap;
		static FontMap_t blueLettersMap;
		static FontMap_t redLettersMap;
		static FontMap_t yellowLettersMap;

	public:
		static Coordinates GetLetterXY(unsigned char c, FontColor_t color);
		static Bitmap GetFontsBitmap(void);

	private:
		static void DisplayLetter (Dim destX, Dim destY, FontColor_t color, char letter);
	public:
		static void DisplayString (Bitmap at, Dim destX, Dim destY, FontColor_t color, std::string str);

	public:
		static void SingletonCleanUp(void);
};


#endif