#include "game.h"


// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	SpawnBall();
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cBlack );
	Play::PresentDrawingBuffer();
	//return Play::KeyDown( KEY_ESCAPE );
	StepFrame(elapsedTime);
	return 1;
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

