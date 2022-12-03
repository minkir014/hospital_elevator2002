#include "Hospital.h"
#include <string>
#include "UI.h"
#include "EventLeave.h"
#include "EventStair.h"
#include <iostream>
#include <iomanip>
using namespace std;


Hospital::Hospital() : TimeStep(0), numOfAutoS(0), numOfLeaveEvents(0) {}

Hospital::~Hospital() { int a = 0; }

void Hospital::IncrementTimeStep() {
	TimeStep++;
}

int Hospital::getTimeStep() const { return TimeStep; }

Floor* Hospital::getFloor(int number) const { return Floors[number]; }
int Hospital::getFloorCount() const { return numOfFloors; }
int Hospital::getS() const { return S; }

void Hospital::countLeave() { numOfLeaveEvents++; }

void Hospital::ExecuteEvents() {
	TimeStep = 1;
	Event* ev = nullptr;
	Events.Peek(ev);

	while (true) {

		if (ev != nullptr && TimeStep == ev->getEventTime()) {
			Events.Dequeue(ev);
			ev->execute(this);
		}

		Simulate();

		if (!Events.Peek(ev))
			ev = nullptr;

		if (ev == nullptr || ev->getEventTime() != TimeStep) {
			OutputToScreen();
			TimeStep++;
		}

		bool a = true;

		if (Events.isEmpty() && Stairs.IsEmpty()) {
			for (int i = 0; i < numOfFloors; i++)
				if (Floors[i]->isWaitingUp() && Floors[i]->isWaitingDown()) {
					a = false;
					break;
				}
			if (a)
				break;
		}

	}
}

bool Hospital::stairPickable(PickablePtr& obj) {
	obj.setStairs();
	Stairs.Insert(obj);

	return true;
}

void Hospital::Simulate() {
	int TargetFloor = 0;
	bool load = false;

	PickablePtr ptr(0);
	for (int i = 0; i < numOfFloors; i++) {

		if (TimeStep % 5 == 0) {
			if (Floors[i]->DequeueUp(ptr)) {
				ptr.setCompleted();
				Finished.Enqueue(ptr);
			}

			if (Floors[i]->DequeueDown(ptr)) {
				ptr.setCompleted();
				Finished.Enqueue(ptr);
			}
		}


		while (TimeStep - Floors[i]->getFirstVisitor().getPickablePtr()->getArrivalTime() == AutoS) {
			if (Floors[i]->getFirstVisitor() == 0) break;
			ptr = Floors[i]->getFirstVisitor();
			if (Floors[i]->DeletePickable(ptr)) {
				ptr.setStairs();
				Stairs.Insert(ptr);
				numOfAutoS++;
			}
		}

	}

	ptr = Stairs.peekTop();
	while (!(ptr == 0)) {
		if (ptr.getPickablePtr()->getPriority() * (-1) == TimeStep) {
			Stairs.Delete(ptr);
			ptr.setCompleted();
			Finished.Enqueue(ptr);
			ptr = Stairs.peekTop();
			continue;
		}
		break;
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
		if (EventType == 'A') {
			InputFile >> PickableType >> timestep >> id >> srcFloor >> targetFloor;
			if (PickableType == 'P') {
				InputFile >> emergency;
				ev = new EventArrival(Arrival, id, emergency, timestep, P, srcFloor, targetFloor);
			}
			else if (PickableType == 'V')
				ev = new EventArrival(Arrival, id, 1, timestep, V, srcFloor, targetFloor);
			else
				ev = new EventArrival(Arrival, id, 1, timestep, C, srcFloor, targetFloor);

		}
		else if (EventType == 'L') {
			InputFile >> timestep >> id;
			ev = new EventLeave(leave, timestep, id);
		}
		else {
			InputFile >> timestep >> id;
			ev = new EventStair(Stair, timestep, id);
		}

		Events.Enqueue(ev);
	}

}
void Hospital::OutputToScreen() {
	if (TimeStep == 1)
		InterfaceController.PrintHeader();

	if (InterfaceController.GetAppMode() != Silent) {
		InterfaceController.PrintTimeStep(TimeStep);
		// PrintWaiting Patients/Cargos/Visitor;
		// LFloors.

		int Waiting = 0; int VisitorsWaiting = 0; int inService = Stairs.getCount(); // To Be Changed in Phase 2
		int Completed = Finished.getCount();
		int numOfStairs = Stairs.getCount();

		for (int i = numOfFloors - 1; i >= 0; i--)
		{
			Floor* CurrentFloor = Floors[i];
			const int UpCount = CurrentFloor->GetUpHeapSize();
			const int DownCount = CurrentFloor->GetdownHeapSize();
			int* Vup = new int[UpCount];
			int* Pup = new int[UpCount];
			int* Cup = new int[UpCount];
			int* Vdown = new int[DownCount];
			int* Pdown = new int[DownCount];
			int* Cdown = new int[DownCount];
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

			Waiting += Vdownsize + Cdownsize + Pdownsize + Vupsize + Cupsize + Pupsize;
			VisitorsWaiting += Vdownsize + Vupsize;

			delete[] Vup; delete[] Pup; delete[] Cup; delete[] Vdown; delete[] Pdown; delete[] Cdown;

		}

		InterfaceController.PrintFinalStats(Waiting, numOfLeaveEvents, inService, numOfStairs, Completed);

		if (InterfaceController.GetAppMode() == StepByStep)
			InterfaceController.WaitOneSecond();
	}
}


void Hospital::OutputToFile() {
	int WaitingTime = 0, ServiceTime = 0, PCount = 0, VCount = 0, CCount = 0;
	int TT, ID, AT, WT, ST;

	PickablePtr ptr(0);
	Pickable* PPtr = nullptr;

	OutputFile.open(InterfaceController.getOutputFileName(), ios::out);
	OutputFile << "TT\tID\tAT\tWT\tST\n";

	while (!Finished.isEmpty()) {
		Finished.Dequeue(ptr);
		PPtr = ptr.getPickablePtr();
		TT = PPtr->getTargetTime();
		AT = PPtr->getArrivalTime();
		ID = PPtr->getID();
		if (PPtr->getServiceTime()) {
			ST = PPtr->getServiceTime();
			WT = TT - ST - AT;
		}
		else {
			ST = 0;
			WT = TT - AT;
		}

		OutputFile << TT << "\t" << ID << "\t" << AT << "\t" << WT << "\t" << ST << "\n";
		WaitingTime += WT; ServiceTime += ST;
		if (PPtr->getType() == P) PCount++;
		else if (PPtr->getType() == V) VCount++;
		else CCount++;
	}


	OutputFile << "***********************************\n";
	OutputFile << "***********************************\n";

	OutputFile << "Passengers: " << PCount + VCount << "\t[V: " << VCount << ", P: " << PCount << "]\n";
	OutputFile << "Cargos: " << CCount << "\n";

	OutputFile << "Avg Wait = " << fixed << setprecision(2) << (double)WaitingTime / (PCount + VCount + CCount) << "\n";
	OutputFile << "Avg Serv = " << fixed << setprecision(2) << (double)ServiceTime / (PCount + VCount + CCount) << "\n";

	OutputFile << "AutoS: " << fixed << setprecision(2) << (double)numOfAutoS / VCount * 100 << "%\n";

	InterfaceController.printFooter();

}
