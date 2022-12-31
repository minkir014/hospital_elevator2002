#pragma once
#include "Pickable.h"

class Hospital;
class PickablePtr {
private:
	Pickable* ptr;
	bool temp;

	bool stairs;
	bool completed;
	bool inService;

	const Hospital* hos;
	
	void setPriority();
public:
	PickablePtr(Pickable* ptr = nullptr, const Hospital* hos = nullptr, bool tmp = false, bool stair = false);
	PickablePtr(const PickablePtr& obj);
	PickablePtr(int tempId);
	PickablePtr& operator=(const PickablePtr& obj);
	~PickablePtr();

	void setPickablePtr(Pickable* ptr);

	bool destroyPickable();


	Pickable* getPickablePtr() const;
	bool setStairs();
	bool setCompleted();
	bool setInService();

	bool operator==(const PickablePtr obj);
	bool operator>(PickablePtr obj);
	bool operator<(PickablePtr obj);
	bool operator>=(PickablePtr obj);
	bool operator<=(PickablePtr obj);



	
};

// Operator Overloading: External Criteria on FIFO
// Add AutoS to Pritority of Patients
// Operator Overloading of ID
// Copy Constructor of Int