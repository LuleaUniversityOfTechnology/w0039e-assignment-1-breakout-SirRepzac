#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Paddle.h"
#include "Play.h"



void DrawPaddle(const Paddle paddle)
{

	//bottom left
	Play::Point2D bottomLeft = Play::Point2D(paddle.pos.x, paddle.pos.y);

	// top right
	Play::Point2D topRight = Play::Point2D(paddle.pos.x + paddle.length, paddle.pos.y + paddle.height);

	Play::DrawRect(bottomLeft, topRight, Play::cWhite, true);
}

//Checks if the paddle is colliding with an object
bool IsColliding(const Paddle paddle, Play::GameObject& obj)
{

	Play::Point2D paddleBottomRight = Play::Point2D(paddle.pos.x + paddle.length, paddle.pos.y);
	Play::Point2D paddleTopLeft = Play::Point2D(paddle.pos.x, paddle.pos.y + paddle.height);

	const float dx = obj.pos.x - Max(paddleTopLeft.x, Min(obj.pos.x, paddleBottomRight.x));
	const float dy = obj.pos.y - Max(paddleTopLeft.y, Min(obj.pos.y, paddleBottomRight.y));
	return (dx * dx + dy * dy) < (obj.radius * obj.radius);

}

void UpdatePaddle(Paddle& paddle)
{
	if (Play::KeyDown(Play::KeyboardButton(VK_LEFT)) && paddle.pos.x > 0)
	{
		paddle.pos.x -= 5;
	}
	if (Play::KeyDown(Play::KeyboardButton(VK_RIGHT)) && paddle.pos.x < DISPLAY_WIDTH - paddle.length)
	{
		paddle.pos.x += 5;
	}
	DrawPaddle(paddle);
}

void SpawnPaddle(Paddle& paddle)
{
	paddle.pos = Play::Point2D(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - (DISPLAY_HEIGHT - 20));
	paddle.height = 10;
	paddle.length = 60;
}

//Outputs the greater of two values
float Max(float value1, float value2)
{
	return (value1 > value2) ? value1 : value2;
}

//Outputs the lesser of two values
float Min(float value1, float value2)
{
	return (value1 < value2) ? value1 : value2;
}

