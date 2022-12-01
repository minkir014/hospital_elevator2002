#pragma once
#include <string>
#include "Defs.h"
using namespace std;

class Hospital;

class Event
{
protected:
	int EventTime;		//Time step
	int ID;				//this ID is for cargo ,visitors,patients
	EventTypes EventType;

public:
	Event(EventTypes CEventType, int CEventTime,int CID);
	virtual bool execute(Hospital* hos) =0 ;
	int getEventTime() const;
	virtual ~Event() {}
};




