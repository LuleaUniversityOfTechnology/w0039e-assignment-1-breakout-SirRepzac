#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"

void SpawnBall() {
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, {DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - (DISPLAY_HEIGHT - 60)}, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * ballSpeed;
}

void StepFrame(float timeSinceLastStep) {
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	for (int i = 0; i < size(ballIds); i++) {
		if (Play::GetGameObject(ballIds[i]).pos.x < 0 or Play::GetGameObject(ballIds[i]).pos.x > DISPLAY_WIDTH - Play::GetGameObject(ballIds[i]).radius * 2) {
			Play::GetGameObject(ballIds[i]).velocity.x = -Play::GetGameObject(ballIds[i]).velocity.x;
		}
		if (Play::GetGameObject(ballIds[i]).pos.y < 0 or Play::GetGameObject(ballIds[i]).pos.y > DISPLAY_HEIGHT - Play::GetGameObject(ballIds[i]).radius * 2) {
			Play::GetGameObject(ballIds[i]).velocity.y = -Play::GetGameObject(ballIds[i]).velocity.y;
		}
		Play::UpdateGameObject(Play::GetGameObject(ballIds[i]));
		Play::DrawObject(Play::GetGameObject(ballIds[i]));

		
	}
	for (int i = 0; i < size(brickIds); i++) {
		Play::UpdateGameObject(Play::GetGameObject(brickIds[i]));
		Play::DrawObject(Play::GetGameObject(brickIds[i]));
	}
}

void SetupScene() {
	for (int x = 10; x < DISPLAY_WIDTH - 10; x = x + 20) {
		for (int y = DISPLAY_HEIGHT - 20; y > DISPLAY_HEIGHT / 1.75; y = y - 15) {
			Play::CreateGameObject(ObjectType::TYPE_BRICK, { x, y }, 6, "brick");
		}
	}
}