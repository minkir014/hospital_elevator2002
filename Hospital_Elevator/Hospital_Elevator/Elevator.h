#pragma once
#include "LinkedHeap.h"
#include "PickablePtr.h"
#include <string>
#include "Defs.h"
using namespace std;

class Hospital;
class Elevator
{
private:
	int CurrentFloor;		//The floor The Elevetor is on
	int TargetFloor;		//The floor the elevator is going to
	int timeOfLastFloor;    // The timestep it was at
	int Speed;				//Time steps needed to move up or down a Floor
	int Capacity;			//max capicity of the elevator 
	ElevatorState state; 
	ElevatorState LastState; 
	LinkedHeap<PickablePtr> Elevatorhead;	//Heap containig People in the elevator

	Hospital* hos;
	ElevatorType type;
public:
	Elevator(int CSpeed, int CCapacity, Hospital* hos, ElevatorType type);
	void incrementFloor();
	void decrementFloor();
	ElevatorState getState() const; 
	ElevatorState getPreviousState() const;
	int getCurrentFloor() const; 
	int getTargetFloor() const;
	int getSpeed() const; 
	int getTimeOfLastFloor() const;
	ElevatorType getType() const;

	void UpdateState( const int & timestep, int Floor , const int &maxFloor, bool load);
	int getCapacity() const; 
	int getNumberOfRiders() const;

	PickablePtr peekTopUser() const;
	bool loading(ElevatorState state);
	bool unload();

	bool Rec_V(PickablePtr temp);


	~Elevator();

};


