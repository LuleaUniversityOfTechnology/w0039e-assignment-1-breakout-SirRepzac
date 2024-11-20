#pragma once

#include "Play.h"
#include "Paddle.h"
#include "constants.h"

class Highscores
{
public:
	unsigned int* score = nullptr;      // Dynamically allocated array, size is declared later
	int amount = 0;                     // Amount of high scores (values in the array)

	void add(int addInt);
	void removeLast();
};

void DrawHighScores(const Highscores highscores, Paddle& paddle);

void DrawCurrentScore(const int highscores);

void AddCurrentScoreToHighScore(int& currentScore, Highscores& highScores);

void RemoveZeroScores(Highscores& highScores);

void LoadHighScores(Highscores& highScores);

void Sort(Highscores& highScores);

void WriteHighscoreToFile(Highscores& highScores);
