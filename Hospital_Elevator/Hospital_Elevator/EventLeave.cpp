#include "EventLeave.h"
#include "Hospital.h"
EventLeave::~EventLeave() {}
EventLeave::EventLeave(EventTypes CEventType, int CEventTime, int CID) : Event(CEventType , CEventTime , CID) {}
bool EventLeave::execute(Hospital* hos) {
	hos->getFloor(0)->getPickable(ID);
	return false; 
}