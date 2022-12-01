#pragma once
#include "Pickable.h"
#include "Hospital.h"

class PickablePtr {
private:
	Pickable* ptr;
	bool temp;

	const Hospital* hos;
	
	void setPriority();
public:
	PickablePtr(Pickable* ptr = nullptr);
	PickablePtr(int tempId);
	~PickablePtr();

	void setPickablePtr(Pickable* ptr);

	bool destroyPickable();

	Pickable* getPickablePtr() const;

	bool operator==(PickablePtr obj);

	bool operator>(PickablePtr obj);
	bool operator<(PickablePtr obj);
	bool operator>=(PickablePtr obj);
	bool operator<=(PickablePtr obj);



	
};

// Operator Overloading: External Criteria on FIFO
// Add AutoS to Pritority of Patients
// Operator Overloading of ID
// Copy Constructor of Int