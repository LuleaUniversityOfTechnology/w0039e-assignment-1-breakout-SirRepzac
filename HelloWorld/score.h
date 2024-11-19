#pragma once

#include "Play.h"
#include "Paddle.h"
#include "constants.h"
#include <array>
#include <stack>
#include <string>

struct Highscores
{
	unsigned int* score = nullptr;
    size_t amount = 0;

    Highscores() = default;

    void add(int addInt)
    {
        int* tempStorage = new int[amount]();
        for (int i = 0; i < amount; i++)
        {
            tempStorage[i] = score[i];
        }
        amount++;
        delete[] score;
        score = nullptr;
        score = new unsigned int[amount];
        for (int i = 0; i < amount - 1; i++)
        {
            score[i] = tempStorage[i];
        }
        score[amount-1] = addInt;
        delete[] tempStorage;
    }

    void removeLast()
    {
        int* tempStorage = new int[amount]();
        for (int i = 0; i < amount; i++)
        {
            tempStorage[i] = score[i];
        }
        amount--;
        delete[] score;
        score = nullptr;
        score = new unsigned int[amount];
        for (int i = 0; i < amount; i++)
        {
            score[i] = tempStorage[i];
        }
        delete[] tempStorage;
    }
};

typedef std::array<unsigned int, 5> HighScoreArray;

void DrawHighScores(const Highscores highscores, Paddle& paddle);

void DrawCurrentScore(const int highscores);

void AddCurrentScoreToHighScore(int& currentScore, Highscores& highScores);

void RemoveZeroScores(Highscores& highScores);

void LoadHighScores(Highscores& highScores);

void Sort(Highscores& highScores);

void WriteHighscoreToFile(Highscores& highScores);
