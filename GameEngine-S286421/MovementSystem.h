#pragma once

#include <memory>
#include <string>
#include "ECS.h"
#include "Components.hpp"

class MovementSystem
{
public:
	static PositionECS AddPositionComponentToEntity(uint32_t EntityID, ECS& const ecs, float InitialX, float InitialY);
	static VelocityECS AddVelocityComponentToEntity(uint32_t EntityID, ECS& const ecs, float InitialDx, float InitialDy, float Gravity = 1.0f);

	static void UpdatePositions(ECS& const ecs);
};

