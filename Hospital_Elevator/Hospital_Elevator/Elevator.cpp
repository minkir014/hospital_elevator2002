#include "ArrayBag.h"
#include "Elevator.h"
#include "Pickable.h"
#include <string>
using namespace std;

Elevator::Elevator(int CSpeed, int CCapacity):Elevatorhead(CCapacity)
{
	CurrentFloor = 0;
	Speed = CSpeed;
	Capacity = CCapacity;
}

Elevator::~Elevator()
{
}