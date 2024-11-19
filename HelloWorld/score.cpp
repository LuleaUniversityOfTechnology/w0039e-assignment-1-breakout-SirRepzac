#include "Play.h"
#include "score.h"
#include "game.h"
#include <fstream>
using namespace std;


void DrawHighScores(const Highscores highScores, Paddle& paddle)
{
	if (paddle.pos.x > DISPLAY_WIDTH - (90 + paddle.length))		//hides the highscores if they seem like they would be in the way
		return;

	int displayCap = (highScores.amount > 5) ? 5 : (int)highScores.amount;	//caps the amount of highscores displayed at 5
	for (int i = 0; i < displayCap; i++)
	{
		std::string scoreString = std::to_string(highScores.score[i]);
		const char* toDraw = scoreString.c_str();
		Play::DrawDebugText({ DISPLAY_WIDTH - 40, displayCap * 15 + 15}, "HighScores", Play::cWhite);
		Play::DrawDebugText({ DISPLAY_WIDTH - 40, displayCap * 15 - i * 15 }, toDraw, Play::cWhite);
	}
}

void DrawCurrentScore(const int currentScore)
{
	std::string scoreString = std::to_string(currentScore);
	const char* toDraw = scoreString.c_str();

	Play::DrawDebugText({ 10, 10 }, toDraw, Play::cWhite);
}

void AddCurrentScoreToHighScore(int& currentScore, Highscores& highScores)
{
	highScores.add(currentScore);			
	RemoveZeroScores(highScores);
}

void RemoveZeroScores(Highscores& highScores)
{
	Sort(highScores);

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