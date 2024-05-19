#pragma once
#include "allo.h"

typedef struct FreeBlock {
	i64 size;
	FreeBlock* next;
}FreeBlock;


typedef struct AllocationHeader{
	i64 size;
	uintptr_t adjustment;

}AllocationHeader;

class FreeListAllocator : public Allocator
{
public:
	FreeListAllocator(std::size_t sizeBytes,
		void* start) noexcept;

	FreeListAllocator(const FreeListAllocator&) = delete;
	FreeListAllocator& operator=(const FreeListAllocator&)
		= delete;
	FreeListAllocator(FreeListAllocator&&) noexcept;
	FreeListAllocator& operator=(FreeListAllocator&&) noexcept;

	
	virtual void* Allocate(const std::size_t& size,
		const std::uintptr_t& alignment
		= sizeof(std::intptr_t)) override;

	virtual void Free(void* const ptr) noexcept override final;




	inline std::size_t alignForwardAdjustment
	(const void* const ptr, const std::size_t& alignment) noexcept
	{
		const auto iptr = reinterpret_cast<std::uintptr_t>(ptr);
		const auto aligned = (iptr - 1u + alignment) &alignment-1;
		return aligned - iptr;
	}


	inline u8 alignForwardAdjustmentWithHeader(const void* address, u8 alignment, u8 headerSize)
	{
		u8 adjustment = alignForwardAdjustment(address, alignment);
		u8 neededSpace = headerSize;

		if (adjustment < neededSpace)
		{
			neededSpace -= adjustment;

			//Increase adjustment to fit header 
			adjustment += alignment * (neededSpace / alignment);

			if (neededSpace % alignment > 0) adjustment += alignment;
		}

		return adjustment;
	}

	inline void* ptr_add(const void* const p, const std::uintptr_t& amount) noexcept
	{
		return reinterpret_cast<void*>
			(reinterpret_cast<std::uintptr_t>(p) + amount);
	}
	inline void* ptr_sub(const void* const p, const std::uintptr_t& amount) noexcept
	{
		return reinterpret_cast<void*>
			(reinterpret_cast<std::uintptr_t>(p) - amount);
	}

protected:
	FreeBlock* m_freeBlocks;
};