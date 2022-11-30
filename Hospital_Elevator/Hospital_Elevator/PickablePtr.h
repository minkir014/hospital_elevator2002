#pragma once
#include "Pickable.h"

class PickablePtr {
private:
	Pickable* ptr;

public:
	PickablePtr(Pickable* ptr = nullptr);
	~PickablePtr();

	void setPickablePtr(Pickable* ptr);

	bool destroyPickable();

	Pickable* getPickablePtr() const;

	bool operator==(PickablePtr obj);
	
};

// Operator Overloading: External Criteria on FIFO
// Add AutoS to Pritority of Patients
// Operator Overloading of ID
// Copy Constructor of Int