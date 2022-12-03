#include "ArrayBag.h"
#include "Elevator.h"
#include "Pickable.h"
#include <string>
#include "Defs.h"
using namespace std;

Elevator::Elevator(int CSpeed, int CCapacity) :Elevatorhead(CCapacity)
{
	CurrentFloor = 0;
	Speed = CSpeed;
	Capacity = CCapacity;
	state = AVAIL;
	LastState = AVAIL;

}


void Elevator::incrementFloor() { CurrentFloor++; }
void Elevator::decrementFloor() { CurrentFloor--; }
ElevatorState Elevator::getState() const { return state; }
int Elevator::getCurrentFloor() const { return CurrentFloor; }
int Elevator::getSpeed() const { return Speed; }
int Elevator::getTimeOfLastFloor() const { return timeOfLastFloor; }
int Elevator::getCapacity() const { return Capacity; }

void Elevator::UpdateState(int& timestep, int& Floor, int& maxFloor, bool& load) {
	if (state == MovingDown) {
		if ((timestep - timeOfLastFloor) % Speed == 0) {
			decrementFloor();
			timeOfLastFloor = timestep;
			if (CurrentFloor == 0) {
				if (Elevatorhead.isEmpty()) {
					state = IDLE;
				}
				else {
					state = Unload;
				}
			}
			else if (CurrentFloor == Floor) {
				if (Elevatorhead.isEmpty()) {
					state = AVAIL;
				}
				else {
					state = Unload;
				}
			}
			LastState = MovingDown;
		}
	}
	if (state == MovingUp) {
		if ((timestep - timeOfLastFloor) % Speed == 0) {
			incrementFloor();
			timeOfLastFloor = timestep;
			if (CurrentFloor == maxFloor) {
				if (Elevatorhead.isEmpty()) {
					state = IDLE;
				}
				else {
					state = Unload;
				}
			}
			else if (CurrentFloor == Floor) {
				if (Elevatorhead.isEmpty()) {
					state = AVAIL;
				}
				else {
					state = Unload;
				}
			}
			LastState = MovingUp;
		}

	}
	if (state == IDLE && (timestep - timeOfLastFloor) == 3) {
		state = AVAIL;
		timeOfLastFloor = timestep;
		LastState = IDLE;
	}
	if (state == AVAIL && (timestep - timeOfLastFloor) == 10) {
		state = IDLE;
		timeOfLastFloor = timestep;
		LastState = AVAIL;
	}
	if (state == AVAIL) {
		if (Floor > CurrentFloor) {
			if (LastState == MovingDown) {
				state = IDLE;
				timeOfLastFloor = timestep;
			}
			else {
				if (load)
					state = Load;
				else
					state = MovingUp;
				timeOfLastFloor = timestep;
			}
			LastState = AVAIL;
		}
		else if (Floor < CurrentFloor) {
			if (LastState == MovingUp) {
				state = IDLE;
				timeOfLastFloor = timestep; // To be Modified
			}
			else {
				if (load)
					state = Load;
				else
					state = MovingDown;
				timeOfLastFloor = timestep;
			}
			LastState = AVAIL;
		}
	}

	if (state == Load && timestep - timeOfLastFloor > 0) {
		if (Floor - CurrentFloor > 0)
			state = MovingUp;
		else
			state = MovingDown;

		LastState = Load;
		timeOfLastFloor = timestep;
	}

	if (state == Unload && timestep - timeOfLastFloor > 0) {
		if (LastState == MovingDown) {
			if ((Floor - CurrentFloor) > 0) {
				state = IDLE;
			}
			else if ((Floor - CurrentFloor) < 0) {
				if (load)
					state = Load;
				else
					state = MovingDown;
			}
			else {
				state = AVAIL;
			}
		}
		else if (LastState == MovingUp) {
			if ((Floor - CurrentFloor) < 0) {
				state = IDLE;
			}
			else if ((Floor - CurrentFloor) > 0) {
				if (load)
					state = Load;
				else
					state = MovingUp;
			}
			else {
				state = AVAIL;
			}
		}
		timeOfLastFloor = timestep;
		LastState = Unload;
	}
	/* In bonus
	if(state == OUT) {
	//	timeOfLastFloor =
	}
	*/
}

// Loading TimeStep

Elevator::~Elevator()
{
}