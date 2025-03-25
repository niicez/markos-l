#pragma once

#include <cstddef>

using namespace std;

namespace Game {
	constexpr uintptr_t ModuleBaseAddress = 0x400000;

	namespace LocalPlayer {
		constexpr ptrdiff_t Entity = 0x561D4;
	}

	namespace Entity {
		constexpr ptrdiff_t Next = 0x4;
		constexpr ptrdiff_t Health = 0xEC;
		constexpr ptrdiff_t PositionX = 0x4;
		constexpr ptrdiff_t PositionZ = 0x8;
		constexpr ptrdiff_t PositionY = 0xC;
	}
}
