#include "Pickable.h"
#include <string>
using namespace std;



Pickable::Pickable(int CID, int CPriority, int CArrivaltime, E_UserType CType, int CSrcfloor, int CTrgfloor) //Constructor for all parameters
{
	ID = CID;
	Priority = CPriority;
	ArrivalTime = CArrivaltime;
	Type = CType;
	Srcfloor = CSrcfloor;
	Trgfloor = CTrgfloor;
}
Pickable::Pickable(int CID, int CArrivaltime, int CTrgfloor)//constructor for visitors assumes Type Priority and source floor
{
	ID = CID;
	Priority = 0;
	ArrivalTime = CArrivaltime;
	Type = V;
	Srcfloor = 0;
	Trgfloor = CTrgfloor;
}

Pickable::~Pickable()
{
}