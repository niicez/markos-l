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

struct Test2 {
	float x;
	float y;
	float w;
	float h;
};
 
struct Test {
	Vector2 screenPosition;
	Test2 tester;
};

using ListEntity = vector<Test>;