#pragma once
#include "Event.h"
#include "Defs.h"
#include "PickablePtr.h"

class EventStair : Event {
public:
	EventStair(EventTypes CEventType, int CEventTime, int CID);
	~EventStair();

	bool execute(Hospital* hos);
};