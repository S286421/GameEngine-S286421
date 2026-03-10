#include "StackArenaAllocator.h"

StackArenaAllocator::StackArenaAllocator(std::size_t capacity) : buffer(new std::byte[capacity]), capacity(capacity), offset(0) {}

/// <summary>
/// Sets the offset variable to 0 (resetting the offset)
/// </summary>
void StackArenaAllocator::reset() noexcept
{
	offset = 0;
}

/// <summary>
/// Allocates data to memory addresses; uses bytes and alignment to calculate offset of data
/// </summary>
/// <param name="bytes"></param>
/// <param name="alignment"></param>
/// <returns></returns>
void* StackArenaAllocator::do_allocate(std::size_t bytes, std::size_t alignment)
{
	std::size_t current = reinterpret_cast<std::size_t>(buffer + offset);
	std::size_t aligned = (current + alignment - 1) & ~(alignment - 1);
	std::size_t newOffset = aligned - reinterpret_cast<std::size_t>(buffer) + bytes;

	if (newOffset > capacity) throw std::bad_alloc{};

	void* ptr = buffer + (aligned - reinterpret_cast<std::size_t>(buffer));
	offset = newOffset;

	return ptr;
}

void StackArenaAllocator::do_deallocate(void* ptr, size_t bytes, size_t align)
{
}

/// <summary>
/// Checks if the current memory_resource is the same as the given memory_resource (that)
/// </summary>
/// <param name="that"></param>
/// <returns></returns>
bool StackArenaAllocator::do_is_equal(const memory_resource& that) const noexcept
{
	return this == &that;
}