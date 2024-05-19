#pragma once
#ifndef  BACKEND_CLASS_H
#define BACKEND_CLASS_H
#include "renderer_types.inl"





struct platformState;

class Backend {
public:
	b8 rendererBackendCreate(rendererBackendType type, struct platformState* platState, rendererBackend* outRendererBackend);
	void rendererBackendDestroy(rendererBackend* rendererBackend);

};

#endif // ! BACKEND_CLASS_H


