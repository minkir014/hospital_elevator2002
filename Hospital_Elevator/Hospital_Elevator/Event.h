#pragma once
#include <string>
#include "Defs.h"
using namespace std;


class Event
{
protected:
	int Eventnumber;	//identifier for Events
	int EventTime;		//Time step
	int ID;				//this ID is for cargo ,visitors,patients
	Events EventType;

public:
	Event(Events CEventType, int CEventTime,int CID,int CEventnumber);
	~Event();
};




