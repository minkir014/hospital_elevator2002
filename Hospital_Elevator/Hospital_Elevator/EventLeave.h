#pragma once
#include "Event.h"
#include "Defs.h"
#include "PickablePtr.h"

class EventLeave : public Event {
public:
	EventLeave(EventTypes CEventType, int CEventTime, int CID);
	bool execute(Hospital* hos);
	~EventLeave();
};