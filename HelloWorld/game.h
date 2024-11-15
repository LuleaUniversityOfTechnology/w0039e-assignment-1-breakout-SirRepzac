#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "constants.h"
#include "Play.h"
#include "Paddle.h"
#include "score.h"

struct GameState {
	bool Lost = false;
};

void SpawnBall();

void StepFrame(float timeSinceLastStep, Paddle& paddle, GameState& gameState);

void CheckAndActIfGameLoss(std::vector<int> ballIds, GameState gameState);

void DestroyBricksTouchedByBall(std::vector<int> ballIds, std::vector<int> brickIds);

void CheckAndActOnBallBounce(std::vector<int> ballIds, Paddle paddle);

void DrawBricks(vector<int> brickIds);

void DrawBalls(vector<int> ballIds);

void SetupScene();

void LoseScenario(std::vector<int> ballIds, GameState& gameState);

void Restart(GameState& gameState, Paddle& paddle);



