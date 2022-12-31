#pragma once
#include "Elevator.h"
#include "Floor.h"
#include "Event.h"
#include "PickablePtr.h"
#include "ArrayBag.h"
#include "LinkedBag.h"
#include "LinkedQueue.h"
#include "UI.h"
#include "EventArrival.h"
#include "Defs.h"
#include <fstream>
#include"LinkedBag.h"


class Hospital {
private:
	UI InterfaceController;

	Elevator* ArrayOfElevators[3];
	Elevator*& PatientElevator;
	Elevator*& VisitorElevator;
	Elevator*& CargoElevator;

	Floor** Floors ;
	int numOfFloors;
	LinkedQueue<Event*> Events;
	
	LinkedHeap<PickablePtr> Stairs;
	LinkedQueue<PickablePtr> Finished;

	int TimeStep;
	int S;
	int AutoS;

	int numOfAutoS;
	int numOfLeaveEvents;

	fstream InputFile;
	fstream OutputFile;

	bool RecursionActivated;
		
	void IncrementTimeStep();
	void Simulate();
	void OutputToScreen();

	int getNearestMove(int currentFloor, ElevatorState previous);

public:
	Hospital();
	~Hospital();

	Floor* getFloor(int number) const;
	int getFloorCount() const;
	int getS() const;

	void countLeave();

	void OutputToFile();
	void InitializeLists();

	void ExecuteEvents();
	bool stairPickable(PickablePtr& obj);
	bool finishedPickable(PickablePtr& obj);

	int getTimeStep() const;

	void setRecursion(bool activated);
	bool getRecursion() const;
	void moveElevators(int start);
};