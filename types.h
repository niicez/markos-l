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

using ListEntity = vector<Vector2>;