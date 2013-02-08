#ifndef	BITMAPFONTS_H
#define	BITMAPFONTS_H

#include "Metrics.h"
#include "utilities.h"

#define LETTER_W 16
#define LETTER_H 16

#define FONT_FRAME_BOX 0

#define FONT_START 32 // ' '
#define FONT_END 90// 'Z'

#define DISTANCE_BETWEEN_LETTERS_W 18
#define LETTER_OFFSET(c) DISTANCE_BETWEEN_LETTERS_W*(c - FONT_START)

class BitmapFonts {

};


#endif