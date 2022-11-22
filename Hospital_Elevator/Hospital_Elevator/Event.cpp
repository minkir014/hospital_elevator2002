#include "Event.h"
#include "Pickable.h"
#include <string>
using namespace std;

Event::Event(int CEventTime, int CID,int CEventnumber=0)
{
	Eventnumber = CEventnumber;
	ID = CID;
	EventTime = CEventTime;
}

Event::~Event()
{
}