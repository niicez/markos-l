#include <iostream>
#include <array>

#include "entities.h"
#include "vector3.h"
#include "types.h"
#include "memory.h"
#include "offsets.h"
#include "rendering.h"

static EntityBox getEntityBox(Vector2& head2D, Vector2& foot2D) {
	float height = foot2D.y - head2D.y;
	float width = height / 2.0f;

	float top = head2D.y;
	float bottom = foot2D.y;
	float left = head2D.x - (width / 3);
	float right = head2D.x + (width / 3);

	return {
		top,
		bottom,
		left,
		right,
	};
}

static HealthBar getEntityHealthBar(Vector2& head2D, Vector2& foot2D) {
	float height = foot2D.y - head2D.y;
	float width = height / 2.0f;

	float boxRight = head2D.x + (width / 3);

	float right = boxRight + (width / 10.0f);
	float left = boxRight + (width / 7.85f);

	return {
		height,
		right,
		left,
	};
}

ListEntity Entities::getEntities(HANDLE processHandle, Memory& memory) {

	ViewMatrix viewMatrix = memory.Read<ViewMatrix>(processHandle, Game::LocalPlayer::ViewMatrix);
	ListEntity listEntity = {};
	
	int entitySize = memory.ReadInt(processHandle, Game::ModuleBaseAddress + Game::Entities::EntitySize);
	if (entitySize == -1) {
		std::cout << "Entity size is -1" << std::endl;
		return listEntity;
	}

	for (int i = 0; i < entitySize; i++) {

		int offsets[2] = {i * Game::Entities::Next, 0x0};
		int entity = memory.GetPointerAddress(processHandle, Game::ModuleBaseAddress + Game::Entities::EntityList, offsets, 2);
		if (entity == -1) continue;
		
		/* NOTE: memory leak, fix later */
		/*char* name = memory.ReadText(processHandle, entity + Game::Entities::Name);
		if (name == "-1") continue;*/

		float health = memory.ReadInt(processHandle, entity + Game::Entities::Health);
		if (health <= 0) continue;

		Vector3 headPosition = memory.Read<Vector3>(processHandle, entity + Game::Entities::HeadPosition);
		Vector3 footPosition = memory.Read<Vector3>(processHandle, entity + Game::Entities::FootPosition);

		Vector2 head2D = Rendering::WorldToScreen(headPosition + Vector3({ 0.0f, 0.0f, 0.7f }), viewMatrix);
		Vector2 foot2D = Rendering::WorldToScreen(footPosition + Vector3({0.0f, 0.0f, -0.5f}), viewMatrix);

		if (foot2D.x == -2.0f || head2D.x == -2.0f) continue;

		EntityBox entityBox = getEntityBox(head2D, foot2D);
		HealthBar healthBar = getEntityHealthBar(head2D, foot2D);

		listEntity.push_back(ListEntityValue {
			entityBox,
			healthBar,
			health,
		});
	}

	return listEntity;
}
