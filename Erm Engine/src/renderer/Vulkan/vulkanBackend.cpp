#include "vulkanBackend.h"

static vulkanContext context;
b8 VulkanRendererBackendInit(rendererBackend* backend, const char* appName, platformState* platState)
{
	context.allocator = 0;

	VkApplicationInfo appInfo = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
	appInfo.apiVersion = VK_API_VERSION_1_2;
	appInfo.pApplicationName = appName;
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Erm Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

	VkInstanceCreateInfo createInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
	createInfo.pApplicationInfo = &appInfo;


	std::vector<const char*> requiredExtension;
	
	requiredExtension.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
	PlatformGetRequiredExtensionNames(&requiredExtension);
#if defined(_DEBUG)
	requiredExtension.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	EDEBUG("Required extensions:");
	u32 length = requiredExtension.size();
	for (u32 i = 0; i < length; i++) {
		EDEBUG(requiredExtension.at(i));
	}
#endif
	createInfo.enabledExtensionCount = requiredExtension.size();
	int lol = requiredExtension.size();
	const char*const a = requiredExtension[0];
	createInfo.ppEnabledExtensionNames = &a;

	const char** requiredValidationLayerNames = 0;
	u32 requiredValidationLayerCount = 0;


#if defined(_DEBUG)
	std::vector<const char**> requiredValidationLayerList;
	
	requiredValidationLayerList.push_back((const char**)"VK_LAYERLKHRONOS_validation");
	requiredValidationLayerCount = requiredValidationLayerList.size();

	u32 availableLayerCount = 0;
	VK_CHECK(vkEnumerateInstanceLayerProperties(&availableLayerCount, 0));
	std::vector <VkLayerProperties*> availableLayers;
	VkLayerProperties* validationLayerArr = availableLayers[0];
	VK_CHECK(vkEnumerateInstanceLayerProperties(&availableLayerCount, validationLayerArr));

	for (u32 i = 0; i < requiredValidationLayerCount; i++) {
		EINFO("searching for layer!: %s...", requiredValidationLayerList[i]);
		b8 found = false;
		for (u32 j = 0; j < availableLayerCount; j++) {
			if (requiredValidationLayerList[i] == (const char**)availableLayers[j]->layerName) {
				found = true;
				EINFO("found");
				break;
			}
		}
		if (!found) {
			EFATAL("Required Validation Layer is missing: %s", requiredValidationLayerList[i]);
		}
	}
	EINFO("all required validation layers are present")
#endif
	createInfo.enabledLayerCount = requiredValidationLayerCount;
	createInfo.ppEnabledLayerNames = requiredValidationLayerNames;

	VkResult result = vkCreateInstance(&createInfo, context.allocator, &context.instance);
	if (result != VK_SUCCESS) {
		EERROR("VKCreateInstance failed with result: %u", result);
		return false;
	}
	EINFO("vulkan renderer initialized successfully!");
	return true;


}

void VulkanRendererShutdown(rendererBackend* backend) {

}

void VulkanRendererBackendOnResize(rendererBackend* backend, u16 width, u16 height) {

}

b8 VulkanRendererBackendBeginFrame(rendererBackend* backend, f32 deltaTime) {
	return true;
}
b8 VulkanRendererBackendEndFrame(rendererBackend* backend, f32 deltaTime) {
	return true;
}