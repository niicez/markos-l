#include <iostream>
#include <glfw3.h>

#include "memory.h"
#include "overlay.h"

using namespace std;

int main()
{
	LPCWSTR targetProcessName = L"ac_client.exe";

	Memory memory;
	memory.GetDebugPrivileges();

	int processId = memory.GetProcessId(targetProcessName);
	cout << "[+] process id: " << processId << endl;

	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	cout << "[+] process handle: " << processHandle << endl;

	/* My overlay */
	Overlay overlay(processHandle, memory);
	overlay.Run();

	return 0;
}
