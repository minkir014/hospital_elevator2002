#pragma once
#include "Event.h"
#include "Pickable.h"
class EventArrival :public Event
{
private:
	Pickable* PickablePTR;

public:
	EventArrival(int CID, int CPriority, int CArrivaltime, string CType, int CSrcfloor, int CTrgfloor, int CEventnumber = 0);
	~EventArrival();
};

