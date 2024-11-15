#include "Play.h"
#include "score.h"
#include <array>
#include <stack>
#include <string>
using namespace std;


void DrawHighScores(const int highScores[])
{

	int nrOfHighScores = GetNumberOfHighScores(highScores);

	for (int i = 0; i < nrOfHighScores; i++)
	{
		std::string scoreString = std::to_string(highScores[i]);
		const char* toDraw = scoreString.c_str();

		Play::DrawDebugText({ DISPLAY_WIDTH - 50, 10 + nrOfHighScores * 20 - i * 20 }, toDraw, Play::cWhite);
	}
}

int GetNumberOfHighScores(const int highScores[])
{
	for (int i = 0; i < 5; i++)
	{
		if (highScores[i] == 0)
		{
			return i;
		}
	}
	return 5;
}

void DrawCurrentScore()
{

}

void ResetCurrentScore()
{

}

void AddCurrentScoreToHighScore()
{

}

void LoadHighScores(int highScores[])
{
	highScores[0] = 500;
	highScores[1] = 399;
	highScores[2] = 50;
	highScores[3] = 20;
	highScores[4] = 0;
}