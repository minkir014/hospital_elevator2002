#include "EventArrival.h"



EventArrival::EventArrival(int CID, int CPriority, int CArrivaltime, string CType, int CSrcfloor, int CTrgfloor,int CEventnumber=0):Event(CArrivaltime, CID, CEventnumber)
{
	Event(CArrivaltime,CID, CEventnumber);
	PickablePTR = new Pickable(CID, CPriority, CArrivaltime, CType, CSrcfloor, CTrgfloor);
}
EventArrival::~EventArrival()
{}