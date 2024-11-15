#pragma once
#include "Play.h"
#include "constants.h"
#include <array>

	typedef std::array<unsigned int, 5> HighScoreArray;


void DrawHighScores(const int highScores[]);

int GetNumberOfHighScores(const int highScores[]);

void DrawCurrentScore();

void ResetCurrentScore();

void AddCurrentScoreToHighScore();

void LoadHighScores(int highScores[]);