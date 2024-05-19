#include "application.h"
#include "gameNeeds.h"





b8 Application::ApplicationCreate(game* gameInst)
{

	if (initialized) {
		EERROR("applicationCreate called more than once...");
		return false;
	}

	appState.gameInst = gameInst;
	//initialize subsystems
	InitializeLogging();
	EFATAL("Testo: %f", 32.0f);
	EERROR("Testo: %f", 32.0f);
	EWARN("Testo: %f", 32.0f);
	EINFO("Testo: %f", 32.0f);
	EDEBUG("Testo: %f", 32.0f);
	ETRACE("Testo: %f", 32.0f);

	event.mem = appState.mem;

	if (!event.EventInitalize()) {
		EERROR("even system failed init. App cannot continue");
		return false;
	}
	appState.isRunning = true;
	appState.isSuspended = false;


	if (!platform->PlatformStartup(&appState.platform, gameInst->appConfig.name, gameInst->appConfig.startPosX,
		gameInst->appConfig.startPosY, gameInst->appConfig.startWidth, gameInst->appConfig.startHeight)) {
		return false;
	}


	if (!appState.gameInst->initialize(appState.gameInst)) {
		EFATAL("Game failed to initalize!!!");
		return false;
	}

	appState.gameInst->onResize(appState.gameInst, appState.width, appState.height);

	initialized = true;

	return true;
}

b8 Application::ApplicationRun()
{
	clockData* clock = appState.clockD.getClock();
	appState.clockD.clockStart(clock,platform);
	appState.clockD.clockUpdate(clock,platform);

	appState.lastTime = clock->elapsed;
	f64 runningTime = 0;
	u8 frameCount = 0;
	//TODO allow for unlimited frames!
	f64 targetFrameSecconds = 1.0f / 60;

	EINFO(appState.mem->GetMemoryUsageString());
	while (appState.isRunning) {

		if (!platform->PlatformPumpMessages(&appState.platform)) {
			appState.isRunning = false;
		}

		if (!appState.isSuspended) {
			appState.clockD.clockUpdate(clock,platform);
			f64 currTime = clock->elapsed;
			f64 delta = (currTime - appState.lastTime);
			f64 frameStartTime = platform->PlatformGetAbsoluteTime();

			if (!appState.gameInst->update(appState.gameInst, delta)) {
				EFATAL("Game update has failed, shutting down!!!");
				appState.isRunning = false;
				break;
			}
			//TODO dont forget to change back to delta
			if (!appState.gameInst->render(appState.gameInst, delta)) {
				EFATAL("Game render has failed, shutting down!!!");
				appState.isRunning = false;
				break;
			}

			//renderPacket packet;
			//packet.deltaTime = delta;
			//rendererDrawFrame(&packet);

			f64 frameEndTime = platform->PlatformGetAbsoluteTime();
			f64 frameElapsedTime = frameEndTime - frameStartTime;
			runningTime += frameElapsedTime;
			f64 remainingSeconds = targetFrameSecconds - frameElapsedTime;

			if (remainingSeconds > 0) {
				u64 remainingMs = (remainingSeconds * 1000);

				b8 limitFrames = false;
				if (remainingMs > 0 && limitFrames) {
					platform->PlatformSleep(remainingMs - 1);
				}
				frameCount++;
			}

			appState.lastTime = currTime;
		}


	}
	appState.isRunning = false;

	//rendererShutdown();
	platform->PlatformShutdown(&appState.platform);
	return true;
}
