#include "game.h"
#include <core/logger.h>

b8 gameInitialize(game* gameInst)
{
	EDEBUG("game shit was called");
	return true;
}

b8 gameUpdate(game* gameInst, f32 deltaTime)
{
	return true;
}

b8 gameRender(game* gameInst, f32 deltaTime)
{
	return true;
}

void gameOnResize(game* gameInst, u32 width, u32 height)
{
}
