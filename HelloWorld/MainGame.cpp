#include "game.h"
#include <fstream>


Paddle globalPaddle;
GameState globalGameState;
Highscores globalHighScores;
int globalCurrentScore;



// The entry point for a PlayBuffer program
void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{


	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	globalCurrentScore = 0;
	LoadHighScores(globalHighScores);
	SetupScene();
	SpawnBall();
	SpawnPaddle(globalPaddle);
}

void HandleLoss() //I dont declare this in a header because i dont want to edit "Play.h"
{
	if (globalGameState.Lost)
	{
		Play::DrawDebugText({ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, "YOU LOSE", Play::cWhite);
		Play::DrawDebugText({ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 - 17 }, "PRESS SPACEBAR TO RETRY", Play::cWhite);
		if (Play::KeyDown(Play::KeyboardButton(VK_SPACE)))
		{
			Restart(globalGameState, globalPaddle, globalCurrentScore);
		}
	}
	if (Play::KeyDown(Play::KeyboardButton(VK_OEM_PLUS)))	//cheat button (on swedish keyboard is the + key))
	{
		globalCurrentScore++;
	}
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate(float elapsedTime)
{

	Play::ClearDrawingBuffer(Play::cBlack);
	StepFrame(elapsedTime, globalPaddle, globalGameState, globalCurrentScore, globalHighScores);
	UpdatePaddle(globalPaddle);
	DrawCurrentScore(globalCurrentScore);
	DrawHighScores(globalHighScores);
	HandleLoss();
	Play::PresentDrawingBuffer();
	return Play::KeyDown(Play::KeyboardButton::KEY_ESCAPE);

	
}



// Gets called once when the player quits the game 
int MainGameExit(void)
{
	WriteHighscoreToFile(globalHighScores);
	delete[] globalHighScores.score;
	Play::DestroyManager();
	return PLAY_OK;
}


