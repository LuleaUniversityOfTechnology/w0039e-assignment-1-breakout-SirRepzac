#include "Paddle.h"

void DrawPaddle(const Paddle paddle) {

	//bottom left
	Play::Point2D bottomLeft = Play::Point2D(paddle.pos.x - 30, paddle.pos.y - 5);

	// top right
	Play::Point2D topRight = Play::Point2D(paddle.pos.x + 30, paddle.pos.y + 5);

	Play::DrawRect(bottomLeft, topRight, Play::cWhite, true);
}

