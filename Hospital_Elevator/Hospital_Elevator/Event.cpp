#include "Event.h"
#include "Pickable.h"
#include "Hospital.h"
#include <string>
using namespace std;


Event::Event(EventTypes CEventType, int CEventTime, int CID)
{
	ID = CID;
	EventTime = CEventTime;
	EventType = CEventType;
}

int Event::getEventTime() const { return EventTime; }