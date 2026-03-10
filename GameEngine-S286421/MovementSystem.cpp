#include "MovementSystem.h"

/// <summary>
/// Creates an Entity Component System (ECS) with the given InitialX and InitialY, and adds it to the entity specified with the EntityID; returns the PositionECS
/// </summary>
/// <param name="EntityID"></param>
/// <param name="ecs"></param>
/// <param name="InitialX"></param>
/// <param name="InitialY"></param>
/// <returns></returns>
PositionECS MovementSystem::AddPositionComponentToEntity(uint32_t EntityID, ECS& const ecs, float InitialX, float InitialY)
{
	PositionECS pos;
	pos.X = InitialX;
	pos.Y = InitialY;

	ecs.positions[EntityID] = pos;
	ecs.entityIDs[EntityID] |= PositionKey;

	return pos;
}

/// <summary>
/// Creates an Entity Component System (ECS) with the given InitialDx, InitialDy, and Gravity, and adds it to the entity specified with the EntityID; returns the VelocityECS
/// </summary>
/// <param name="EntityID"></param>
/// <param name="ecs"></param>
/// <param name="InitialDx"></param>
/// <param name="InitialDy"></param>
/// <param name="Gravity"></param>
/// <returns></returns>
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

/// <summary>
/// Updates PositionECS and VelocityECS of all entities
/// </summary>
/// <param name="ecs"></param>
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