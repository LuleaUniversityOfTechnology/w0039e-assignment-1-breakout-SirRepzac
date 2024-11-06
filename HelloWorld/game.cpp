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
}

void SetupScene() {
	for (int x = 2; x < DISPLAY_WIDTH - 8; x = x + 8) {
		for (int y = 2; y < 23; y = y + 4) {
			Play::CreateGameObject(ObjectType::TYPE_BRICK, { x, y }, 6, "brick");
		}
	}
}