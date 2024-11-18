#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "constants.h"
#include "Play.h"

using namespace Play;

struct Paddle
{
	Play::Point2D pos; //bottom left corner
	int height;
	int length;
};

void DrawPaddle(const Paddle paddle);

void SpawnPaddle(Paddle& paddle);

void UpdatePaddle(Paddle& paddle);

bool IsColliding(Paddle paddle, int objId);

float Max(float value1, float value2);

float Min(float value1, float value2);