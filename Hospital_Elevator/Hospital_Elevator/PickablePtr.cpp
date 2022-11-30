	#include "PickablePtr.h"

PickablePtr::PickablePtr(Pickable* ptr) { this->ptr = ptr; }

PickablePtr::~PickablePtr() {}

void PickablePtr::setPickablePtr(Pickable* ptr) { this->ptr = ptr; }

Pickable* PickablePtr::getPickablePtr() const { return ptr; }