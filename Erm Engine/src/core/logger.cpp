#include "logger.h"
#include "asserts.h"

//TODO TEMPORARY

#include<iostream>
#include<string>
#include<cstdarg>
#include <cstdio>

void Report_assertion_failure(const char* expression, const char* message, const char* file, __int32 line) {
	LogOutput(LOG_LEVEL_FATAL, "Assertion FAILURE: %s, message: '%s', in file: %s, line: %d\n", expression, message, file, line);
}

bool InitializeLogging()
{
	return false;
	//TODO create log file
}

void ShutdownLogging()
{
	//TODO Clean logg/write queued entries.
}

void LogOutput(log_level level, const char* message, ...)
{
	Platform plat;
	const char* levelString[6] = { "[FATAL]:","[ERROR]:" ,"[WARN]:" ,"[INFO]:" ,"[DEBUG]:" ,"[TRACE]:" };
	bool isError = level < LOG_LEVEL_WARN;

	// places the memory on the stack for SPEED, limits messages to 32,000
	// i dont foresee a situation where that limit is reached lol
	const i32 msgLength = 32000;
	char outMessage[msgLength];
	memset(outMessage, 0, sizeof(outMessage));

	va_list argPtr;
	va_start(argPtr, message);
	vsnprintf(outMessage, msgLength, message, argPtr);
	va_end(argPtr);

	char outMessageBuffer2[msgLength];
	sprintf_s(outMessageBuffer2, "%s%s\n", levelString[level], outMessage);

	if (isError) {
		plat.PlatformConsoleWriteError(outMessageBuffer2, level);

	}
	else {
		plat.PlatformConsoleWrite(outMessageBuffer2, level);
	}



}