#include <iostream>
#include <array>
#include <glfw3.h>

#include "memory.h"
#include "offsets.h"
#include "vector3.h"
#include "types.h"
#include "rendering.h"

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

	int localPlayerPtr = Memory.GetPointerAddress(processHandle, baseAddress + Game::LocalPlayer::Entity, new int[2] {0x0, 0x0}, 2);

	cout << "[!] local player address: 0x" << hex << localPlayerPtr << endl;

	float healthPtr = Memory.ReadInt(processHandle, localPlayerPtr + Game::Entities::Health);

	cout << "[!] health value: " << healthPtr << endl;

	/*
	TODO: get number of enemy
	*/

	/* Temp: Overlay */
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Config */
	glfwWindowHint(GLFW_FLOATING, true);
	//glfwWindowHint(GLFW_RESIZABLE, false);
	//glfwWindowHint(GLFW_MAXIMIZED, true);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);
	glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, true);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the ESP box
		glColor3f(1.0f, 0.0f, 0.0f);

		// Read Player View Matrix
		ViewMatrix viewMatrix = Memory.Read<ViewMatrix>(processHandle, Game::LocalPlayer::ViewMatrix);

		// Get Entities
		for (int i = 0; i < 3; i++) {
			// Read Entity
			int entity = Memory.GetPointerAddress(processHandle, baseAddress + Game::Entities::Entity, new int[2] {i* Game::Entities::Next, 0x0}, 2);
			if (entity == -1) continue;

			// Read Name
			char* name = Memory.ReadText(processHandle, entity + Game::Entities::Name);
			if (name == "-1") continue;

			// Read Health
			float health = Memory.ReadInt(processHandle, entity + Game::Entities::Health);
			if (health <= 0) continue;

			// Read Coordinates
			Vector3 enemyPosition = Memory.Read<Vector3>(processHandle, entity + Game::Entities::PositionX);

			cout << "----------------------------------------" << endl;
			cout << "[*] entity address: 0x" << hex << entity << endl;
			cout << "[!] name: " << name << endl;
			cout << "[!] health: " << health << endl;
			cout << "[!] x: " << enemyPosition.x << " y: " << enemyPosition.y << " z: " << enemyPosition.z << endl;

			// Show Screen Position
			Vector2 screenPosition = Rendering::WorldToScreen(enemyPosition, viewMatrix);
			if (screenPosition.x == -2.0f) continue;

			cout << "[+] Screen-x: " << screenPosition.x << " Screen-y: " << screenPosition.y << endl;

			glBegin(GL_LINES);

			glVertex2f(0.0f, -1.0f);
			glVertex2f(screenPosition.x, screenPosition.y);
			glEnd();
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
