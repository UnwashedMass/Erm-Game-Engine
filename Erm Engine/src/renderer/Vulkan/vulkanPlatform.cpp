#include "vulkanPlatform.h"

void PlatformGetRequiredExtensionNames(std::vector<const char*>* array)
{
#if EPLATFORM_WINDOWS
	array->push_back("VK_KHR_win32_surface");
#endif
}
