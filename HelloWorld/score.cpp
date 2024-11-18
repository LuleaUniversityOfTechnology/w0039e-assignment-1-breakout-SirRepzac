#include "Play.h"
#include "score.h"
#include "game.h"
#include <fstream>
using namespace std;


void DrawHighScores(const Highscores highScores)
{

	//int nrOfHighScores = GetNumberOfHighScores(highScores);
	//int nrOfHighscoresLowerOrEqualToFive;
	//if (nrOfHighScores > 5)
	//{
	//	 nrOfHighscoresLowerOrEqualToFive = 5;
	//}
	//else
	//{
	//	nrOfHighscoresLowerOrEqualToFive = nrOfHighScores;
	//}

	for (int i = 0; i < 5; i++)
	{
		if (highScores.scores[i] != 0)
		{
			std::string scoreString = std::to_string(highScores.scores[i]);
			const char* toDraw = scoreString.c_str();

			Play::DrawDebugText({ DISPLAY_WIDTH - 30, 10 + (highScores.amount < 5 ? highScores.amount : 5) * 15 - i * 15 }, toDraw, Play::cWhite);
		}
	}
}

//int GetNumberOfHighScores(const Highscores highScores)
//{
//	int nrOfHighscores = 0;
//	int i = 0;
//	while (true)
//	{
//		if (highScores[i] == 0)
//		{
//			return nrOfHighscores;
//		}
//		i++;
//		nrOfHighscores++;
//	}
//}

void DrawCurrentScore(const int currentScore)
{
	std::string scoreString = std::to_string(currentScore);
	const char* toDraw = scoreString.c_str();

	Play::DrawDebugText({10, 10}, toDraw, Play::cWhite);
}

void AddCurrentScoreToHighScore(int& currentScore, Highscores& highScores)
{
	//int nrOfHS = GetNumberOfHighScores(highScores);
	for (int i = 0; i < highScores.amount; i++)
	{
		if (currentScore > highScores.scores[i])	//new score is bigger than any of the previous scores
		{
			for (int j = highScores.amount - 1; j > i; j--)			//moves all scores smaller than the new score down one step
			{
				highScores.scores[j] = highScores.scores[j - 1];
			}
			highScores.scores[i] = currentScore;
			return;
		}
	}

	//if (highScores.amount < 5)
	//{
	//	for (int i = 0; i < 5; i++)
	//	{
	//		if (currentScore > highScores[i])
	//		{
	//			for (int j = nrOfHS - 1; j > i; j--)
	//			{
	//				highScores[j] = highScores[j - 1];
	//			}
	//			highScores[i] = currentScore;
	//			return;
	//		}
	//	}
	//}
}

void LoadHighScores(Highscores& highScores)
{
	ifstream highscoreFile;
	highscoreFile.open("Highscores.txt");

	int nrOfHighscores = std::count(std::istreambuf_iterator<char>(highscoreFile),std::istreambuf_iterator<char>(), '\n');
	highScores.scores = new int[nrOfHighscores]();
	highScores.amount = nrOfHighscores;

	for (int i = 0; i < nrOfHighscores; i++)
	{
		char score[16];
		highscoreFile.getline(score, 16);
		sscanf_s(score, "%d", &highScores.scores[i]);
	}
}



void WriteHighscoreToFile(Highscores& highScores)
{
	
	//int nrOfHS = GetNumberOfHighScores(highScores);
	ofstream highscoreFile;
	highscoreFile.open("Highscores.txt");

	for (int i = 0; i < highScores.amount; i++)
	{
		highscoreFile << std::to_string(highScores.scores[i]) << "\n";
	}
	if (highScores.scores[highScores.amount] != 0)
	{
		highscoreFile << "0";
	}
	highscoreFile.close();

}