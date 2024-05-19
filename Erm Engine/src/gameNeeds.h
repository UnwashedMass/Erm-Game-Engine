#pragma once

#include "core/application.h"

typedef struct game {
	// the application configuration
	applicationConfig appConfig;

	//functionpointer to ames init function
	b8(*initialize)(struct game* gameInstance);
	// function pointer to games update function
	b8(*update)(struct game* gameInstance, f32 deltaTime);
	// function pointer to games render funciton
	b8(*render)(struct game* gameInstance, f32 deltaTime);
	// function pointer to handle game resizes
	void(*onResize)(struct game* gameInstance, u32 width, u32 height);
	// game specic game state. created and managed by the game
	void* state;



} game;