#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "game.h"

Paddle globalPaddle;

void SpawnBall() {
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, {DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - (DISPLAY_HEIGHT - 60)}, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * ballSpeed;
}

void SpawnPaddle() {
	globalPaddle.pos = Play::Point2D(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - (DISPLAY_HEIGHT - 20));
}

//Occurs every frame
void StepFrame(float timeSinceLastStep) {
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);

	for (int i = 0; i < size(brickIds); i++) {
		Play::UpdateGameObject(Play::GetGameObject(brickIds[i]));
		Play::DrawObject(Play::GetGameObject(brickIds[i]));
	}

	//Checks collision between the paddle and the balls
	for (int i = 0; i < size(ballIds); i++) {
		if (IsColliding(globalPaddle, GetGameObject(ballIds[i]))) {
			Play::GetGameObject(ballIds[i]).velocity.y *= -1;
		}
	}

	//Changes the balls direction if it hits something
	for (int i = 0; i < size(ballIds); i++) {
		if (Play::GetGameObject(ballIds[i]).pos.x < 0 or Play::GetGameObject(ballIds[i]).pos.x > DISPLAY_WIDTH - Play::GetGameObject(ballIds[i]).radius * 2) {
			Play::GetGameObject(ballIds[i]).velocity.x *= -1;
		}
		if (Play::GetGameObject(ballIds[i]).pos.y < 0 or Play::GetGameObject(ballIds[i]).pos.y > DISPLAY_HEIGHT - Play::GetGameObject(ballIds[i]).radius * 2) {
			Play::GetGameObject(ballIds[i]).velocity.y *= -1;
		}
		Play::UpdateGameObject(Play::GetGameObject(ballIds[i]));
		Play::DrawObject(Play::GetGameObject(ballIds[i]));

	}

	//Destroys brick if it is touched by a ball
	for (int ball = 0; ball < size(ballIds); ball++) {
		for (int brick = 0; brick < size(brickIds); brick++) {
			if (Play::IsColliding(Play::GetGameObject(ballIds[ball]), Play::GetGameObject(brickIds[brick]))) {
				Play::DestroyGameObject(brickIds[brick]);
				Play::GetGameObject(ballIds[ball]).velocity.y *= -1;
			}
		}
	}

	
	UpdatePaddle();
	DrawPaddle(globalPaddle);

}

//Checks if the paddle is colliding with an object
bool IsColliding(const Paddle paddle, GameObject& obj) {

	Play::Point2D paddleBottomRight = Play::Point2D(paddle.pos.x + 30, paddle.pos.y - 5);
	Play::Point2D paddleTopLeft = Play::Point2D(paddle.pos.x - 30, paddle.pos.y + 5);

	const float dx = obj.pos.x - Max(paddleTopLeft.x, Min(obj.pos.x, paddleBottomRight.x));
	const float dy = obj.pos.y - Max(paddleTopLeft.y, Min(obj.pos.y, paddleBottomRight.y));
	return (dx * dx + dy * dy) < (obj.radius * obj.radius);
}

//Outputs the greater of two values
int Max(int value1, int value2) {
	return (value1 > value2) ? value1 : value2;
}

//Outputs the lesser of two values
int Min(int value1, int value2) {
	return (value1 < value2) ? value1 : value2;
}

void UpdatePaddle() {
	if (Play::KeyDown(Play::KeyboardButton(VK_LEFT))) {
		globalPaddle.pos.x -= 5;
	}
	if (Play::KeyDown(Play::KeyboardButton(VK_RIGHT))) {
		globalPaddle.pos.x += 5;
	}
}

//Setup bricks
void SetupScene() {
	int xChange = 18;		//How far away each brick is from eachother in the x axis (includes the length of the next brick)
	int yChange = 12;		//How far away each brick is from eachother in the y axis (includes the length of the next brick)
	int distFromEdge = 10;	//How far from the edge the outer bricks should be at minimum
	float extraPixels = ((DISPLAY_WIDTH - distFromEdge*2) / xChange) % xChange;			//extraPixels is meant to be the amount of pixels that could not fit an entire brick
	for (float x = distFromEdge + extraPixels / 2; x < DISPLAY_WIDTH - distFromEdge; x += xChange) {		
		for (int y = DISPLAY_HEIGHT - 20; y > DISPLAY_HEIGHT / 1.5; y -= yChange) {
			Play::CreateGameObject(ObjectType::TYPE_BRICK, { x, y }, 6, "brick");
		}
	}
}