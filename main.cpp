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

	cout << "[+] process id: " << processId << endl;

	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

	cout << "[+] process handle: " << processHandle << endl;

	int baseAddress = Game::ModuleBaseAddress;

	cout << "[+] base address: 0x" << hex << baseAddress << endl;

	int localPlayerPtr = Memory.GetPointerAddress(processHandle, baseAddress + Game::LocalPlayer::Entity, new int[2] {0x0, 0x0}, 2);

	cout << "[!] local player ptr: 0x" << hex << localPlayerPtr << endl;

	float healthPtr = Memory.ReadInt(processHandle, localPlayerPtr + Game::Entity::Health);

	cout << "[!] health ptr: " << healthPtr << endl;

	(void)getchar();

	return 0;
}
