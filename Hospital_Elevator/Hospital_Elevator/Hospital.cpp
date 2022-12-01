#include "Hospital.h"
#include <string>
#include "UI.h"

Hospital::Hospital() : TimeStep(0) {}

Hospital::~Hospital() {}

void Hospital::IncrementTimeStep() {
	TimeStep++;
}

int Hospital::getTimeStep() const { return TimeStep; }

void Hospital::ExecuteEvents() {
	TimeStep = 1;
	Event* ev = nullptr;
	while (true) {
		Events.Peek(ev);

		if (TimeStep == ev->getEventTime()) {
			Events.Dequeue(ev);
			ev->execute(this);
		}

		OutputToScreen();
		bool a = true;

		if (Events.isEmpty() && Stairs.isEmpty()) {
			for (int i = 0; i < numOfFloors; i++)
				if (Floors[i]->isWaiting()) {
					a = false;
					break;
				}
			if (a)
				break;
		}
		TimeStep++;
	}
}


void Hospital::InitializeLists() {
	InputFile.open(InterfaceController.getInputFileName(), ios::in);
	int noOfFloors;
	InputFile >> noOfFloors;
	Floors = new Floor * [noOfFloors];
	numOfFloors = noOfFloors;

	for (int i = 0; i < noOfFloors; i++)
		Floors[i] = new Floor(i);

	int V_Speed, C_Speed, P_Speed;
	InputFile >> V_Speed >> C_Speed >> P_Speed;

	int V_Cap, C_Cap, P_Cap;
	InputFile >> V_Cap >> C_Cap >> P_Cap;

	PatientElevator = new Elevator(P_Speed, P_Cap);
	VisitorElevator = new Elevator(V_Speed, V_Cap);
	CargoElevator = new Elevator(C_Speed, C_Cap);

	InputFile >> S;
	InputFile >> AutoS;

	InputFile >> noOfFloors;

	char EventType, PickableType; int timestep, id, srcFloor, targetFloor, emergency;
	Event* ev = nullptr;

	while (InputFile >> EventType) {
		InputFile >> PickableType >> timestep >> id >> srcFloor >> targetFloor;

		if (EventType == 'A') {
			if (PickableType == 'P') {
				InputFile >> emergency;
				ev = new EventArrival(Arrival, id, emergency, timestep, P, srcFloor, targetFloor);
			}
			else if (PickableType == 'V')
				ev = new EventArrival(Arrival, id, 0, timestep, V, srcFloor, targetFloor);
			else
				ev = new EventArrival(Arrival, id, -1, timestep, C, srcFloor, targetFloor);

		}
		else if (EventType == 'L') {
			ev = new Event(leave, timestep, id);
		}
		else {
			ev = new Event(Stair, timestep, id);
		}

		Events.Enqueue(ev);
	}

}
void Hospital::OutputToScreen() {
	cout << "Current Timestep :" << TimeStep << endl;
	// PrintWaiting Patients/Cargos/Visitor;
	// LFloors.
	for (int i = 0; i < numOfFloors; i++)
	{
		Floor* CurrentFloor = Floors[i]; 
		const int UpCount = CurrentFloor->GetUpHeapSize();
		const int DownCount = CurrentFloor->GetdownHeapSize();
		int * Vup = new int[UpCount];
		int * Pup = new int[UpCount];
		int * Cup = new int[UpCount];
		int * Vdown = new int[DownCount];
		int * Pdown = new int[DownCount];
		int * Cdown = new int[DownCount];
		int Vupsize = 0;
		int Vdownsize = 0;
		int Cupsize = 0;
		int Cdownsize = 0;
		int Pupsize = 0;
		int Pdownsize = 0;
		CurrentFloor->TraversePickables(Vup, Vdown, Cup, Cdown, Pup, Pdown, Vupsize, Vdownsize, Cupsize, Cdownsize, Pupsize, Pdownsize); 
		InterfaceController.PrintWaitingPatients(Pupsize, Pup, Pdownsize, Pdown);
		InterfaceController.PrintWaitingCargos(Cupsize, Cup, Cdownsize, Cdown);
		InterfaceController.PrintWaitingVisitors(Vupsize, Vup, Vdownsize, Vdown);
		//InterfaceController.PrintElevator()
		int s = i + 1; 
		InterfaceController.PrintFloor(s);

	}
	




}

