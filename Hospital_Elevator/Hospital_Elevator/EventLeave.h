#pragma once
#include "Event.h"
#include "Defs.h"
#include "PickablePtr.h"

class EventLeave : Event {
public:
	bool execute(Hospital* hos);
};