
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"

void SpawnBall() {
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, {DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - (DISPLAY_HEIGHT - 60)}, 4, "ball");
}

void StepFrame(float timeSinceLastStep) {
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	for (int i = 0; i < size(ballIds); i++) {
		Play::DrawObject(Play::GetGameObject(ballIds[i]));
		
	}
}