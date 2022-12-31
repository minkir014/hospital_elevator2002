#include "Hospital.h"
#include <string>
#include "UI.h"
#include "EventLeave.h"
#include "EventStair.h"
#include <iostream>
#include <iomanip>
using namespace std;


Hospital::Hospital() : TimeStep(0), numOfAutoS(0), numOfLeaveEvents(0), PatientElevator(ArrayOfElevators[0]),
VisitorElevator(ArrayOfElevators[1]), CargoElevator(ArrayOfElevators[2]), RecursionActivated(0) {}

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

		while (ev != nullptr && TimeStep == ev->getEventTime()) {
			if (!Events.Dequeue(ev)) break;
			ev->execute(this);
			Events.Peek(ev);
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


int Hospital::getNearestMove(int currentFloor, ElevatorState previous) {
	int pending = 0;

	int i = 1;
	while (i < numOfFloors) {

		if (currentFloor + i < numOfFloors && Floors[currentFloor + i]->GetUpHeapSize() + Floors[currentFloor + i]->GetdownHeapSize() > 0)
			if (previous == MovingUp)
				return i;
			else
				pending = i;

		if (currentFloor - i >= 0 && Floors[currentFloor - i]->GetUpHeapSize() + Floors[currentFloor - i]->GetdownHeapSize() > 0)
			return -i;

		if (pending != 0) return pending;

		i++;

	}

	return 0;

}




void Hospital::moveElevators(int start) {
	ElevatorType type;
	for (int i = start; i < 3; i++) {
		if (i > 0 && RecursionActivated) break;

		if (i == 0) type = PE;
		else if (i == 1) type = VE;
		else type = CE;

		if (ArrayOfElevators[i]->getState() == AVAIL) {
			PickablePtr topPriority = Floors[ArrayOfElevators[i]->getCurrentFloor()]->peekTopPriority(type, -1); // P is a random case as the elevator is empty.
			if (topPriority == 0) {
				int nearestFloor = getNearestMove(ArrayOfElevators[i]->getCurrentFloor(), ArrayOfElevators[i]->getPreviousState());
				ArrayOfElevators[i]->UpdateState(TimeStep, ArrayOfElevators[i]->getCurrentFloor() + nearestFloor, numOfFloors, 0);
			}
			else
				ArrayOfElevators[i]->UpdateState(TimeStep, topPriority.getPickablePtr()->getTrgfloor(), numOfFloors, 1);

		}
		else if (ArrayOfElevators[i]->getState() == MovingUp || ArrayOfElevators[i]->getState() == MovingDown) {

			if ((TimeStep - ArrayOfElevators[i]->getTimeOfLastFloor()) % ArrayOfElevators[i]->getSpeed() == 0) {

				if ((Floors[ArrayOfElevators[i]->getCurrentFloor() + 1]->GetUpHeapSize() > 0 &&
					ArrayOfElevators[i]->getState() == MovingUp) ||
					(Floors[ArrayOfElevators[i]->getCurrentFloor() - 1]->GetdownHeapSize() > 0 &&
						ArrayOfElevators[i]->getState() == MovingDown)) {

					if (ArrayOfElevators[i]->getNumberOfRiders() < ArrayOfElevators[i]->getCapacity())

						ArrayOfElevators[i]->UpdateState(TimeStep, ArrayOfElevators[i]->getCurrentFloor() + 
							ArrayOfElevators[i]->getState() == MovingUp ? 1 : -1, numOfFloors, 1);
					else
						ArrayOfElevators[i]->UpdateState(TimeStep, ArrayOfElevators[i]->getTargetFloor(), numOfFloors, 0);
				}
				else {
					ArrayOfElevators[i]->UpdateState(TimeStep, ArrayOfElevators[i]->getTargetFloor(), numOfFloors, 0);
				}
			}
		}

		else if (ArrayOfElevators[i]->getState() == Unload) {

			if ((Floors[ArrayOfElevators[i]->getCurrentFloor()]->GetUpHeapSize() > 0 &&
				ArrayOfElevators[i]->getPreviousState() == MovingUp) ||
				(Floors[ArrayOfElevators[i]->getCurrentFloor()]->GetdownHeapSize() > 0 &&
					ArrayOfElevators[i]->getPreviousState() == MovingDown)) {

				ArrayOfElevators[i]->UpdateState(TimeStep, ArrayOfElevators[i]->getCurrentFloor() + 
					ArrayOfElevators[i]->getPreviousState() == MovingUp ? 1 : -1, numOfFloors, 1);
			}
			else
				if (ArrayOfElevators[i]->getNumberOfRiders() == 0) {
					ArrayOfElevators[i]->UpdateState(TimeStep, ArrayOfElevators[i]->getCurrentFloor(), numOfFloors, 0); // Nearest Floor. Change Direections
					i--;
				}
				else
					ArrayOfElevators[i]->UpdateState(TimeStep, ArrayOfElevators[i]->getCurrentFloor()
						+ ArrayOfElevators[i]->getPreviousState() == MovingUp ? 1 : -1, numOfFloors, 0); // Nearest Floor. Change Direections
		}

		else if (ArrayOfElevators[i]->getState() == Load) {

			if ((Floors[ArrayOfElevators[i]->getCurrentFloor()]->GetUpHeapSize() > 0 &&
				(ArrayOfElevators[i]->getPreviousState() == MovingUp) || ArrayOfElevators[i]->getTargetFloor() - 
				ArrayOfElevators[i]->getCurrentFloor() > 0) ||

				(Floors[ArrayOfElevators[i]->getCurrentFloor()]->GetdownHeapSize() > 0 &&
					(ArrayOfElevators[i]->getPreviousState() == MovingDown) || ArrayOfElevators[i]->getTargetFloor() - 
					ArrayOfElevators[i]->getCurrentFloor() < 0)) {

				if (ArrayOfElevators[i]->getNumberOfRiders() < ArrayOfElevators[i]->getCapacity())
					ArrayOfElevators[i]->UpdateState(TimeStep, ArrayOfElevators[i]->getCurrentFloor(), numOfFloors, 1);

				else
					ArrayOfElevators[i]->UpdateState(TimeStep, ArrayOfElevators[i]->getCurrentFloor(), numOfFloors, 0);
			}
			
			else
				ArrayOfElevators[i]->UpdateState(TimeStep, ArrayOfElevators[i]->getCurrentFloor(), numOfFloors, 0);
		}

		else if (ArrayOfElevators[i]->getState() == IDLE) {
			if (ArrayOfElevators[i]->getTimeOfLastFloor() - TimeStep == 3) {
				if ((Floors[ArrayOfElevators[i]->getCurrentFloor()]->GetUpHeapSize() > 0 &&
					ArrayOfElevators[i]->getPreviousState() == MovingUp)) {

					PickablePtr temp = Floors[ArrayOfElevators[i]->getCurrentFloor()]->peekTopPriorityDown(type, -1);
					if (temp == 0)
						ArrayOfElevators[i]->UpdateState(TimeStep, ArrayOfElevators[i]->getTargetFloor(), numOfFloors, 0);
					else
						ArrayOfElevators[i]->UpdateState(TimeStep, ArrayOfElevators[i]->getCurrentFloor(), numOfFloors, 1);


				}
				else if ((Floors[ArrayOfElevators[i]->getCurrentFloor()]->GetdownHeapSize() > 0 &&
					ArrayOfElevators[i]->getPreviousState() == MovingDown))
				{

					PickablePtr temp = Floors[ArrayOfElevators[i]->getCurrentFloor()]->peekTopPriorityUp(type, -1);
					if (temp == 0)
						ArrayOfElevators[i]->UpdateState(TimeStep, ArrayOfElevators[i]->getTargetFloor(), numOfFloors, 0);
					else
						ArrayOfElevators[i]->UpdateState(TimeStep, ArrayOfElevators[i]->getCurrentFloor(), numOfFloors, 1);
				}

				else if (ArrayOfElevators[i]->getPreviousState() == AVAIL) {
					ArrayOfElevators[i]->UpdateState(TimeStep, ArrayOfElevators[i]->getCurrentFloor(), numOfFloors, 0);
					i--;
				}
			}
		}

	}

}

void Hospital::setRecursion(bool activated) {
	RecursionActivated = activated;
}

bool Hospital::getRecursion() const {
	return RecursionActivated;
}

void Hospital::Simulate() {
	int TargetFloor = 0;
	bool load = false;

	moveElevators(0);
	RecursionActivated = false;

	PickablePtr ptr(0);
	for (int i = 0; i < numOfFloors; i++) {

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

bool Hospital::finishedPickable(PickablePtr& obj) {
	obj.setCompleted();
	Finished.Enqueue(obj);
	return true;
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

	PatientElevator = new Elevator(P_Speed, P_Cap, this, PE);
	VisitorElevator = new Elevator(V_Speed, V_Cap, this, VE);
	CargoElevator = new Elevator(C_Speed, C_Cap, this, CE);

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

		int E[3] = { -1, -1, -1 };

		for (int i = 0; i < 3; i++)
			if (ArrayOfElevators[i]->getState() != MovingDown && ArrayOfElevators[i]->getState() != MovingUp)
				E[i] = ArrayOfElevators[i]->getCurrentFloor();
		

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

			InterfaceController.PrintElevatorHeader();

			int j = 0;
			for (;j < 3; j++)
				if (E[j] == i) {
					InterfaceController.PrintElevator(ArrayOfElevators[j]);
				}
				else break;

			if (j == 0) InterfaceController.PrintElevator(nullptr);

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
