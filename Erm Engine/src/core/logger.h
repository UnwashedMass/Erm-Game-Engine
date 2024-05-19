#pragma once

#include "defines.h"
#include "platform/platform.h"

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

#if RELEASE ==1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0

#endif // RELEASE ==1


typedef enum log_level {
	LOG_LEVEL_FATAL = 0,
	LOG_LEVEL_ERROR =1,
	LOG_LEVEL_WARN =2,
	LOG_LEVEL_INFO =3,
	LOG_LEVEL_DEBUG =4,
	LOG_LEVEL_TRACE =5
};log_level;

bool InitializeLogging();
void ShutdownLogging();

EAPI void LogOutput(log_level level, const char* message, ...);

#define EFATAL(message, ...) LogOutput(LOG_LEVEL_FATAL, message, __VA_ARGS__);
#ifndef EERROR

#define EERROR(message, ...) LogOutput(LOG_LEVEL_ERROR,message, __VA_ARGS__);
#endif // !GERROR

#if LOG_WARN_ENABLED ==1
#define EWARN(message, ...) LogOutput(LOG_LEVEL_WARN,message, __VA_ARGS__);
#else
#define EWARN(message,...)
#endif


#if LOG_INFO_ENABLED ==1
#define EINFO(message, ...) LogOutput(LOG_LEVEL_INFO,message, __VA_ARGS__);
#else
#define EINFO(message,...)
#endif

#if LOG_DEBUG_ENABLED ==1
#define EDEBUG(message, ...) LogOutput(LOG_LEVEL_DEBUG,message, __VA_ARGS__);
#else
#define EDEBUG(message,...)
#endif


#if LOG_TRACE_ENABLED ==1
#define ETRACE(message, ...) LogOutput(LOG_LEVEL_TRACE,message, __VA_ARGS__);
#else
#define ETRACE(message,...)
#endif