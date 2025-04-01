#include <iostream>

#include "entities.h"
#include "vector3.h"
#include "types.h"
#include "memory.h"
#include "offsets.h"
#include "rendering.h"

ListEntity Entities::getEntities(HANDLE processHandle, Memory& memory) {

	ViewMatrix viewMatrix = memory.Read<ViewMatrix>(processHandle, Game::LocalPlayer::ViewMatrix);
	ListEntity listEntity = {};

	for (int i = 0; i < 3; i++) {

		int entity = memory.GetPointerAddress(processHandle, Game::ModuleBaseAddress + Game::Entities::Entity, new int[2] {i* Game::Entities::Next, 0x0}, 2);
		if (entity == -1) continue;

		char* name = memory.ReadText(processHandle, entity + Game::Entities::Name);
		if (name == "-1") continue;

		float health = memory.ReadInt(processHandle, entity + Game::Entities::Health);
		if (health <= 0) continue;

		Vector3 enemyPosition = memory.Read<Vector3>(processHandle, entity + Game::Entities::PositionX);

		/*cout << "----------------------------------------" << endl;
		cout << "[*] entity address: 0x" << hex << entity << endl;
		cout << "[!] name: " << name << endl;
		cout << "[!] health: " << health << endl;
		cout << "[!] x: " << enemyPosition.x << " y: " << enemyPosition.y << " z: " << enemyPosition.z << endl;*/

		Vector2 screenPosition = Rendering::WorldToScreen(enemyPosition, viewMatrix);
		if (screenPosition.x == -2.0f) continue;

		/*cout << "[!] screen x: " << screenPosition.x << " screen y: " << screenPosition.y << endl;*/

		listEntity.push_back(screenPosition);
	}

	return listEntity;
}
