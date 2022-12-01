#include "EventArrival.h"
#include "Defs.h"
#include "Hospital.h"



EventArrival::EventArrival(EventTypes CEventType, int CID, int CPriority, int CArrivaltime, E_UserType CType, int CSrcfloor, int CTrgfloor) : Event(CEventType, CArrivaltime, CID)
{
	Priority = CPriority;
	Type = CType;
	Srcfloor = CSrcfloor;
	Trgfloor = CTrgfloor;

}

bool EventArrival::execute(Hospital* hos) {
	Pickable* pick = new Pickable(ID, EventTime, Trgfloor);
	PickablePtr ptr(pick);

	if (Trgfloor - Srcfloor > 0)
		hos->getFloor(Srcfloor)->EnqueueUp(ptr);
	else
		hos->getFloor(Srcfloor)->EnqueuDown(ptr);

	return true;
}

EventArrival::~EventArrival()
{}
