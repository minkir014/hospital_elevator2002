#include "EventArrival.h"
#include "Defs.h"



EventArrival::EventArrival(EventTypes CEventType, int CID, int CPriority, int CArrivaltime, E_UserType CType, int CSrcfloor, int CTrgfloor) : Event(CEventType, CArrivaltime, CID)
{
	Pickable* Pickableptr = new Pickable(CID, CPriority, CArrivaltime, CType, CSrcfloor, CTrgfloor);
	PickablePTR.setPickablePtr(Pickableptr);
}
EventArrival::~EventArrival()
{}

PickablePtr EventArrival::getPickablePtr() const { return PickablePTR; }