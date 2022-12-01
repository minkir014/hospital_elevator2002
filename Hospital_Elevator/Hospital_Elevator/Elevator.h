#pragma once
#include "ArrayBag.h"
#include "Pickable.h"
#include <string>
using namespace std;

class Elevator
{
private:
	int CurrentFloor;		//The floor The Elevetor is on
	int timeOfLastFloor;    // The timestep it was at
	int Speed;				//Time steps needed to move up or down a Floor
	int Capacity;			//max capicity of the elevator 
	ArrayBag<Pickable*> Elevatorhead;	//bag containig People in the elevator
public:
	Elevator(int CSpeed, int CCapacity);
	~Elevator();

};


