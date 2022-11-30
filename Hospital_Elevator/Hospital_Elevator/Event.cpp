#include "Event.h"
#include "Pickable.h"
#include <string>
using namespace std;


Event::Event(EventTypes CEventType, int CEventTime, int CID)
{
	ID = CID;
	EventTime = CEventTime;
	EventType = CEventType;
}

Event::~Event()
{
}