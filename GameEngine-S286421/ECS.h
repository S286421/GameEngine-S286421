#pragma once

#include <array>
#include <vector>
#include "Components.hpp"

uint32_t constexpr MAX_ENTITIES = 100;
class ECS
{
public:
	ECS()
	{
		entityIDs.resize(MAX_ENTITIES);
		positions.resize(MAX_ENTITIES);
		velocities.resize(MAX_ENTITIES);
		bitmaps.resize(MAX_ENTITIES);
	}

	std::vector<uint64_t> entityIDs{ 0 };
	std::vector<PositionECS> positions;
	std::vector<VelocityECS> velocities;
	std::vector<BitmapECS> bitmaps;
};

