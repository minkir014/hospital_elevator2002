#include "EventStair.h"
#include "Hospital.h"

EventStair::EventStair(EventTypes CEventType, int CEventTime, int CID) : Event(CEventType, CEventTime, CID) { }

EventStair::~EventStair() { }

bool EventStair::execute(Hospital* hos) {
	PickablePtr ptr(ID);
	// return hos
}