#pragma once
#include "Event.h"
#include "PickablePtr.h"
#include "Defs.h"
class EventArrival :public Event
{
private:
	int Priority;
	E_UserType Type;
	int Srcfloor;
	int Trgfloor;

public:
	EventArrival(EventTypes CEventType, int CID, int CPriority, int CArrivaltime, E_UserType CType, int CSrcfloor, int CTrgfloor);
	bool execute(Hospital* hos);

	~EventArrival();
};

// Execute Event should pass a hospital pointer.
