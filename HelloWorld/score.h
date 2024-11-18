#pragma once

#include "Play.h"
#include "constants.h"
#include <array>
#include <stack>
#include <string>


struct Highscores
{
	int* scores;
	int amount;
};

typedef std::array<unsigned int, 5> HighScoreArray;


void DrawHighScores(const Highscores highscores);

//int GetNumberOfHighScores(const Highscores highscores);

void DrawCurrentScore(const int highscores);

void AddCurrentScoreToHighScore(int& currentScore, Highscores& highScores);

void LoadHighScores(Highscores& highScores);

void WriteHighscoreToFile(Highscores& highScores);
