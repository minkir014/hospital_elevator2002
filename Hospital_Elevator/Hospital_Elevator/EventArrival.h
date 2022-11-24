#pragma once
#include "Event.h"
#include "Pickable.h"
#include "Defs.h"
class EventArrival :public Event
{
private:
	Pickable* PickablePTR;

public:
	EventArrival(Events CEventType, int CID, int CPriority, int CArrivaltime, E_UserType CType, int CSrcfloor, int CTrgfloor, int CEventnumber = 0);
	~EventArrival();
};

