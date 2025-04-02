#include <iostream>

#include "entities.h"
#include "vector3.h"
#include "types.h"
#include "memory.h"
#include "offsets.h"
#include "rendering.h"

ListEntity Entities::getEntities(HANDLE processHandle, Memory& memory) {

	int localplayer = memory.GetPointerAddress(processHandle, Game::ModuleBaseAddress + Game::LocalPlayer::Entity, new int[2] {0x0, 0x0}, 2);

	Vector3 playerPosition = memory.Read<Vector3>(processHandle, localplayer + Game::Entities::PositionX);
	ViewMatrix viewMatrix = memory.Read<ViewMatrix>(processHandle, Game::LocalPlayer::ViewMatrix);
	ListEntity listEntity = {};

	for (int i = 0; i < 3; i++) {

		int entity = memory.GetPointerAddress(processHandle, Game::ModuleBaseAddress + Game::Entities::Entity, new int[2] {i* Game::Entities::Next, 0x0}, 2);
		if (entity == -1) continue;

		char* name = memory.ReadText(processHandle, entity + Game::Entities::Name);
		if (name == "-1") continue;

		float health = memory.ReadInt(processHandle, entity + Game::Entities::Health);
		if (health <= 0) continue;

		Vector3 headPosition = memory.Read<Vector3>(processHandle, entity + Game::Entities::PositionX);
		Vector3 footPosition = memory.Read<Vector3>(processHandle, entity + 0x28);

		Vector2 topScreen = Rendering::WorldToScreen(headPosition + Vector3({ 0.0f, 0.0f, 0.7f }), viewMatrix);
		Vector2 bottomScreen = Rendering::WorldToScreen(footPosition + Vector3({0.0f, 0.0f, -0.5f}), viewMatrix);
		
		if (bottomScreen.x == -2.0f) continue;

		float height = bottomScreen.y - topScreen.y;
		float width = height / 2.0f;

		float left = topScreen.x - (width / 3);
		float top = topScreen.y;
		float right = topScreen.x + (width / 3);
		float bottom = bottomScreen.y;

		Test2 tester {
			left,
			top,
			right,
			bottom,
		};

		listEntity.push_back(Test {
			bottomScreen,
			tester,
		});
	}

	return listEntity;
}
