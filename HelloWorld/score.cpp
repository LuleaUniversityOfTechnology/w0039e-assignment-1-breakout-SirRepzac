#include "Play.h"
#include "score.h"
#include "game.h"
#include <fstream>
using namespace std;


void DrawHighScores(const Highscores highScores)
{
	int realAmount = 0;
	for (int i = 0; i < highScores.amount; i++)
	{
		if (highScores.scores[i] != 0)
		{
			realAmount++;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if (highScores.scores[i] != 0)
		{
			std::string scoreString = std::to_string(highScores.scores[i]);
			const char* toDraw = scoreString.c_str();

			Play::DrawDebugText({ DISPLAY_WIDTH - 30, 10 + ((realAmount > 5) ? 5 : realAmount) * 15 - i * 15 }, toDraw, Play::cWhite);
		}
	}
}

void DrawCurrentScore(const int currentScore)
{
	std::string scoreString = std::to_string(currentScore);
	const char* toDraw = scoreString.c_str();

	Play::DrawDebugText({10, 10}, toDraw, Play::cWhite);
}

void AddCurrentScoreToHighScore(int& currentScore, Highscores& highScores)
{
	for (int i = 0; i < highScores.amount; i++)
	{
		if (currentScore > highScores.scores[i])	//new score is bigger than any of the previous scores
		{
			for (int j = highScores.amount; j > i; j--)			//moves all scores smaller than the new score down one step
			{
				if (j < highScores.amount)
					highScores.scores[j] = highScores.scores[j - 1];
			}
			highScores.scores[i] = currentScore;
			return;
		}

	}

}

void LoadHighScores(Highscores& highScores)
{
	ifstream highscoreFile;
	highscoreFile.open("Highscores.txt");
	int amountOfLines = 0;
	int tempInt = 0;
	std:string line;
	while (std::getline(highscoreFile, line))
	{
		const char* charLine = line.c_str();
		sscanf_s(charLine, "%d", &tempInt);
		highScores.add(tempInt);

	}
	while (highScores.amount < 5)	//fill up the first 5 lines with 0 if the text document didnt contain 5 lines
	{
		highScores.add(0);

	}

	
}



void WriteHighscoreToFile(Highscores& highScores)
{
	ofstream highscoreFile;
	highscoreFile.open("Highscores.txt");

	for (int i = 0; i < highScores.amount; i++)
	{
		highscoreFile << std::to_string(highScores.scores[i]) << "\n";
	}
	highscoreFile.close();
}