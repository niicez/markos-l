#pragma once

#include <glfw3.h>

#include "types.h"
#include "memory.h"

class Overlay
{
public:
	Overlay(HANDLE processHandle, Memory memory);
	~Overlay();
	int Run();
private:
	HANDLE processHandle;
	Memory memory;
	GLFWwindow* window;

	int Initialize();
	void Render();
};

