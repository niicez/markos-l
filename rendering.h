#pragma once

#include <glfw3.h>
#include "types.h"
#include "vector3.h"

class Rendering
{
public:
	static Vector2 WorldToScreen(Vector3 worldPosition, ViewMatrix& viewMatrix);
	static void DrawBox(float x, float y, float w, float h);
};

