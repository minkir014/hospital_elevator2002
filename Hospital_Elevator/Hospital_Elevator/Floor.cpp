#include "Floor.h";
#include "Defs.h";
#include "Queue.h";
#include "LinkedQueue.h";
#include "HeapNode.h";
#include "LinkedHeap.h"; 
#include "Pickableptr.h";

Floor::Floor(int Cfloor) :CurrentFloor(Cfloor) {} 

void Floor::TraversePickables(int* Vup, int* Vdown, int* Cup, int* Cdown, int* Pup, int* Pdown, int& Vupsize, int& Vdownsize, int& Cupsize, int& Cdownsize, int& Pupsize, int& Pdownsize) {
	//  sizes should be passed [Zero]; 
	
	// Traverse Up
		LinkedQueue<LinkedHeap<PickablePtr>> BreadthQueue;
		BreadthQueue.Enqueue(Up);
		while (!BreadthQueue.isEmpty()) {
			LinkedHeap<PickablePtr> Front;
			BreadthQueue.Dequeue(Front);
			PickablePtr PickableInFront = Front.peekTop();
			Pickable* PickableInFrontPtr = PickableInFront.getPickablePtr();
			E_UserType  Type = PickableInFrontPtr->getType(); 
			if (Type == V) {
				Vup[Vupsize] = PickableInFrontPtr->getID(); 
				Vupsize++; 
			}
			else if (Type == C) {
				Cup[Cupsize] = PickableInFrontPtr->getID();
				Cupsize++; 
			}else{
				Pup[Pupsize] = PickableInFrontPtr->getID();
				Pupsize++;
			}
			if (Front.getLeftSubTree().getCount() != 0) {
				BreadthQueue.Enqueue(Front.getLeftSubTree());
			}
			if (Front.getLeftSubTree().getCount() != 0) {
				BreadthQueue.Enqueue(Front.getRightSubTree());
			}
			
		}
	//Traverse Down
		BreadthQueue.Enqueue(Down);
		while (!BreadthQueue.isEmpty()) {
			LinkedHeap<PickablePtr> Front;
			BreadthQueue.Dequeue(Front);
			PickablePtr PickableInFront = Front.peekTop();
			Pickable* PickableInFrontPtr = PickableInFront.getPickablePtr();
			E_UserType  Type = PickableInFrontPtr->getType();
			if (Type == V) {
				Vdown[Vdownsize] = PickableInFrontPtr->getID();
				Vdownsize++;
			}	
			else if (Type == C) {
				Cdown[Cdownsize] = PickableInFrontPtr->getID();
				Cdownsize++;
			}
			else {
				Pdown[Pdownsize] = PickableInFrontPtr->getID();
				Pdownsize++;
			}
			if (Front.getLeftSubTree().getCount() != 0) {
				BreadthQueue.Enqueue(Front.getLeftSubTree());
			}
			if (Front.getLeftSubTree().getCount() != 0) {
				BreadthQueue.Enqueue(Front.getRightSubTree());
			}

		}
}

int Floor::GetUpHeapSize() const {return Up.getCount();}
int Floor::GetdownHeapSize() const{ return Down.getCount();}

bool Floor::isWaiting() const {
	if (Up.IsEmpty() && Down.IsEmpty())
		return false;

	return true;
}