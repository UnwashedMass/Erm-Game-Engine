#include <entry.h>
#include "game.h"

#include <core/ememory.h>

// Definition of the function to creat game
b8 createGame(game* outGame) {

	outGame->appConfig.startPosX = 100;
	outGame->appConfig.startPosY = 100;
	outGame->appConfig.startWidth = 1280;
	outGame->appConfig.startHeight = 720;
	outGame->appConfig.name = (char*)"erm test bed";

	outGame->update = gameUpdate;
	outGame->render = gameRender;
	outGame->initialize = gameInitialize;
	outGame->onResize = gameOnResize;

	outGame->state = mem.EAllocate(sizeof(gameState), MEMORY_TAG_GAME);
	


	return true;
}