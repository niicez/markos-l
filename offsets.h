#pragma once

#include <cstddef>

using namespace std;

namespace Game {
	constexpr uintptr_t ModuleBaseAddress = 0x400000;

	namespace LocalPlayer {
		constexpr ptrdiff_t Entity = 0x561D4;
		constexpr uintptr_t ViewMatrix = 0x0057DFD0;
	}

	namespace Entities {
		constexpr int Next = 0x4;

		constexpr ptrdiff_t Entity = 0x191FCC;
		constexpr ptrdiff_t Health = 0xEC;
		constexpr ptrdiff_t Name = 0x205;

		constexpr ptrdiff_t HeadPosition = 0x4;
		constexpr ptrdiff_t FootPosition = 0x28;
	}
}
