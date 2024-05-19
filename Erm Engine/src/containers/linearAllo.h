#include "allo.h"

class LinearAllocator : public Allocator
{
public:
	LinearAllocator(const std::size_t sizeBytes,
		void* const start) noexcept;

	LinearAllocator(const LinearAllocator&) = delete;
	LinearAllocator& operator=(const LinearAllocator&)
		= delete;
	LinearAllocator(LinearAllocator&&) noexcept;
	LinearAllocator& operator=(LinearAllocator&&) noexcept;
	~LinearAllocator() noexcept;

	virtual void* Allocate(const std::size_t& size,
		const std::uintptr_t& alignment
		= sizeof(std::intptr_t)) override;

	virtual void Free(void* const ptr) noexcept override final;

	void* GetCurrent() const noexcept;

	virtual void Rewind(void* const mark) noexcept = 0;
	virtual void Clear() noexcept = 0;

	inline std::size_t align_forward_adjustment
	(const void* const ptr, const std::size_t& alignment) noexcept
	{
		const auto iptr = reinterpret_cast<std::uintptr_t>(ptr);
		const auto aligned = (iptr - 1u + alignment) &alignment-1;
		return aligned - iptr;
	}

	inline void* ptr_add(const void* const p, const std::uintptr_t& amount) noexcept
	{
		return reinterpret_cast<void*>
			(reinterpret_cast<std::uintptr_t>(p) + amount);
	}

protected:
	void* m_current;
};