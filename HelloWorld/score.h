#pragma once
#include "Play.h"
#include "constants.h"

void DrawHighScores(const int highScores[]);

int GetNumberOfHighScores(const int highScores[]);

void DrawCurrentScore(const int currentScore);

void ResetCurrentScore();

void AddCurrentScoreToHighScore(int& currentScore, int highScores[]);

void LoadHighScores(int highScores[]);