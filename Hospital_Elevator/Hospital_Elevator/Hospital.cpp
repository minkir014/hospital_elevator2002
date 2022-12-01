#include "Hospital.h"
#include <string>
#include "UI.h"

Hospital::Hospital() : TimeStep(0) {}

Hospital::~Hospital() {}

void Hospital::IncrementTimeStep() {
	TimeStep++;
}

int Hospital::getTimeStep() const {	return TimeStep; }

void Hospital::InitializeLists() {
	InputFile.open(InterfaceController.getInputFileName(), ios::in);
	int noOfFloors;
	InputFile >> noOfFloors;
	Floors = new ArrayBag<Floor*>(noOfFloors);

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
	int* Vup, Vdown, Cup, Cdown, Pup, Pdown;
	int Vupsize = 0;
	int Vdownsize = 0;
	int Cupsize = 0;  
	int Cdownsize = 0; 
	int Pupsize = 0;
	int Pdownsize = 0; 
	// PrintWaiting Patients/Cargos/Visitor;
	// LFloors.



	


}	

