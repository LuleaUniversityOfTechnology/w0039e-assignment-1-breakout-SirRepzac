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

    // Destructor to clean up memory


    // A method to initialize the array
    void allocate(size_t newSize)
    {
        delete[] scores;  // Clean up old memory, if any
        amount = newSize;
        scores = new unsigned int[amount];  // Allocate new memory
        for (int i = 0; i < amount; i++)
        {
            scores[i] = 0;
        }
    }

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

//int GetNumberOfHighScores(const Highscores highscores);

void DrawCurrentScore(const int highscores);

void AddCurrentScoreToHighScore(int& currentScore, Highscores& highScores);

void LoadHighScores(Highscores& highScores);

void WriteHighscoreToFile(Highscores& highScores);
