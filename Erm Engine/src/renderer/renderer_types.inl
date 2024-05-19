#pragma once

#include "defines.h"


typedef enum rendererBackendType {
	RENDERER_BACKEND_TYPE_OPENGL,
	RENDERER_BACKEND_TYPE_VULKAN,
	RENDERER_BACKEND_TYPE_DIRECTX,
	RENDERER_BACKEND_TYPE_METAL
} rendererBackendType;

typedef struct renderPacket {
	f32 deltaTime;
};

class rendererBackend {
public:
	struct platformState* platState;

	u64 frameNumber;

	b8(*initialize)(struct rendererBackend* backend, const char* applicationName, struct platformState* platState);

	void(*shutdown)(struct rendererBackend* backend);

	void (*resize)(struct rendererBackend* backend, u16 width, u16 height);

	b8(*beginFrame)(struct rendererBackend* backend, f32 deltaTime);
	b8(*endFrame)(struct rendererBackend* backend, f32 deltaTime);
};
