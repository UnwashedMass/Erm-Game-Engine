#include "frontend.h"

static rendererBackend* backend = 0;

b8 Frontend::rendererInitialize(const char* applicationName, platformState* platState, EMemory* mem2, Backend* backEndPtr)
{
    mem = mem2;
    backend = (rendererBackend*)mem->EAllocate(sizeof(rendererBackend*), MEMORY_TAG_RENDERER);
    //todo make configurable
    backEndPtr->rendererBackendCreate(RENDERER_BACKEND_TYPE_VULKAN, platState, backend);
    
    backend->frameNumber = 0;

    if (!backend->initialize(backend, applicationName, platState)) {
        EFATAL("renderer backend failed to initialize");
        return false;
    }
    return true;
}

void Frontend::rendererShutdown()
{
    backend->shutdown(backend);
    mem->EFree(backend, sizeof(rendererBackend), MEMORY_TAG_RENDERER);
}

void Frontend::rendererOnResized(u16 width, u16 height)
{

}

b8 Frontend::rendererBeginFrame(f32 deltaTime)
{
    return backend->beginFrame(backend, deltaTime);
}

b8 Frontend::rendererEndFrame(f32 deltaTime)
{
    b8 result = backend->endFrame(backend, deltaTime);
    backend->frameNumber++;
    return result;
}

b8 Frontend::rendererDrawFrame(renderPacket* packet)
{
    if (rendererBeginFrame(packet->deltaTime)) {
        b8 result = rendererEndFrame(packet->deltaTime);
        if (!result) {
            EERROR("renderer end frame failed :(. application shutting down!");
            return false;
        }
    }

    return true;
}
