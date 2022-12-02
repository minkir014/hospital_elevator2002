#include "Pickable.h"
#include <string>
#include "Defs.h"
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

int Pickable::getID() { return ID; }
int Pickable::getPriority() { return Priority; }
void Pickable::resetPriority(int PriorityVariable, bool stairsOrCompleted) { 
	if (!stairsOrCompleted)
		Priority = Priority;
	else
		Priority = PriorityVariable;
}

int Pickable::getArrivalTime() { return ArrivalTime; }
int Pickable::getSrcfloor() { return Srcfloor; }
int Pickable::getTrgfloor() { return Trgfloor; }
E_UserType Pickable::getType() { return Type; }

void Pickable::setTargetTime(int TT) {
	TargetTime = TT;
}

int Pickable::getTargetTime() const { return TargetTime; }

Pickable::~Pickable()
{
}