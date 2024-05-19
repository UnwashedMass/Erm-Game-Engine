#pragma once
#ifndef EMEMORY_CLASS_H
#define EMEMORY_CLASS_H
#include "defines.h"
#include "platform/platform.h"
#include<string>
#include <cstdio>

typedef enum memoryTag {
	// for memory use should be assifned one of these below or have a new tag created
	MEMORY_TAG_UNKNOWN,
	MEMORY_TAG_ARRAY,
	MEMORY_TAG_DARRAY,
	MEMORY_TAG_DICT,
	MEMORY_TAG_RING_QUEUE,
	MEMORY_TAG_BST,
	MEMORY_TAG_STRING,
	MEMORY_TAG_APPLICATION,
	MEMORY_TAG_JOB,
	MEMORY_TAG_TEXTURE,
	MEMORY_TAG_MATERIAL_INSTANCE,
	MEMORY_TAG_RENDERER,
	MEMORY_TAG_GAME,
	MEMORY_TAG_TRANSFORM,
	MEMORY_TAG_ENTITY,
	MEMORY_TAG_ENTITY_NODE,
	MEMORY_TAG_SCENE,

	MEMORY_TAG_MAX_TAGS
}memoryTag;

typedef struct memoryStats {
	u64 totalAllocated;
	u64 taggedAllocations[MEMORY_TAG_MAX_TAGS];
} memoryStats;


class EMemory {
public:


	void InitalizeMemory();
	void ShutdownMemory();

	EAPI void* EAllocate(u64 size, memoryTag tag);

	EAPI void* EFree(void* bloc, u64 size, memoryTag tag);
	

	EAPI void EUpdateTag(u64 size, memoryTag tag);

	EAPI void* EZeroMemory(void* block, u64 size);

	EAPI void* ECopyMemory(void* dest, const void* source, u64 size);

	EAPI void* ESetMemory(void* dest, i32 value, u64 size);

	EAPI char* GetMemoryUsageString();
private:
	Platform* platform;
};

#endif // 
