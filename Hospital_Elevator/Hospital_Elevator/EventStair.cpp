#include "EventStair.h"
#include "Hospital.h"

EventStair::EventStair(EventTypes CEventType, int CEventTime, int CID) : Event(CEventType, CEventTime, CID) { }

EventStair::~EventStair() { }

bool EventStair::execute(Hospital* hos) {
	PickablePtr ptr(ID);
	int c = hos->getFloorCount();

	for (int i = 0; i < c; i++)
		if (hos->getFloor(i)->DeletePickable(ptr))
			return hos->stairPickable(ptr);

	return true;
}