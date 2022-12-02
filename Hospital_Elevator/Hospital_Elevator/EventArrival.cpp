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
	Pickable* pick = new Pickable(ID, Priority, EventTime, Type, Srcfloor, Trgfloor);
	PickablePtr ptr(pick, hos);

	if (Trgfloor - Srcfloor > 0)
		hos->getFloor(Srcfloor)->EnqueueUp(ptr);
	else
		hos->getFloor(Srcfloor)->EnqueuDown(ptr);

	return true;
}

EventArrival::~EventArrival()
{}
