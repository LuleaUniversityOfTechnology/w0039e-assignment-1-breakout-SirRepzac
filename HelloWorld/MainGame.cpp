#include "Paddle.h"
#include "game.h"
#include <fstream>


Paddle globalPaddle;
GameState globalGameState;
Highscores globalHighscores;
int globalCurrentScore;


// The entry point for a PlayBuffer program
void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{


	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	globalCurrentScore = 0;
	LoadHighScores(globalHighscores);
	SetupScene();
	SpawnBall();
	SpawnPaddle(globalPaddle);
	LoadHighScores(globalHighscores);
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate(float elapsedTime)
{

	Play::ClearDrawingBuffer(Play::cBlack);
	StepFrame(elapsedTime, globalPaddle, globalGameState, globalCurrentScore, globalHighscores);
	UpdatePaddle(globalPaddle);
	DrawCurrentScore(globalCurrentScore);
	DrawHighScores(globalHighscores);
	if (globalGameState.Lost)
	{
		Play::DrawDebugText({ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, "YOU LOSE", Play::cWhite);
		if (Play::KeyDown(Play::KeyboardButton(VK_SPACE)))
		{
			Restart(globalGameState, globalPaddle, globalCurrentScore);
		}
	}
	Play::PresentDrawingBuffer();
	return Play::KeyDown(Play::KeyboardButton::KEY_ESCAPE);


}

// Gets called once when the player quits the game 
int MainGameExit(void)
{
	WriteHighscoreToFile(globalHighscores);
	delete[] globalHighscores.scores;
	Play::DestroyManager();
	return PLAY_OK;
}


