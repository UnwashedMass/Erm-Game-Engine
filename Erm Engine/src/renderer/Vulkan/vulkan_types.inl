#pragma once
#include "defines.h"
#include "core/asserts.h"
#include <vulkan/vulkan.h>

typedef struct vulkanContext {
	//holds our static data lol :)

	VkInstance instance;
	VkAllocationCallbacks* allocator;
#if defined(_DEBUG)
	VkDebugUtilsMessengerEXT debug_messenger;
#endif
} vulkanContext;

#define VK_CHECK(expr)               \
    {                                \
        EASSERT(expr == VK_SUCCESS); \
    }

