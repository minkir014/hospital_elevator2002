#include "PickablePtr.h"
#include "Hospital.h"
#include <math.h>

PickablePtr::PickablePtr(Pickable* ptr, const Hospital* hos, bool tmp, bool stair) { 
	this->ptr = ptr; temp = false; this->hos = hos; stairs = stair; completed = false; inService = false;
}

PickablePtr::PickablePtr(const PickablePtr& obj) { 
	ptr = obj.ptr; hos = obj.hos; temp = false; stairs = obj.stairs; completed = false; inService = obj.inService; ele = obj.ele;
}

PickablePtr::PickablePtr(int tempID) { 
	ptr = new Pickable(tempID, 0, 0); temp = true; stairs = false; completed = false; inService = false;
}

PickablePtr& PickablePtr::operator=(const PickablePtr& obj) {
	if (temp)
		delete ptr;
	ptr = new Pickable(*obj.getPickablePtr());
	//delete obj.ptr;  /// Problematic ..............................................

	temp = false;
	hos = obj.hos;

	ele = obj.ele;

	inService = obj.inService;
	stairs = obj.stairs;
	completed = obj.completed;

	return *this;
}

PickablePtr::~PickablePtr() { 
	//if (temp) destroyPickable();
}

void PickablePtr::setPickablePtr(Pickable* ptr) { this->ptr = ptr; }

Pickable* PickablePtr::getPickablePtr() const { return ptr; }

bool PickablePtr::destroyPickable() { delete ptr; return true; }

bool PickablePtr::operator==(const PickablePtr obj) {
	if (ptr->getID() == obj.getPickablePtr()->getID())
		return true;

	return false;
}

bool PickablePtr::operator<(PickablePtr obj) {
	setPriority();
	obj.setPriority();
	if (ptr->getPriority() < obj.getPickablePtr()->getPriority())
		return true;
	return false;
}

bool PickablePtr::operator<=(PickablePtr obj) {
	setPriority();
	obj.setPriority();
	if (ptr->getPriority() <= obj.getPickablePtr()->getPriority())
		return true;
	return false;
}

bool PickablePtr::operator>(PickablePtr obj) {
	setPriority();
	obj.setPriority();
	if (ptr->getPriority() > obj.getPickablePtr()->getPriority())
		return true;
	return false;
}

bool PickablePtr::operator>=(PickablePtr obj) {
	setPriority();
	obj.setPriority();
	if (ptr->getPriority() >= obj.getPickablePtr()->getPriority())
		return true;
	return false;
}

bool PickablePtr::setStairs() {
	stairs = true;
	int priority = abs(ptr->getTrgfloor() - ptr->getSrcfloor()) * (-1) * hos->getS() - hos->getTimeStep();
	ptr->resetPriority(priority, stairs);
	ptr->setServiceTime(abs(ptr->getTrgfloor() - ptr->getSrcfloor()) * hos->getS());
	return true;
}

bool PickablePtr::setCompleted() {
	if (inService)
		ptr->setServiceTime(hos->getTimeStep() - ptr->getServiceTime());

	stairs = false;
	inService = false;
	completed = true;
	ptr->setTargetTime(hos->getTimeStep());
	return true;
}

bool PickablePtr::setInService(Elevator* e) {
	inService = true;
	ele = e;
	int priority = abs(ptr->getTrgfloor() - e->getCurrentFloor()) * -1;
	ptr->resetPriority(priority, true);
	ptr->setServiceTime(hos->getTimeStep());
	return true;
}

void PickablePtr::setPriority() {
	if (!(*this == 0))
		if (!stairs && !completed && !inService)
			ptr->resetPriority(hos->getTimeStep(), stairs);
		else if (completed)
			ptr->resetPriority(ptr->getTargetTime(), completed);
		else if (inService)
			ptr->resetPriority(abs(ptr->getTrgfloor() - ele -> getCurrentFloor()) * -1, true);
}