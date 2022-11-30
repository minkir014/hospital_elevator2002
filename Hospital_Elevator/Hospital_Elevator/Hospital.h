#pragma once
#include "Elevator.h"
#include "Floor.h"
#include "Event.h"
#include "PickablePtr.h"
#include "ArrayBag.h"
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

	LinkedBag<Floor>* Floors;
	LinkedQueue<Event*> Events;

	ArrayBag<PickablePtr>* Stairs;// To be changed to LL Bag
	
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


};