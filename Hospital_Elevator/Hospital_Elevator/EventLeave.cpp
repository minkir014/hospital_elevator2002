#include "EventLeave.h"
#include "Hospital.h"

bool EventLeave::execute(Hospital* hos) {
	hos->getFloor(0)->getPickable(ID);
}