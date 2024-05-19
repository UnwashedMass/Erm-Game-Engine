#pragma once
#ifndef CLOCK_CLASS_H
#define CLOCK_CLASS_H


#include "defines.h"
#include "platform/platform.h"

typedef struct clockData {
	f64 startTime;
	f64 elapsed;
} clockData;

class Clock {
public:



	void clockUpdate(clockData* clock, Platform* plat);

	void clockStart(clockData* clock, Platform* plat);

	void clockStop(clockData* clock);

	clockData* getClock();

private:
	clockData clock;
};

#endif // !CLOCK_CLASS_H
