#pragma once
#include "Event.h"
#include "PickablePtr.h"
#include "Defs.h"
class EventArrival :public Event
{
private:
	PickablePtr PickablePTR;

public:
	EventArrival(EventTypes CEventType, int CID, int CPriority, int CArrivaltime, E_UserType CType, int CSrcfloor, int CTrgfloor);

	PickablePtr getPickablePtr() const;

	~EventArrival();
};

