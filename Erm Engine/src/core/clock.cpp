#include "clock.h"
#include "platform/platform.h"



void Clock::clockUpdate(clockData* clock,Platform* plat)
{
	if (clock->startTime != 0) {
		clock->elapsed = plat->PlatformGetAbsoluteTime() - clock->startTime;
	}
}

void Clock::clockStart(clockData* clock, Platform* plat)
{
	clock->startTime = plat->PlatformGetAbsoluteTime();
	clock->elapsed = 0;
}

void Clock::clockStop(clockData* clock)
{
	clock->startTime = 0;
}

clockData* Clock::getClock()
{
	return &clock;
}
