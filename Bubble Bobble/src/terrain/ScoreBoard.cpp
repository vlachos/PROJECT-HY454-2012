#include "ScoreBoard.h"
#include "MemoryManage.h"
#include "BitmapLoader.h"
#include "AnimationFilmHolder.h"

typedef std::pair<ScoreBoardFont_t, const AnimationFilm*> FontPair;

FontMap_t ScoreBoard::FontStartXY;
ScoreBoard* ScoreBoard::myScoreBoard;
Bitmap ScoreBoard::TextAboveScore[MAX_LETTERS];
Bitmap ScoreBoard::ScoreDigits[MAX_SCORE_DIGITS];

ScoreBoard::ScoreBoard(){
	ScoreBoard::FontStartXY.insert(FontPair(white, AnimationFilmHolder::GetFilm("WhiteLettersFont")) );
	ScoreBoard::FontStartXY.insert(FontPair(green, AnimationFilmHolder::GetFilm("GreenLettersFont")) );
	ScoreBoard::FontStartXY.insert(FontPair(blue, AnimationFilmHolder::GetFilm("BlueLettersFont")) );
	ScoreBoard::FontStartXY.insert(FontPair(red, AnimationFilmHolder::GetFilm("RedLettersFont")) );
	ScoreBoard::FontStartXY.insert(FontPair(yellow, AnimationFilmHolder::GetFilm("YellowLettersFont")) );
}

ScoreBoard::~ScoreBoard(){
	ScoreBoard::FontStartXY.clear();
}

void ScoreBoard::SingeletonCreate(){
	ScoreBoard::myScoreBoard = DNEWCLASS(ScoreBoard,() );
}

const AnimationFilm* ScoreBoard::GetLetterBitmapXY(char c, ScoreBoardFont_t font){
	return ScoreBoard::FontStartXY.find(font)->second;
}

void ScoreBoard::DisplayScore(unsigned int bubScore, unsigned int bobScore){}

void ScoreBoard::SingeletonCleanUp(){
	delete ScoreBoard::myScoreBoard;
}