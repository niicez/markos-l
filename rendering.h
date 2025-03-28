#pragma once

#include "types.h"
#include "vector3.h"

class Rendering
{
public:
	static Vector2 WorldToScreen(Vector3& worldPosition, ViewMatrix& viewMatrix);
};

