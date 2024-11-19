#include "Play.h"
#include "score.h"
#include "game.h"
#include <fstream>
using namespace std;


void DrawHighScores(const Highscores highScores)
{
	int realAmount = GetRealAmountOfHighScores(highScores);

	for (int i = 0; i < realAmount; i++)
	{
		std::string scoreString = std::to_string(highScores.score[i]);
		const char* toDraw = scoreString.c_str();

		Play::DrawDebugText({ DISPLAY_WIDTH - 30, 10 + ((realAmount > 5) ? 5 : realAmount) * 15 - i * 15 }, toDraw, Play::cWhite); //((realAmount > 5) ? 5 : realAmount) makes it so that a maximum of five highscores can be displayed
	}
}

//returns the amount of high scores that are larger than 0
int GetRealAmountOfHighScores(const Highscores highScores)
{
	int returnAmount = 0;
	for (int i = 0; i < highScores.amount; i++)
	{
		if (highScores.score[i] > 0)
		{
			returnAmount++;
		}
	}
	return returnAmount;
}

void DrawCurrentScore(const int currentScore)
{
	std::string scoreString = std::to_string(currentScore);
	const char* toDraw = scoreString.c_str();

	Play::DrawDebugText({ 10, 10 }, toDraw, Play::cWhite);
}

void AddCurrentScoreToHighScore(int& currentScore, Highscores& highScores)
{
	for (int i = 0; i < highScores.amount; i++)
	{
		if (currentScore < highScores.score[i])	//a check for if new score is bigger than any of the previous scores
			continue;

		highScores.add(0);			//adds a "0" to extend the array, thus making the previously smallest number fit
		for (int j = highScores.amount; j > i; j--)			//moves all scores smaller than the new score down one step
		{
			if (j < highScores.amount)
			{
				highScores.score[j] = highScores.score[j - 1];
			}
		}
		highScores.score[i] = currentScore;
		RemoveZeroScores(highScores);
		return;
	}
}

void RemoveZeroScores(Highscores& highScores)
{
	Sort(highScores);

	if (highScores.amount <= 5)
		return;
	if (highScores.score[highScores.amount - 1] == 0)
	{
		highScores.removeLast();
		RemoveZeroScores(highScores);
	}

}

void LoadHighScores(Highscores& highScores)
{
	ifstream highscoreFile;
	highscoreFile.open("Highscores.txt");
	int newHighScore = 0;
std:string line;
	while (std::getline(highscoreFile, line))		//get lines for as long as possible and store the contents in "line"
	{
		const char* charLine = line.c_str();
		sscanf_s(charLine, "%d", &newHighScore);
		highScores.add(newHighScore);

	}
	while (highScores.amount < 5)	//fill up the first 5 lines with "0" if the text document didnt contain 5 lines
	{
		highScores.add(0);

	}
	Sort(highScores);
}

//Sorts from the biggest score (at index: 0) to smallest score (at index: amount - 1)
void Sort(Highscores& highScores)
{
	for (int i = highScores.amount - 1; i > 0; i--)
	{
		if (highScores.score[i] > highScores.score[i - 1])
		{
			std::swap(highScores.score[i], highScores.score[i - 1]);
			Sort(highScores);
		}
	}
}

void WriteHighscoreToFile(Highscores& highScores)
{
	ofstream highscoreFile;
	highscoreFile.open("Highscores.txt");

	for (int i = 0; i < highScores.amount; i++)
	{
		highscoreFile << std::to_string(highScores.score[i]) << "\n";
	}
	highscoreFile.close();
}