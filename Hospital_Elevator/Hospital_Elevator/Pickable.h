#pragma once
#include <string>
using namespace std;


class Pickable
{
private:
	int ID;					//unique for each entity
	int Priority;			//0 for Visitors ,-1 for Cargo ,<0 for Patients  
	int ArrivalTime;		//The time which the entity has arrived
	string Type;			//"Patients" , "Visitors" , "Cargo"
	int Srcfloor;			//Source floor 
	int Trgfloor;			//Target floor

public:
	Pickable(int CID, int CPriority, int CArrivaltime, string CType,int CSrcfloor,int CTrgfloor);
	Pickable(int CID, int CArrivaltime, int CTrgfloor);
	~Pickable();

};
