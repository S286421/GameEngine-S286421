#pragma once
#include <memory>
#include <SDL3/SDL_render.h>

uint64_t constexpr VelocityKey = 1 << 0;
uint64_t constexpr PositionKey = 1 << 1;
uint64_t constexpr BitmapKey = 1 << 2;

struct VelocityECS
{
	float dx, dy;
	float gravity = 1.0f;
};

struct PositionECS
{
	float X, Y;
	PositionECS operator+(const VelocityECS& other) const
	{
		return { X + other.dx , other.dy };
	}
	PositionECS& operator+=(const VelocityECS& other)
	{
		X += other.dx;
		Y += other.dy;
		return *this;
	}
};

struct BitmapECS
{
	std::shared_ptr<SDL_Texture> texture;
};