#pragma once
#ifndef VULKANBACKEND_CLASS_H
#define VULKANBACKEND_CLASS_H
#include "renderer/backend.h"
#include "vulkan_types.inl"
#include "core\logger.h"
#include "vulkanPlatform.h"

#include "platform\platform.h"
#include <string>
#include <vector>
#include "core\ememory.h"

class VulkanBackend {

public:


#endif // !VULKANBACKEND_CLASS_H
};
b8 VulkanRendererBackendInit(rendererBackend* backend, const char* appName, struct platformState* platState);

void VulkanRendererShutdown(rendererBackend* backend);

void VulkanRendererBackendOnResize(rendererBackend* backend, u16 width, u16 height);

b8 VulkanRendererBackendBeginFrame(rendererBackend* backend, f32 deltaTime);
b8 VulkanRendererBackendEndFrame(rendererBackend* backend, f32 deltaTime);

