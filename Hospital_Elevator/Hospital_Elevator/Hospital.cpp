#include "Hospital.h"
#include <string>
#include "UI.h"

Hospital::Hospital() : TimeStep(0) {
	

}

Hospital::~Hospital() {}

void Hospital::IncrementTimeStep() {
	TimeStep++;
}

void Hospital::InitializeLists() {
	InputFile.open(InterfaceController.getInputFileName(), ios::in);
	int noOfFloors;
	InputFile >> noOfFloors;
	//Floors = new LinkedBag<Floor>();

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

	while (InputFile >> EventType) {
		if (EventType == 'A') {
			InputFile >> PickableType >> timestep >> id >> srcFloor >> targetFloor;
			//Event* arr = new EventArrival()
		}
	}

}
void Hospital::OutputToScreen() {
	cout << "Current Timestep :" << TimeStep << endl; 
	int loop = 

	// PrintWaitingPatients 
	// PrintWaitingCargos
	// PrintWaintingVisitor





}

