#pragma once
#include "core/application.h"
#include "core/logger.h"
#include "gameNeeds.h"
#include "core/ememory.h"

EMemory mem;

extern b8 createGame(game* outGame);

int main() {

	
	mem.InitalizeMemory();
	// request game instance
	game gameInstance;
	Application app;
	app.appState.mem = &mem;

	if (!createGame(&gameInstance)) {
		EFATAL("could not create game!!!");
		return -1;
	}
	if (!gameInstance.render || !gameInstance.update || !gameInstance.initialize || !gameInstance.onResize) {
		EFATAL("the games function pointers must be assigned!!!");
		return -2;
	}
	// initialization
	if (!app.ApplicationCreate(&gameInstance)) {
		EINFO("Application has failed to create!!!");
		return 1;
	}
	// begin game loop
	if (!app.ApplicationRun()) {
		EINFO("Application did not shutdown properly!!!");
		return 2;
	}





	mem.ShutdownMemory();
	return 0;
}