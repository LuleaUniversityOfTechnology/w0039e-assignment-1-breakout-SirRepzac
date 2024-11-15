#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "game.h"


void SpawnBall()
{
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - (DISPLAY_HEIGHT - 60) }, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * ballSpeed;
}


//Occurs every frame
void StepFrame(float timeSinceLastStep, Paddle& paddle, GameState& gameState, int& currentScore, int highScores[])
{
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);

	DrawBricks(brickIds);
	DrawBalls(ballIds);
	CheckAndActOnBallBounce(ballIds, paddle);
	DestroyBricksTouchedByBall(ballIds, brickIds, currentScore);
	CheckAndActIfGameLoss(ballIds, gameState, currentScore, highScores);
	
}

//Ends game
void CheckAndActIfGameLoss(std::vector<int> ballIds, GameState gameState, int& currentScore, int highScores[])
{
	//If ball reaches bottom of the screen
	for (int i = 0; i < size(ballIds); i++)
	{
		if (Play::GetGameObject(ballIds[i]).pos.y < 0)
		{
			LoseScenario(ballIds, gameState, currentScore, highScores);
		}
	}
}

//Destroys brick if it is touched by a ball
void DestroyBricksTouchedByBall(std::vector<int> ballIds, std::vector<int> brickIds, int& currentScore)
{
	for (int ball = 0; ball < size(ballIds); ball++)
	{
		for (int brick = 0; brick < size(brickIds); brick++)
		{
			if (Play::IsColliding(Play::GetGameObject(ballIds[ball]), Play::GetGameObject(brickIds[brick])))
			{
				Play::DestroyGameObject(brickIds[brick]);
				Play::GetGameObject(ballIds[ball]).velocity.y *= -1;
				currentScore++;
			}
		}
	}
}

//Checks if a ball needs to bounce and then performs if
void CheckAndActOnBallBounce(std::vector<int> ballIds, Paddle paddle)
{
	//Bounces ball on the paddle
	for (int i = 0; i < size(ballIds); i++)
	{
		if (IsColliding(paddle, GetGameObject(ballIds[i])))
		{
			Play::GetGameObject(ballIds[i]).velocity.y *= -1;
		}
	}

	//Bounces ball if it hits screen edge
	for (int i = 0; i < size(ballIds); i++)
	{
		if (Play::GetGameObject(ballIds[i]).pos.x < 0 || Play::GetGameObject(ballIds[i]).pos.x > DISPLAY_WIDTH - Play::GetGameObject(ballIds[i]).radius * 2)
		{
			Play::GetGameObject(ballIds[i]).velocity.x *= -1;
		}
		if (Play::GetGameObject(ballIds[i]).pos.y > DISPLAY_HEIGHT - Play::GetGameObject(ballIds[i]).radius * 2)
		{
			Play::GetGameObject(ballIds[i]).velocity.y *= -1;
		}
	}
}

//Draws bricks
void DrawBricks(std::vector<int> brickIds)
{
	for (int i = 0; i < size(brickIds); i++)
	{
		Play::UpdateGameObject(Play::GetGameObject(brickIds[i]));
		Play::DrawObject(Play::GetGameObject(brickIds[i]));
	}
}

//Draws balls
void DrawBalls(std::vector<int> ballIds)
{
	for (int i = 0; i < size(ballIds); i++)
	{
		Play::UpdateGameObject(Play::GetGameObject(ballIds[i]));
		Play::DrawObject(Play::GetGameObject(ballIds[i]));
	}
}

//When the player loses
void LoseScenario(vector<int> ballIds, GameState& gameState, int& currentScore, int highScores[])
{
	for (int i = 0; i < size(ballIds); i++)
	{
		Play::DestroyGameObject(ballIds[i]);
	}
	
	AddCurrentScoreToHighScore(currentScore, highScores);
	ResetCurrentScore();
	gameState.Lost = true;
}

//When the player restarts
void Restart(GameState& gameState, Paddle& paddle, int& currentScore)
{
	const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	for (int i = 0; i < size(brickIds); i++)
	{
		Play::DestroyGameObject(brickIds[i]);
	}
	gameState.Lost = false;
	SpawnPaddle(paddle);
	SetupScene();
	SpawnBall();
	currentScore = 0;
}

//Setup bricks
void SetupScene()
{
	int xChange = 18;		//How far away each brick is from eachother in the x axis (includes the length of the next brick)
	int yChange = 12;		//How far away each brick is from eachother in the y axis (includes the length of the next brick)
	int distFromEdge = 10;	//How far from the edge the outer bricks should be at minimum
	int extraPixels = ((DISPLAY_WIDTH - distFromEdge * 2) / xChange) % xChange;			//extraPixels is meant to be the amount of pixels that could not fit an entire brick
	for (int x = distFromEdge + extraPixels / 2; x < DISPLAY_WIDTH - distFromEdge; x += xChange)
	{
		for (int y = DISPLAY_HEIGHT - 20; y > DISPLAY_HEIGHT / 1.5; y -= yChange)
		{
			Play::CreateGameObject(ObjectType::TYPE_BRICK, { x, y }, 6, "brick");
		}
	}
}