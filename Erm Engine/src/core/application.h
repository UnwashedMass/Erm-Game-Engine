#pragma once
#ifndef APPLICATION_CLASS_H
#define APPLICATION_CLASS_H

#include "defines.h"
#include "asserts.h"
#include "logger.h"
#include "platform/platform.h"
#include"ememory.h"
#include "event.h"
#include "clock.h"

struct game;
typedef struct applicationState {
	EMemory* mem;
	game* gameInst;
	b8 isRunning;
	b8 isSuspended;
	platformState platform;
	Clock clockD;
	i16 width;
	i16 height;
	f64 lastTime;

} applicationState;

typedef struct applicationConfig {

	i16 startPosX;
	i16 startPosY;
	i16 startWidth;
	i16 startHeight;

	char* name;
} applicationConfig;



class Application {
	

public:
	Event event;
	
	static inline b8 initialized = false;
	static inline applicationState appState;
	static inline Platform* platform;



	EAPI b8 ApplicationCreate(game* gameInst);

	EAPI b8 ApplicationRun();

private:

	
};

#endif // !APPLICATION_CLASS_H
