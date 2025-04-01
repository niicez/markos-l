#pragma once

#include <vector>

#include "types.h"
#include "memory.h"

class Entities
{
public:
	static ListEntity getEntities(HANDLE processHandle, Memory& memory);
};
