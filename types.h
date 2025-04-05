#pragma once

#include <vector>
#include <array>

using namespace std;
using ViewMatrix = array<array<float, 4>, 4>;

struct Vector2 {
	float x, y;
};

struct Vector4 {
	float x, y, z, w;
};

struct EntityBox {
	float top;
	float bottom;
	float left;
	float right;
};

struct HealthBar {
	float height;
	float right;
	float left;
};

struct ListEntityValue {
	EntityBox entityBox;
	HealthBar healthBar;
	
	float health;
};

using ListEntity = vector<ListEntityValue>;