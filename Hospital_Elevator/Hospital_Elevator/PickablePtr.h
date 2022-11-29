#pragma once
#include "Pickable.h"

class PickablePtr {
private:
	Pickable* ptr;

public:
	PickablePtr(Pickable* ptr = nullptr);
	~PickablePtr();

	void setPickablePtr(Pickable* ptr);

	Pickable* getPickablePtr() const;
	
};

// Operator Overloading: External Criteria on FIFO
// Add AutoS to Pritority of Patients