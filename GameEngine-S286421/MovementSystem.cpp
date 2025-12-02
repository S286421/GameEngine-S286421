#include "MovementSystem.h"

PositionECS MovementSystem::AddPositionComponentToEntity(uint32_t EntityID, ECS& const ecs, float InitialX, float InitialY)
{
	PositionECS pos;
	pos.X = InitialX;
	pos.Y = InitialY;

	ecs.positions[EntityID] = pos;
	ecs.entityIDs[EntityID] |= PositionKey;

	return pos;
}

VelocityECS MovementSystem::AddVelocityComponentToEntity(uint32_t EntityID, ECS& const ecs, float InitialDx, float InitialDy, float Gravity)
{
	VelocityECS vel;
	vel.dx = InitialDx;
	vel.dy = InitialDy;
	vel.gravity = Gravity;

	ecs.velocities[EntityID] = vel;
	ecs.entityIDs[EntityID] |= VelocityKey;

	return vel;
}

void MovementSystem::UpdatePositions(ECS& const ecs)
{
	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++)
	{
		if (ecs.entityIDs[entityID] & (PositionKey | VelocityKey))
		{
			ecs.velocities[entityID].dy += ecs.velocities[entityID].gravity;
			ecs.positions[entityID] += ecs.velocities[entityID];
		}
	}
}