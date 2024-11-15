#include "Paddle.h"
#include "game.h"


Paddle globalPaddle;
GameState globalGameState;
int globalHighScores[5];


// The entry point for a PlayBuffer program
void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	SetupScene();
	SpawnBall();
	SpawnPaddle(globalPaddle);
	LoadHighScores(globalHighScores);
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate(float elapsedTime)
{

	Play::ClearDrawingBuffer(Play::cBlack);
	StepFrame(elapsedTime, globalPaddle, globalGameState);
	UpdatePaddle(globalPaddle);
	DrawCurrentScore();
	DrawHighScores(globalHighScores);
	if (globalGameState.Lost)
	{
		Play::DrawDebugText({ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, "YOU LOSE", Play::cWhite);
		if (Play::KeyDown(Play::KeyboardButton(VK_SPACE)))
		{
			Restart(globalGameState, globalPaddle);
		}
	}
	Play::PresentDrawingBuffer();
	return Play::KeyDown(Play::KeyboardButton::KEY_ESCAPE);


}

// Gets called once when the player quits the game 
int MainGameExit(void)
{
	Play::DestroyManager();
	return PLAY_OK;
}


