#pragma once

#include <array>
#include "Components.hpp"

uint32_t constexpr MAX_ENTITIES = 100;
class ECS
{
public:
	std::array<uint64_t, MAX_ENTITIES> entityIDs{ 0 };
	std::array<PositionECS, MAX_ENTITIES> positions;
	std::array<VelocityECS, MAX_ENTITIES> velocities;
	std::array<BitmapECS, MAX_ENTITIES> bitmaps;
};

