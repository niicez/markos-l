#include <iostream>
#include "memory.hpp"

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

	int baseAddress = Memory.GetModuleBase(processHandle, TARGET_PROCESS_NAME);

	cout << "[+] base address: 0x" << hex << baseAddress << endl;

	int localPlayerPtr = Memory.GetPointerAddress(processHandle, baseAddress + 0x0018b0b8, new int[2]{0x0, 0x404}, 2);

	cout << "[!] local player ptr: " << hex << localPlayerPtr << endl;

	float healthPtr = Memory.ReadInt(processHandle, localPlayerPtr + 0x4);

	cout << "[!] health ptr: " << healthPtr << endl;

	(void)getchar();

	return 0;
}
