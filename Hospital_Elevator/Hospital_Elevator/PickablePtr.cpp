#include "PickablePtr.h"
#include "Hospital.h"

PickablePtr::PickablePtr(Pickable* ptr) { this->ptr = ptr; temp = false; }

PickablePtr::PickablePtr(int tempID) { ptr = new Pickable(tempID, 0, 0); temp = true; }

PickablePtr::~PickablePtr() { if (temp) destroyPickable(); }

void PickablePtr::setPickablePtr(Pickable* ptr) { this->ptr = ptr; }

Pickable* PickablePtr::getPickablePtr() const { return ptr; }

bool PickablePtr::destroyPickable() { delete ptr; return true; }

bool PickablePtr::operator==(const PickablePtr obj) {
	if (ptr->getID() == obj.getPickablePtr()->getID())
		return true;

	return false;
}

bool PickablePtr::operator<(PickablePtr obj) {
	if (ptr->getPriority() < obj.getPickablePtr()->getPriority())
		return true;
	return false;
}

bool PickablePtr::operator<=(PickablePtr obj) {
	if (ptr->getPriority() <= obj.getPickablePtr()->getPriority())
		return true;
	return false;
}

bool PickablePtr::operator>(PickablePtr obj) {
	if (ptr->getPriority() > obj.getPickablePtr()->getPriority())
		return true;
	return false;
}

bool PickablePtr::operator>=(PickablePtr obj) {
	if (ptr->getPriority() >= obj.getPickablePtr()->getPriority())
		return true;
	return false;
}

void PickablePtr::setPriority() {
	ptr->resetPriority(hos->getTimeStep());
}