#include "Floor.h";
#include "Defs.h";
#include "Queue.h";
#include "LinkedQueue.h";
#include "HeapNode.h";
#include "LinkedHeap.h"; 
#include "Pickableptr.h";

Floor::Floor(int Cfloor) :CurrentFloor(Cfloor), Up(false), Down(false) {}

void Floor::TraversePickables(int* Vup, int* Vdown, int* Cup, int* Cdown, int* Pup, int* Pdown, int& Vupsize, int& Vdownsize, int& Cupsize, int& Cdownsize, int& Pupsize, int& Pdownsize) {
	//  sizes should be passed [Zero]; 
	
	// Traverse Up
		LinkedQueue<LinkedHeap<PickablePtr>> BreadthQueue;
		LinkedHeap<PickablePtr> LH(Up, true);
		BreadthQueue.Enqueue(LH);
		while (!BreadthQueue.isEmpty()) {
			LinkedHeap<PickablePtr> Front;
			BreadthQueue.Dequeue(Front);
			PickablePtr PickableInFront = Front.peekTop();
			if (PickableInFront == 0)  continue; 
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
				LinkedHeap<PickablePtr> heaps(Front.getLeftSubTree(), true);
				BreadthQueue.Enqueue(heaps);
			}
			if (Front.getRightSubTree().getCount() != 0) {
				LinkedHeap<PickablePtr> heaps(Front.getRightSubTree(), true);
				BreadthQueue.Enqueue(heaps);
			}
			
		}
	//Traverse Down
		LinkedHeap<PickablePtr> LH1(Down, true);
		while (!BreadthQueue.isEmpty()) {
			LinkedHeap<PickablePtr> Front;
			BreadthQueue.Dequeue(Front);
			PickablePtr PickableInFront = Front.peekTop();
			if (PickableInFront == 0)  continue;
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
				LinkedHeap<PickablePtr> heaps(Front.getLeftSubTree(), true);
				BreadthQueue.Enqueue(heaps);
			}
			if (Front.getRightSubTree().getCount() != 0) {
				LinkedHeap<PickablePtr> heaps(Front.getRightSubTree(), true);
				BreadthQueue.Enqueue(heaps);
			}

		}
}

int Floor::GetUpHeapSize() const {return Up.getCount();}
int Floor::GetdownHeapSize() const{ return Down.getCount();}

bool Floor::EnqueueUp(PickablePtr ptr) {
	return Up.Insert(ptr);
}
bool Floor::EnqueuDown(PickablePtr ptr) {
	return Down.Insert(ptr);
	
}

PickablePtr Floor::getPickable(PickablePtr key) const {
	PickablePtr ptr = Up.Search(key);
	if (!(ptr == 0))
		return ptr;
	
	ptr = Down.Search(key);
	if (!(ptr == 0))
		return ptr;

	return 0;

}

bool Floor::isWaiting() const {
	if (Up.IsEmpty() && Down.IsEmpty())
		return false;

	return true;
}