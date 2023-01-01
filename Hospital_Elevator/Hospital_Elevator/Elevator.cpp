#include "ArrayBag.h"
#include "Elevator.h"
#include "Pickable.h"
#include <string>
#include "Defs.h"
#include "Hospital.h"
using namespace std;

Elevator::Elevator(int CSpeed, int CCapacity, Hospital* hos, ElevatorType type)
{
	CurrentFloor = 0;
	TargetFloor = 0;
	Speed = CSpeed;
	Capacity = CCapacity;
	state = AVAIL;
	LastState = AVAIL;
	this->hos = hos;
	this->type = type;
}


void Elevator::incrementFloor() { CurrentFloor++; }
void Elevator::decrementFloor() { CurrentFloor--; }
ElevatorState Elevator::getState() const { return state; }
ElevatorState Elevator::getPreviousState() const { return LastState; }
int Elevator::getCurrentFloor() const { return CurrentFloor; }
int Elevator::getTargetFloor()	const { return TargetFloor; }
int Elevator::getSpeed() const { return Speed; }
int Elevator::getTimeOfLastFloor() const { return timeOfLastFloor; }
int Elevator::getCapacity() const { return Capacity; }
int Elevator::getNumberOfRiders() const { return Elevatorhead.getCount(); }
ElevatorType Elevator::getType() const { return type; }

void Elevator::UpdateState(const int& timestep, int Floor, const int& maxFloor, bool load) {

	if ((state == Load || state == Unload) && timestep - timeOfLastFloor > 0)
		if (Elevatorhead.peekTop() == 0) // Load passes this condition. Unload has a problem. Its last state must be Up or Down.
			if (load)
				Floor = CurrentFloor + (LastState == MovingDown) ? -1 : 1;
			else Floor = CurrentFloor;

		else Floor = Elevatorhead.peekTop().getPickablePtr()->getTrgfloor();

	TargetFloor = Floor;


	if (state == MovingDown) {
		if ((timestep - timeOfLastFloor) % Speed == 0) {
			decrementFloor();
			timeOfLastFloor = timestep;
			if (CurrentFloor == 0) {
				if (Elevatorhead.IsEmpty()) {
					state = IDLE;
				}
				else {
					if (Elevatorhead.peekTop().getPickablePtr()->getTrgfloor() == Floor) {
						state = Unload;
						unload();  // call unload here and give TimeStep + 1
					}

					else {
						state = Load;
						loading(MovingDown);
					}
				}
			}
			else if (CurrentFloor == Floor) {
				if (Elevatorhead.IsEmpty()) {
					state = AVAIL;
				}
				else {
					if (Elevatorhead.peekTop().getPickablePtr()->getTrgfloor() == Floor) {
						state = Unload;
						unload();
					}

					else {
						state = Load;
						loading(MovingDown);
					}
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
				if (Elevatorhead.IsEmpty()) {
					state = IDLE;
				}
				else {
					if (Elevatorhead.peekTop().getPickablePtr()->getTrgfloor() == Floor) {
						state = Unload;
						unload();
					}

					else {
						state = Load;
						loading(MovingUp);
					}
				}
			}
			else if (CurrentFloor == Floor) {
				if (Elevatorhead.IsEmpty()) {
					state = AVAIL;
				}
				else {
					if (Elevatorhead.peekTop().getPickablePtr()->getTrgfloor() == Floor) {
						state = Unload;
						unload();
					}

					else {
						state = Load;
						loading(MovingUp);
					}
				}
			}
			LastState = MovingUp;
		}

	}
	if (state == IDLE && (timestep - timeOfLastFloor) == 3) {
		if (load) {
			state = Load;
			if (LastState == MovingDown)
				loading(MovingUp);
			else if (LastState == MovingUp)
				loading(MovingDown);

			else
				loading(LastState);
		}
		else if (Floor - CurrentFloor > 0)
			state = MovingUp;
		else if (Floor - CurrentFloor < 0)
			state = MovingDown;
		else
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
				if (load) {
					state = Load;
					loading(MovingUp);
				}
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
				if (load) {
					state = Load;
					loading(MovingDown);
				}
				else
					state = MovingDown;
				timeOfLastFloor = timestep;
			}
			LastState = AVAIL;
		}
	}

	if (state == Load && timestep - timeOfLastFloor > 0) {
		if (!load) {
			if (Floor - CurrentFloor > 0)
				state = MovingUp;
			else
				state = MovingDown;

			LastState = Load;
		}
		else {
			loading(Floor - CurrentFloor > 0 ? MovingUp : MovingDown);
		}
		timeOfLastFloor = timestep;
	}

	if (state == Unload && timestep - timeOfLastFloor > 0) {

		if (LastState == MovingDown) {
			if ((Floor - CurrentFloor) > 0) {
				state = IDLE;
			}
			else if ((Floor - CurrentFloor) < 0) {
				if (load) {
					state = Load;
					loading(MovingDown);
				}
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
				if (load) {
					state = Load;
					loading(MovingUp);
				}
				else
					state = MovingUp;
			}
			else {
				state = AVAIL;
			}
		}
		timeOfLastFloor = timestep;
	}
	/* In bonus
	if(state == OUT) {
	//	timeOfLastFloor =
	}
	*/
}

