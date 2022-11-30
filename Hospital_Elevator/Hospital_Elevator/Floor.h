#pragma once
#include "LinkedHeap.h"
#include "PickablePtr.h"
#include "Defs.h"

class Floor {
private:
	int CurrentFloor;
	LinkedHeap<PickablePtr> Up;
	LinkedHeap<PickablePtr> Down;

	//PickablePtr // To be asked about
	//Traverse in Heap
	//Divide into 2 lists
	//Have next property
public:
	Floor(int CFloor); 
	void TraversePickables(int* Vup, int* Vdown, int* Cup, int* Cdown, int* Pup, int* Pdown, int &Vupsize, int & Vdownsize, int& Cupsize, int& Cdownsize, int& Pupsize, int& Pdownsize);
	int GetUpHeapSize() const ; // will need to Intialize arrays int traverse Functions ; 
	int GetdownHeapSize() const;
};