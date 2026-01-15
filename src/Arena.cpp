#include "Arena.hpp"

ArenaAllocator::~ArenaAllocator()
{
	// No destructors are called for the stored objects. Thus, memory
	// leaks are possible (e.g. when storing std::vector objects or
	// other non-trivially destructible objects in the allocator).
	// Although this could be changed, it would come with additional
	// runtime overhead and therefore is not implemented.
	delete[] m_buffer;
}

ArenaAllocator &ArenaAllocator::operator=(ArenaAllocator &&other) noexcept
{
	std::swap(m_size, other.m_size);
	std::swap(m_buffer, other.m_buffer);
	std::swap(m_offset, other.m_offset);
	return *this;
}

ArenaAllocator::ArenaAllocator(ArenaAllocator &&other) noexcept :
	m_size{std::exchange(other.m_size, 0)}, m_buffer{std::exchange(other.m_buffer, nullptr)},
	m_offset{std::exchange(other.m_offset, nullptr)}
{
}

ArenaAllocator::ArenaAllocator(const size_t max_num_bytes) :
	m_size{max_num_bytes}, m_buffer{new std::byte[max_num_bytes]}, m_offset{m_buffer}
{
}
