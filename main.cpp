#include <iostream>

#include "memory.h"
#include "offsets.h"

using namespace std;

int main()
{
	SetConsoleTitle(L"Markos - Assault Cube");

	LPCWSTR TARGET_PROCESS_NAME = L"ac_client.exe";

	Memory Memory;
	Memory.GetDebugPrivileges();

	int processId = Memory.GetProcessId(TARGET_PROCESS_NAME);

	cout << "[*] process id: " << processId << endl;

	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

	cout << "[+] process handle: " << processHandle << endl;

	int baseAddress = Game::ModuleBaseAddress;

	cout << "[+] base address: 0x" << hex << baseAddress << endl;

	// Health Player

	int localPlayerPtr = Memory.GetPointerAddress(processHandle, baseAddress + Game::LocalPlayer::Entity, new int[2] {0x0, 0x0}, 2);

	cout << "[!] local player address: 0x" << hex << localPlayerPtr << endl;

	float healthPtr = Memory.ReadInt(processHandle, localPlayerPtr + Game::Entities::Health);

	cout << "[!] health value: " << healthPtr << endl;

	// Get Entities
	for (int i = 0; i < 11; i++) {
		// Read Entity
		int entityPtr = Memory.GetPointerAddress(processHandle, baseAddress + Game::Entities::Entity, new int[2] {i * Game::Entities::Next, 0x0}, 2);
		if (entityPtr == -1) continue;

		// Read Name
		char* name = Memory.ReadText(processHandle, entityPtr + Game::Entities::Name);
		if (name == "-1") continue;

		// Read Health
		float health = Memory.ReadInt(processHandle, entityPtr + Game::Entities::Health);
		if (health <= 0) continue;

		// Read Coordinates
		float x = Memory.ReadFloat(processHandle, entityPtr + Game::Entities::PositionX);
		float y = Memory.ReadFloat(processHandle, entityPtr + Game::Entities::PositionY);
		float z = Memory.ReadFloat(processHandle, entityPtr + Game::Entities::PositionZ);

		cout << "----------------------------------------" << endl;
		cout << "[" << i << "] entity address: 0x" << hex << entityPtr << endl;
		cout << "[!] name: " << name << endl;
		cout << "[!] health: " << health << endl;
		cout << "[!] x: " << x << " y: " << y << " z: " << z << endl;
	}

	return 0;
}
