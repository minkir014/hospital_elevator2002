#pragma once
#include <string>
#include "Defs.h"
using namespace std;


class Pickable
{
private:
	int ID;					//unique for each entity
	int Priority;			//0 for Visitors ,-1 for Cargo ,<0 for Patients  
	int ArrivalTime;		//The time which the entity has arrived
	E_UserType Type;			//"Patients" , "Visitors" , "Cargo"
	int Srcfloor;			//Source floor 
	int Trgfloor;			//Target floor
	int TargetTime;			// Target Time

public:
	Pickable(int CID, int CPriority, int CArrivaltime, E_UserType CType,int CSrcfloor,int CTrgfloor);
	Pickable(int CID, int CArrivaltime, int CTrgfloor);
	int getID();
	int getPriority();
	void resetPriority(int PriorityVariable, bool stairs);
	int getArrivalTime();
	int getSrcfloor();
	int getTrgfloor();
	int getTargetTime() const;
	void setTargetTime(int TT);
	E_UserType getType();
	~Pickable();

};
