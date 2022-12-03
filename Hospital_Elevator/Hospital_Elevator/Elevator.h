#pragma once
#include "ArrayBag.h"
#include "Pickable.h"
#include <string>
#include "Defs.h"
using namespace std;

class Elevator
{
private:
	int CurrentFloor;		//The floor The Elevetor is on
	int timeOfLastFloor;    // The timestep it was at
	int Speed;				//Time steps needed to move up or down a Floor
	int Capacity;			//max capicity of the elevator 
	ElevatorState state; 
	ElevatorState LastState; 
	ArrayBag<Pickable*> Elevatorhead;	//bag containig People in the elevator
public:
	Elevator(int CSpeed, int CCapacity);
	void incrementFloor();
	void decrementFloor();
	ElevatorState getState() const; 
	int getCurrentFloor() const; 
	int getSpeed() const; 
	int getTimeOfLastFloor() const;
	void UpdateState( int & timestep, int &Floor , int &maxFloor, bool& load);
	int getCapacity() const; 

	~Elevator();

};


