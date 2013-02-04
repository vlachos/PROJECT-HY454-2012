#include "ScoreBoard.h"
#include "MemoryManage.h"
#include "PathNames.h"
#include "BitmapLoader.h"
#include "AnimationFilmHolder.h"
#include "AnimationFilm.h"
#include <algorithm>

typedef std::pair<ScoreBoardFont_t, const AnimationFilm*> FontPair;

	struct DeleteAnimation{
		void operator()(std::pair<ScoreBoardFont_t, const AnimationFilm*> _pair){
			_pair.first = white;
			_pair.second = 0;
		}
	};

	/////////// Constructor / Destructor
	ScoreBoard::ScoreBoard(){
		spritesBitmap = BitmapLoader::Load(BubblePathnames::GetSpritesBitmap() );

		FontsStartXYMap.insert(FontPair(white, AnimationFilmHolder::GetFilm("WhiteLettersFont")) );
		FontsStartXYMap.insert(FontPair(green, AnimationFilmHolder::GetFilm("GreenLettersFont")) );
		FontsStartXYMap.insert(FontPair(blue, AnimationFilmHolder::GetFilm("BlueLettersFont")) );
		FontsStartXYMap.insert(FontPair(red, AnimationFilmHolder::GetFilm("RedLettersFont")) );
		FontsStartXYMap.insert(FontPair(yellow, AnimationFilmHolder::GetFilm("YellowLettersFont")) );
	}

	ScoreBoard::~ScoreBoard(){
		std::for_each(  FontsStartXYMap.begin(),
						FontsStartXYMap.end(),
						DeleteAnimation() );

		FontsStartXYMap.clear();
	}

	/////////// Generate starting points of each letter on the score board
	const AnimationFilm* ScoreBoard::GetFontAnimationFilm(ScoreBoardFont_t font){
		DASSERT(white<=font<=yellow);

		return FontsStartXYMap.find(font)->second;
	}

	Coordinates ScoreBoard::GetLetterXY(unsigned char c, ScoreBoardFont_t color){
		DASSERT(FONT_START <= c <= FONT_END);

		Dim x = GetFontAnimationFilm(color)->GetFrameBox(FONT_FRAME_BOX).GetX();
		Dim y = ScoreBoard::GetFontAnimationFilm(color)->GetFrameBox(FONT_FRAME_BOX).GetY();

		return std::make_pair(x + LETTER_OFFSET(c), y);
	}

	void ScoreBoard::GenerateScoreLettersXY(unsigned int startIndex, std::string scoreStr, ScoreBoardFont_t color) {
		DASSERT(scoreStr.length()+startIndex <= MAX_ROW_LETTER);
		
		for (unsigned int i=startIndex; i < scoreStr.length()+startIndex; ++i){
			scores[i] = GetLetterXY(scoreStr.at(i-startIndex), color);
		}
	}

	void ScoreBoard::GenerateAboveScoreLettersXY(unsigned int startIndex, std::string aboveScoreStr, ScoreBoardFont_t color) {
		DASSERT(aboveScoreStr.length()+startIndex <= MAX_ROW_LETTER);
		
		for (unsigned int i=startIndex; i < aboveScoreStr.length()+startIndex; ++i){
			aboveScores[i] = GetLetterXY(aboveScoreStr.at(i-startIndex), color);
		}
	}


	void ScoreBoard::GenerateScoreBoardInfo(int bubScore, int highScore, int bobScore){
		DASSERT(bubScore <= SCORE_LIMIT && highScore <= SCORE_LIMIT && bobScore <= SCORE_LIMIT);

		//bub score
		if (bubScore != -1){
			GenerateAboveScoreLettersXY(CURSOR_BUB_ABOVE_SCR ,ABOVE_SCORE_TEXT_P1, green);
			GenerateScoreLettersXY(CURSOR_BUB_SCR ,ScoreToString(bubScore), white);
		}
		else{
			GenerateAboveScoreLettersXY(CURSOR_BUB_ABOVE_SCR ,ABOVE_SCORE_TEXT_PRESS1, yellow);
			GenerateScoreLettersXY(CURSOR_BUB_SCR ,TO_START, yellow);
		}
		GenerateScoreLettersXY(CURSOR_BUB_SCR + MAX_SCORE_DIGITS ,BETWEEN_1P_HIGH, white);

		//high score
		GenerateAboveScoreLettersXY(CURSOR_HIGH_ABOVE_SCR ,ABOVE_SCORE_TEXT_HIGH, red);
		GenerateScoreLettersXY(CURSOR_HIGH_SCR ,ScoreToString(highScore), white);
		GenerateScoreLettersXY(CURSOR_HIGH_SCR + MAX_SCORE_DIGITS ,BETWEEN_HIGH_2P, white);

		//bob score
		if (bobScore != -1){
			GenerateAboveScoreLettersXY(CURSOR_BOB_ABOVE_SCR ,ABOVE_SCORE_TEXT_P2, blue);
			GenerateScoreLettersXY(CURSOR_BOB_SCR ,ScoreToString(bobScore), white);
		}
		else{
			GenerateAboveScoreLettersXY(CURSOR_BOB_ABOVE_SCR ,ABOVE_SCORE_TEXT_PRESS2, yellow);
			GenerateScoreLettersXY(CURSOR_BOB_SCR ,TO_START, yellow);
		}
		GenerateScoreLettersXY(CURSOR_BOB_SCR + MAX_SCORE_DIGITS ,BETWEEN_2P_END, white);
	}


	/////////// integer score to string
	std::string ScoreBoard::ScoreToString(int score){
		unsigned int d1 = 1, d2 = 10;
		std::string scoreStr = "";
		std::stringstream ss;
		ss << score;
		for (unsigned i = 0; i < MAX_SCORE_DIGITS - ss.str().length(); ++i){
			scoreStr.append(" ");
		}
		scoreStr.append(ss.str());
		return scoreStr;
	}


	/////////// display
	void ScoreBoard::DisplayLetter(Bitmap at, Dim destX, Dim destY, Coordinates coord){

		al_draw_bitmap_region(spritesBitmap, coord.first, coord.second, LETTER_W, LETTER_H,
										destX, destY, NULL);
	}


	void ScoreBoard::DisplayScoreBoard(Bitmap at, int bubScore, int highScore, int bobScore){
		DASSERT(at == al_get_target_bitmap() );

		GenerateScoreBoardInfo(bubScore, highScore, bobScore);

		for (unsigned int i=0; i < MAX_ROW_LETTER; ++i){
			DisplayLetter(at, i*LETTER_W, 0,ScoreBoard::aboveScores[i]);
			DisplayLetter(at, i*LETTER_W, LETTER_H, ScoreBoard::scores[i]);
		}
	}
