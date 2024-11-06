#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "constants.h"
#include "Play.h"
#include "Paddle.h"

void SpawnBall();

void StepFrame(float timeSinceLastStep);

void SetupScene();

void UpdatePaddle();

bool IsColliding(Paddle paddle, Play::GameObject obj);

int Max(int value1, int value2);

int Min(int value1, int value2);