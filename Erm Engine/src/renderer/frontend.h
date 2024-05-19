#pragma once
#include "renderer_types.inl"

#include"core/logger.h"
#include"core/ememory.h"
#include "backend.h"

struct meshData;
struct platformState;

class Frontend {

	EMemory* mem;

	

	b8 rendererInitialize(const char* applicationName, platformState* platState, EMemory* mem2, Backend* backe);

	void rendererShutdown();

	void rendererOnResized(u16 width, u16 height);

	b8 rendererBeginFrame(f32 deltaTime);

	b8 rendererEndFrame(f32 delta_time);

	b8 rendererDrawFrame(renderPacket* packet);
};

