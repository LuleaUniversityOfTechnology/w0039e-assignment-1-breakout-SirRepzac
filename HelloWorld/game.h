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

void SetupScene();

void LoseSenario(std::vector<int> ballIds, GameState& gameState);

void Restart(GameState& gameState, Paddle& paddle);



