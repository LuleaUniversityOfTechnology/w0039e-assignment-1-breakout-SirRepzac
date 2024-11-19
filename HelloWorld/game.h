#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "constants.h"
#include "Play.h"
#include "score.h"
#include "Paddle.h"


struct GameState {
	bool Lost = false;
};


void SpawnBall();

void StepFrame(float timeSinceLastStep, Paddle& paddle, GameState& gameState, int& currentScore, Highscores& highScores);

void ActOnGameLoss(std::vector<int> ballIds, GameState& gameState, int& currentScore, Highscores& highScores);

void DestroyBricksTouchedByBall(std::vector<int> ballIds, std::vector<int> brickIds, int& currentScore);

void ActOnBallBounce(std::vector<int> ballIds, Paddle paddle);

void CheckSpeed(int ballId);

void DrawBricks(std::vector<int> brickIds);

void DrawBalls(std::vector<int> ballIds);

void SetupScene();

void LoseScenario(std::vector<int> ballIds, GameState& gameState, int& currentScore, Highscores& highScores);

void Restart(GameState& gameState, Paddle& paddle, int& currentScore);





