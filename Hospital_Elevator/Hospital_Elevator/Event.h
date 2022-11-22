#pragma once
#include <string>
using namespace std;


class Event
{
protected:
	int Eventnumber;	//identifier for Events
	int EventTime;		//Time step
	int ID;				//this ID is for cargo ,visitors,patients

public:
	Event(int CEventTime,int CID,int CEventnumber);
	~Event();
};




