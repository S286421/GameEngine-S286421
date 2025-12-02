#pragma once
#include <cstddef>
#include <cstdint>
#include <memory>
#include <new>
#include <type_traits>
#include <cassert>
#include <memory_resource>

class StackArenaAllocator : public std::pmr::memory_resource
{
private:
	std::byte* buffer;
	std::size_t capacity;
	std::size_t offset;
public:
	StackArenaAllocator(std::size_t capacity);
	~StackArenaAllocator() override { delete[] buffer; }
	void reset() noexcept;
protected:
	void* do_allocate(std::size_t bytes, std::size_t alignment) override;
	void do_deallocate(void* ptr, size_t bytes, size_t align) override;
	bool do_is_equal(const memory_resource& that) const noexcept override;
};

