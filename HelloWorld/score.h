#pragma once

#include "Play.h"
#include "constants.h"
#include <array>
#include <stack>
#include <string>

struct Highscores
{
	unsigned int* scores = nullptr;
    size_t amount = 0;

    Highscores() = default;

    void add(int addInt)
    {
        int* temp = new int[amount]();
        for (int i = 0; i < amount; i++)
        {
            temp[i] = scores[i];
        }
        amount++;
        delete[] scores;
        scores = nullptr;
        scores = new unsigned int[amount];
        for (int i = 0; i < amount - 1; i++)
        {
            scores[i] = temp[i];
        }
        scores[amount-1] = addInt;
        delete[] temp;
    }
};

typedef std::array<unsigned int, 5> HighScoreArray;

void DrawHighScores(const Highscores highscores);

int GetRealAmountOfHighScores(const Highscores highScores);

void DrawCurrentScore(const int highscores);

void AddCurrentScoreToHighScore(int& currentScore, Highscores& highScores);

void LoadHighScores(Highscores& highScores);

void Sort(Highscores& highScores);

void WriteHighscoreToFile(Highscores& highScores);
