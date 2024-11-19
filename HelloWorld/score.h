#pragma once

#include "Play.h"
#include "Paddle.h"
#include "constants.h"
#include <array>
#include <stack>
#include <string>

struct Highscores
{
	unsigned int* score = nullptr;      // Dynamically allocated array, size is declared later
    int amount = 0;                     // Amount of high scores (values in the array)

    Highscores() = default;

    void add(int addInt)
    {
        unsigned int* tempStorage = new unsigned int[amount]();   
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
        unsigned int* tempStorage = new unsigned int[amount]();
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

void DrawHighScores(const Highscores highscores, Paddle& paddle);

void DrawCurrentScore(const int highscores);

void AddCurrentScoreToHighScore(int& currentScore, Highscores& highScores);

void RemoveZeroScores(Highscores& highScores);

void LoadHighScores(Highscores& highScores);

void Sort(Highscores& highScores);

void WriteHighscoreToFile(Highscores& highScores);
