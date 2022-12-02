#include "PickablePtr.h"
#include "Hospital.h"
#include <math.h>

PickablePtr::PickablePtr(Pickable* ptr, const Hospital* hos, bool tmp, bool stair) { 
	this->ptr = ptr; temp = tmp; this->hos = hos; stairs = stair; completed = false;
}

PickablePtr::PickablePtr(const PickablePtr& obj) { 
	ptr = obj.ptr; hos = obj.hos; temp = false; stairs = obj.stairs; completed = false;
}

PickablePtr::PickablePtr(int tempID) { 
	ptr = new Pickable(tempID, 0, 0); temp = true; stairs = false; completed = false;
}

PickablePtr& PickablePtr::operator=(const PickablePtr& obj) {
	if (temp)
		delete ptr;
	ptr = new Pickable(*obj.getPickablePtr());
	temp = false;
	hos = obj.hos;

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
	return true;
}

bool PickablePtr::setCompleted() {
	stairs = false;
	completed = true;
	ptr->setTargetTime(hos->getTimeStep());
	return true;
}

void PickablePtr::setPriority() {
	if (!stairs && !completed)
		ptr->resetPriority(hos->getTimeStep(), stairs);
	else if (stairs)
		ptr->resetPriority(abs(ptr->getTrgfloor() - ptr->getSrcfloor()), stairs);
	else
		ptr->resetPriority(ptr->getTargetTime(), completed);
}