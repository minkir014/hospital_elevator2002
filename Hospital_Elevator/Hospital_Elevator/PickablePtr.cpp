	#include "PickablePtr.h"

PickablePtr::PickablePtr(Pickable* ptr) { this->ptr = ptr; }

PickablePtr::~PickablePtr() {}

void PickablePtr::setPickablePtr(Pickable* ptr) { this->ptr = ptr; }

Pickable* PickablePtr::getPickablePtr() const { return ptr; }

bool PickablePtr::destroyPickable() { delete ptr; return true; }

bool PickablePtr::operator==(PickablePtr obj) {
	if (ptr->getID() == obj.getPickablePtr()->getID())
		return true;

	return false;
}