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

	Elevator* PatientElevator;
	Elevator* VisitorElevator;
	Elevator* CargoElevator;

	Floor** Floors;
	int numOfFloors;
	LinkedQueue<Event*> Events;
	
	LinkedBag<PickablePtr> Stairs;
	LinkedQueue<PickablePtr> Finished;

	int TimeStep;
	int S;
	int AutoS;

	fstream InputFile;
	fstream OutputFile;
		
	void IncrementTimeStep();
	void ExecuteEvent();
	void OutputToScreen();
public:
	Hospital();
	~Hospital();

	void OutputToFile();
	void InitializeLists();

	void ExecuteEvents();

	int getTimeStep() const;


};