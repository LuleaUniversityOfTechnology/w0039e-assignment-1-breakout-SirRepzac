#pragma once
#include "Play.h"
#include "constants.h"


struct Paddle
{
	Play::Point2D pos;
};

void DrawPaddle(const Paddle paddle);

void SpawnPaddle();