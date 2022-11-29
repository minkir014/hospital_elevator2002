#include "Event.h"
#include "Pickable.h"
#include <string>
using namespace std;


Event::Event(Events CEventType, int CEventTime, int CID,int CEventnumber=0)
{
	Eventnumber = CEventnumber;
	ID = CID;
	EventTime = CEventTime;
	EventType = CEventType;
}

Event::~Event()
{
}