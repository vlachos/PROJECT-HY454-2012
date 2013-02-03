#ifndef	SCOREBOARD_H
#define	SCOREBOARD_H

#include "Metrics.h"
#include "utilities.h"
#include "AnimationFilm.h"
#include <map>

#define LETTER_W 16
#define LETTER_H 16

#define FONT_FRAME_BOX 0

#define FONT_START 32 // ' '
#define FONT_END 90// 'Z'

#define DISTANCE_BETWEEN_LETTERS_W 18
#define LETTER_OFFSET(c) DISTANCE_BETWEEN_LETTERS_W*(c - FONT_START)

#define MAX_ROW_LETTER 32
#define MAX_SCORE_DIGITS 8
#define SCORE_LIMIT 999999999

#define BETWEEN_1P_HIGH	"   "
#define BETWEEN_HIGH_2P	"   "
#define BETWEEN_2P_END	"  "

#define TO_START "TO START"
#define ABOVE_SCORE_TEXT_P1		"    1UP    "
#define ABOVE_SCORE_TEXT_PRESS1 " PRESS 1   "
#define ABOVE_SCORE_TEXT_HIGH	"HIGH SCORE"
#define ABOVE_SCORE_TEXT_P2		"     2UP   "
#define ABOVE_SCORE_TEXT_PRESS2	"  PRESS 2  "


#define CURSOR_BUB_ABOVE_SCR 0
#define CURSOR_BUB_SCR 0
#define CURSOR_HIGH_ABOVE_SCR 11
#define CURSOR_HIGH_SCR MAX_SCORE_DIGITS + 3
#define CURSOR_BOB_ABOVE_SCR 21
#define CURSOR_BOB_SCR CURSOR_HIGH_SCR + MAX_SCORE_DIGITS + 3


enum ScoreBoardFont_t{white, green, blue, red, yellow };
typedef std::map<ScoreBoardFont_t, const AnimationFilm*> FontMap_t;

class ScoreBoard{

	public:
		ScoreBoard();
		~ScoreBoard();

	private:
		Bitmap spritesBitmap;
		FontMap_t FontsStartXYMap;
		Coordinates aboveScores[MAX_ROW_LETTER];
		Coordinates scores[MAX_ROW_LETTER];

	private:
		const AnimationFilm* GetFontAnimationFilm(ScoreBoardFont_t color);
		Coordinates GetLetterXY(unsigned char c, ScoreBoardFont_t font);
		void GenerateScoreLettersXY(unsigned int startIndex, std::string scoreStr, ScoreBoardFont_t color);
		void GenerateAboveScoreLettersXY(unsigned int startIndex, std::string aboveScoreStr, ScoreBoardFont_t color);
		void GenerateScoreBoardInfo(int bubScore, int highScore, int bobScore);
		std::string ScoreToString(int score);

	private:
		void DisplayLetter (Bitmap at, Dim destX, Dim destY, Coordinates coord);
	public:
		void DisplayScoreBoard (Bitmap at, int bubScore, int highScore, int bobScore);

};

#endif