bool Elevator::loading(ElevatorState stateOfImportance) {
	PickablePtr loaded(1);

	bool isItloaded = false;

	while (!(loaded == 0) && getNumberOfRiders() < Capacity) {
		loaded = 0;

		if (stateOfImportance == MovingUp) {
			if (!Elevatorhead.IsEmpty()) {
				PickablePtr temp = hos->getFloor(CurrentFloor)->peekTopPriorityUp(type, Elevatorhead.peekTop().getPickablePtr()->getType()); // may cause null exception error
				if (!(temp == 0))
					if (Rec_V(temp)) {
						loaded = 1;
						continue;
					}
					else
						hos->getFloor(CurrentFloor)->DequeueUp(loaded);
			}
			else {
				PickablePtr temp = hos->getFloor(CurrentFloor)->peekTopPriorityUp(type, -1);
				if (!(temp == 0)) {
					if (Rec_V(temp)) {
						loaded = 1;
						continue;
					}
					else
						hos->getFloor(CurrentFloor)->DequeueUp(loaded);
				}
			}
		}

		if (stateOfImportance == MovingDown) {
			if (!Elevatorhead.IsEmpty()) {
				PickablePtr temp = hos->getFloor(CurrentFloor)->peekTopPriorityDown(type, Elevatorhead.peekTop().getPickablePtr()->getType()); // may cause null exception error
				if (!(temp == 0))
					if (Rec_V(temp)) {
						loaded = 1;
						continue;
					}
					else
						hos->getFloor(CurrentFloor)->DequeueDown(loaded);
			}
			else {
				PickablePtr temp = hos->getFloor(CurrentFloor)->peekTopPriorityDown(type, -1);
				if (!(temp == 0)) {
					if (Rec_V(temp)) {
						loaded = 1;
						continue;
					}
					else
						hos->getFloor(CurrentFloor)->DequeueDown(loaded);
				}
			}
		}

		if (stateOfImportance == AVAIL) {
			if (!Elevatorhead.IsEmpty()) {
				PickablePtr temp = hos->getFloor(CurrentFloor)->peekTopPriority(type, Elevatorhead.peekTop().getPickablePtr()->getType()); // may cause null exception error
				if (!(temp == 0))
					if (Rec_V(temp)) {
						loaded = 1;
						continue;
					}
					else
						if (temp.getPickablePtr()->getTrgfloor() > CurrentFloor)
							hos->getFloor(CurrentFloor)->DequeueUp(loaded);

						else hos->getFloor(CurrentFloor)->DequeueDown(loaded);
			}
			else {
				PickablePtr temp = hos->getFloor(CurrentFloor)->peekTopPriority(type, -1);
				if (!(temp == 0)) {
					if (Rec_V(temp)) {
						loaded = 1;
						continue;
					}
					else
						if (temp.getPickablePtr()->getTrgfloor() > CurrentFloor)
							hos->getFloor(CurrentFloor)->DequeueUp(loaded);

						else hos->getFloor(CurrentFloor)->DequeueDown(loaded);
				}
			}
		}

		if (!(loaded == 0)) {
			loaded.setInService(this);
			Elevatorhead.Insert(loaded);
			isItloaded = true;
		}

	}

	return isItloaded;


}

bool Elevator::unload() {

	bool isItUnloaded = false;
	PickablePtr unloaded(1);

	while (!(unloaded == 0) && getNumberOfRiders() != 0 && Elevatorhead.peekTop().getPickablePtr()->getTrgfloor() == CurrentFloor) {
		unloaded = 0;
		Elevatorhead.Delete(unloaded);

		if (!(unloaded == 0)) {
			hos->finishedPickable(unloaded);
			isItUnloaded = true;
		}

	}

	return isItUnloaded;
}


PickablePtr Elevator::peekTopUser() const {
	return Elevatorhead.peekTop();
}

bool Elevator::Rec_V(PickablePtr temp) {
	if (temp.getPickablePtr()->getType() == V && type == PE && !hos->getRecursion()) {
		hos->moveElevators(1);
		hos->setRecursion(1);
		return true;
	}
	return false;
}

// Loading TimeStep

Elevator::~Elevator()
{
}