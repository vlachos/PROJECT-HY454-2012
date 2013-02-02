#ifndef	SCOREBOARD_H
#define	SCOREBOARD_H

#include "Metrics.h"
#include "utilities.h"
#include "AnimationFilm.h"
#include <map>

#define MY_ASCII_START 33 // '!'
#define MY_ASCII_END 90// 'Z'

#define LETTER_W 16
#define LETTER_H 16

#define MAX_LETTERS 10
#define MAX_SCORE_DIGITS 8

enum ScoreBoardFont_t{white, green, blue, red, yellow };
typedef std::map<ScoreBoardFont_t, const AnimationFilm*> FontMap_t;

class ScoreBoard{

	private:
		ScoreBoard();
		~ScoreBoard();

	private:
		static ScoreBoard* myScoreBoard;
		static FontMap_t FontStartXY;
		static Bitmap TextAboveScore[MAX_LETTERS];
		static Bitmap ScoreDigits[MAX_SCORE_DIGITS];

	public:
		static void SingeletonCreate();

	private:
		static const AnimationFilm* GetLetterBitmapXY(char c, ScoreBoardFont_t color);

	public:
		static void DisplayScore(unsigned int bubScore, unsigned int bobScore);

	public:
		static void SingeletonCleanUp();
};

#endif