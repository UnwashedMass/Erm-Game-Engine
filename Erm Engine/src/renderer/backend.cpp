#include "backend.h"
#include"Vulkan/vulkanBackend.h"

b8 Backend::rendererBackendCreate(rendererBackendType type, platformState* platState, rendererBackend* outRendererBackend)
{
	outRendererBackend->platState = platState;
	if (type == RENDERER_BACKEND_TYPE_VULKAN) {

		outRendererBackend->initialize = VulkanRendererBackendInit;
		outRendererBackend->shutdown = VulkanRendererShutdown;
		outRendererBackend->beginFrame = VulkanRendererBackendBeginFrame;
		outRendererBackend->endFrame = VulkanRendererBackendEndFrame;
		outRendererBackend->resize = VulkanRendererBackendOnResize;
		return true;
	}


	if (type == RENDERER_BACKEND_TYPE_OPENGL) {
		return true;
	}

	return false;
}

void Backend::rendererBackendDestroy(rendererBackend* rendererBackend)
{
	
}
