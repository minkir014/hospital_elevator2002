#include "EventLeave.h"
#include "Hospital.h"


EventLeave::~EventLeave() {}
EventLeave::EventLeave(EventTypes CEventType, int CEventTime, int CID) : Event(CEventType , CEventTime , CID) {}

bool EventLeave::execute(Hospital* hos) {
	PickablePtr ptr(ID);
	if (hos->getFloor(0)->DeletePickable(ptr)) {
		hos->countLeave();
		return true;
	}

	return false;
}