#include "Pickable.h"
#include <string>
#include "Defs.h"
using namespace std;



Pickable::Pickable(int CID, int CPriority, int CArrivaltime, E_UserType CType, int CSrcfloor, int CTrgfloor) //Constructor for all parameters
{
	ID = CID;
	Emergency = CPriority;
	ArrivalTime = CArrivaltime;
	Type = CType;
	Srcfloor = CSrcfloor;
	Trgfloor = CTrgfloor;
	ServiceBegining = 0;
}
Pickable::Pickable(int CID, int CArrivaltime, int CTrgfloor)//constructor for visitors assumes Type Priority and source floor
{
	ID = CID;
	Emergency = 1;
	ArrivalTime = CArrivaltime;
	Type = V;
	Srcfloor = 0;
	Trgfloor = CTrgfloor;
	ServiceBegining = 0;
}

int Pickable::getID() { return ID; }
int Pickable::getPriority() { return Priority; }
void Pickable::resetPriority(int PriorityVariable, bool stairsOrCompleted) { 
	if (!stairsOrCompleted)
		if (Type == P)
			Priority = (PriorityVariable - ArrivalTime) * Emergency + 100000;
		else if (Type == V)
			Priority = (PriorityVariable - ArrivalTime) * Emergency + 1;
		else
			Priority = (PriorityVariable - ArrivalTime) * Emergency - 100000;
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

void Pickable::setServiceTime(int ST) {	ServiceBegining = ST; }

int Pickable::getServiceTime() const { return ServiceBegining; }

Pickable::~Pickable()
{
}