#ifndef	SCOREBOARD_H
#define	SCOREBOARD_H

#include "BitmapFontHolder.h"
#include "Metrics.h"
#include "utilities.h"
#include <map>
#include <vector>

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


class ScoreBoard{

	public:
		ScoreBoard();
		~ScoreBoard();

	private:
		std::vector<Rect> aboveScores;
		std::vector<Rect> scores;

	private:
		void GenerateScoreLettersXY(unsigned int startIndex, std::string scoreStr, FontColor_t color);
		void GenerateAboveScoreLettersXY(unsigned int startIndex, std::string aboveScoreStr, FontColor_t color);
		void GenerateScoreBoardInfo(int bubScore, int highScore, int bobScore);
		std::string ScoreToString(int score);
		void DisplayLetter(Bitmap at, int destX, int destY, Rect rect);

	public:
		void DisplayScoreBoard (Bitmap at, int bubScore, int highScore, int bobScore);

};

#endif