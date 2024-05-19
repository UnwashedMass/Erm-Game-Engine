#pragma once
#include "allo.h"
#include "free list allo.h"
#include "linearAllo.h"
template<typename T, typename Alloc>
class STLAdaptor
{
public:

	typedef T value_type;

	template<typename U>
	struct rebind
	{
		typedef STLAdaptor<U, Alloc> other;
	};

	STLAdaptor(Alloc& allocator)
		:
		m_allocator(allocator)
	{

	}

	template<typename U>
	STLAdaptor(const STLAdaptor<U, Alloc>& other) noexcept
		:
		m_allocator(other.m_allocator)
	{}

	[[nodiscard]] constexpr T* allocate(std::size_t n)
	{
		return reinterpret_cast<T*>
			(m_allocator.Allocate(n * sizeof(T), alignof(T)));
	}

	constexpr void deallocate(T* p, [[maybe_unused]] std::size_t n)
	{
		m_allocator.Free(p);
	}

	std::size_t MaxAllocationSize() const
	{
		return m_allocator.GetSize();
	}

	bool operator==(const STLAdaptor<T, Alloc>& rhs) const noexcept
	{
		
		return m_allocator.GetStart() == rhs.m_allocator.GetStart();
		
	}
	bool operator!=(const STLAdaptor<T, Alloc>& rhs) const noexcept
	{
		return !(*this == rhs);
	}

	Alloc& m_allocator;
};