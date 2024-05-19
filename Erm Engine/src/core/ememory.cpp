#include "ememory.h"
#include <vector>
static struct memoryStats stats;



static const char* memoryTagStrings[MEMORY_TAG_MAX_TAGS] = {
	"UNKNOWN    ",
	"ARRAY      ",
	"DARRAY     ",
	"DICT       ",
	"RING_QUEUE ",
	"BST        ",
	"STRING     ",
	"APPLICATION",
	"JOB        ",
	"TEXTURE    ",
	"MAT_INST   ",
	"RENDERER   ",
	"GAME       ",
	"TRANSFORM  ",
	"ENTITY     ",
	"ENTITY_NODE",
	"SCENE      " };


void EMemory::InitalizeMemory()
{
	platform->PlatformZeroMemory(&stats, sizeof(stats));

}

void EMemory::ShutdownMemory()
{
	
}

void* EMemory::EAllocate(u64 size, memoryTag tag)
{

	if (tag == MEMORY_TAG_UNKNOWN) {
		EWARN("EAllocate called using Unknown memory tag, re class this allocation!");
	}
	stats.totalAllocated += size;
	stats.taggedAllocations[tag] += size;

	//todo make it less shit
	void* block = platform->PlatformAllocate(size, false);

	platform->PlatformZeroMemory(block, size);

	return block;
}

void* EMemory::EFree(void* block, u64 size, memoryTag tag)
{
	if (tag == MEMORY_TAG_UNKNOWN) {
		EWARN("EAllocate called using Unknown memory tag, re class this allocation!");
	}
	stats.totalAllocated -= size;
	stats.taggedAllocations[tag] -= size;

	platform->PlatformFree(block, false);

	return block;

}

void EMemory::EUpdateTag(u64 size, memoryTag tag)
{
	stats.totalAllocated += size;
	stats.taggedAllocations[tag] += size;

}

void* EMemory::EZeroMemory(void* block, u64 size)
{
	return platform->PlatformZeroMemory(block, size);
}

void* EMemory::ECopyMemory(void* dest, const void* source, u64 size)
{
	return platform->PlatformCopyMemory(dest, source, size);
}

void* EMemory::ESetMemory(void* dest, i32 value, u64 size)
{
	return platform->PlatformSetMemory(dest, value, size);
}

char* EMemory::GetMemoryUsageString()
{
	const u64 gib = 1024 * 1024 * 1024;
	const u64 mib = 1024 * 1024;
	const u64 kib = 1024;

	char buffer[8000] = "System memory use (tagged):\n";
	u64 offset = strlen(buffer);
	for (u32 i = 0; i < MEMORY_TAG_MAX_TAGS; ++i) {
		char unit[4] = "XiB";
		float amount = 1.0f;
		if (stats.taggedAllocations[i] >= gib) {
			unit[0] = 'G';
			amount = stats.taggedAllocations[i] / (float)gib;
		}
		else if (stats.taggedAllocations[i] >= mib) {
			unit[0] = 'M';
			amount = stats.taggedAllocations[i] / (float)mib;
		}
		else if (stats.taggedAllocations[i] >= kib) {
			unit[0] = 'K';
			amount = stats.taggedAllocations[i] / (float)kib;
		}
		else {
			unit[0] = 'B';
			unit[1] = 0;
			amount = (float)stats.taggedAllocations[i];
		}

		i32 length = snprintf(buffer + offset, 8000, "  %s: %.2f%s\n", memoryTagStrings[i], amount, unit);
		offset += length;
	}
	char* out_string = _strdup(buffer);
	return out_string;

}

