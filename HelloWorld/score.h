#pragma once
#include "Play.h"
#include "constants.h"
#include <array>
#include <stack>
#include <string>

typedef std::array<unsigned int, 5> HighScoreArray;


void DrawHighScores(const int highScores[]);

int GetNumberOfHighScores(const int highScores[]);

void DrawCurrentScore(const int currentScore);

void AddCurrentScoreToHighScore(int& currentScore, int highScores[]);

void LoadHighScores(int highScores[]);