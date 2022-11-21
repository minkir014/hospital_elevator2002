#include "ArrayBag.h"
#include "Elevator.h"
#include "Pickable.h"
#include <string>
using namespace std;

Elevator::Elevator(int CCurrentFloor, int CSpeed, int CCapacity):Elevatorhead(CCapacity)
{
	CurrentFloor = CCurrentFloor;
	Speed = CSpeed;
	Capacity = CCapacity;
}

Elevator::~Elevator()
{
}