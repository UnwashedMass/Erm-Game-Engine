#include "event.h"

#define MAX_MESSAGE_CODES 16384

typedef struct registeredEvent {
	void* listener;
	PFNOnEvent callback;
}registeredEvent;

typedef struct eventCodeEntry {
	std::vector<registeredEvent*> events;
}eventCodeEntry;

typedef struct eventSystemState {
	std::vector<eventCodeEntry> registered[MAX_MESSAGE_CODES];
} eventSystemState;


static b8 isInitialized = false;
static eventSystemState state;


b8 Event::EventInitalize()
{
	if (isInitialized) {
		return false;
	}
	mem->EZeroMemory(&state, sizeof(state));
	isInitialized = true;
	return true;
}

void Event::EventShutdown()
{
	for (u16 i = 0;i < MAX_MESSAGE_CODES; i++) {
		if (state.registered->at(i).events.size()!= 0) {
			state.registered->at(i).events.clear();
		}
	}
}

b8 Event::EventRegister(u16 code, void* listener, PFNOnEvent onEvent)
{
	if (isInitialized == false) {
		return false;
	}
	if (state.registered->at(code).events.size() == 0) {
		std::vector<registeredEvent*> erm;
		state.registered->at(code).events = erm;
	}

	u64 registeredCount = state.registered->at(code).events.size();
	for (u64 i = 0; i < registeredCount; i++) {
		if (state.registered->at(code).events.at(i)->listener == listener) {
			return false;
		}
	}

	registeredEvent event;
	event.listener = listener;
	event.callback = onEvent;
	state.registered->at(code).events.push_back(&event);


	return true;
}

b8 Event::EventUnregister(u16 code, void* listener, PFNOnEvent on_event)
{
	if (!isInitialized) {
		return false;
	}

	// On nothing is registered for the code, boot out.
	if (state.registered->at(code).events.size() == 0) {
		// TODO: warn
		return false;
	}

	u64 registeredCount = state.registered->at(code).events.size();
	for (u64 i = 0; i < registeredCount; ++i) {
		registeredEvent e = (registeredEvent)state.registered->at(code).events.at(i);
		if (e.listener == listener && e.callback == on_event) {
			// Found one, remove it
			registeredEvent popped_event = (registeredEvent)state.registered->at(code).events.at(i);
			state.registered->at(code).events.erase(state.registered->at(code).events.begin()+i);
			return true;
		}
	}

	// Not found.
	return false;
}

b8 Event::EventFire(u16 code, void* sender, eventContext context)
{
	if (isInitialized == false) {
		return false;
	}
	if (state.registered->at(code).events.size() == 0) {
		return false;
	}

	u64 registeredCount = state.registered->at(code).events.size();
	for (u64 i = 0; i < registeredCount;i++) {
		registeredEvent e = (registeredEvent) state.registered->at(code).events.at(i);
		if (e.callback(code, sender, e.listener, context)) {
			return true;
		}
	}
	return false;
}
