#pragma once
#ifndef PLATFORM_CLASS_H
#define PLATFORM_CLASS_H

#include"defines.h"
#include"containers/stlAdaptor.h"

#include <core/asserts.h>
#include <core/logger.h>
#include <algorithm>  
#include <memory>
#include<vector>
const std::size_t totalMem = 2000000;


typedef struct platformState {
	//the type will be determined on the different implementation
	void* internalState;
} platformState;

class Platform {
public:
	





    b8 PlatformStartup(platformState* platState, const char* appName, i32 x, i32 y, i32 width, i32 height);

	void PlatformShutdown(platformState* platState);

	b8 PlatformPumpMessages(platformState* platState);



	void* PlatformAllocate(u64 size, b8 aligned);




	void PlatformFree(void* block, b8 aligned);

	void* PlatformZeroMemory(void* block, u64 size);

	void* PlatformCopyMemory(void* destination, const void* source, u64 size);

	void* PlatformSetMemory(void* destination, i32 value, u64 size);

	void PlatformConsoleWrite(const char* message, u8 color);
	void PlatformConsoleWriteError(const char* message, u8 color);

	f64 PlatformGetAbsoluteTime();
	
	void PlatformSleep(u64 miliseconds);
};




#endif // !PLATFORM_CLASS_H
