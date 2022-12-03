#include "Floor.h";
#include "Defs.h";
#include "Queue.h";
#include "LinkedQueue.h";
#include "HeapNode.h";
#include "LinkedHeap.h"; 
#include "Pickableptr.h";

Floor::Floor(int Cfloor) : CurrentFloor(Cfloor), Up(false), Down(false), FirstVisitor(0), FirstCargo(0) {}

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
		}
		else {
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

int Floor::GetUpHeapSize() const { return Up.getCount(); }
int Floor::GetdownHeapSize() const { return Down.getCount(); }

bool Floor::EnqueueUp(PickablePtr ptr) {
	if (FirstVisitor == 0 && ptr.getPickablePtr()->getType() == V)
		FirstVisitor = ptr;

	if (FirstCargo == 0 && ptr.getPickablePtr()->getType() == C)
		FirstCargo = ptr;

	bool u = Up.Insert(ptr);
	return u;
}
bool Floor::EnqueuDown(PickablePtr ptr) {
	if (FirstVisitor == 0 && ptr.getPickablePtr()->getType() == V)
		FirstVisitor = ptr;

	if (FirstCargo == 0 && ptr.getPickablePtr()->getType() == C)
		FirstCargo = ptr;

	return Down.Insert(ptr);

}

bool Floor::DeletePickable(PickablePtr& ptr) {

	PickablePtr ptrSearch = Up.Search(ptr);
	if (!(ptrSearch == 0)) {
		if (ptrSearch == FirstVisitor)
			ValidateFirst(Up, ptrSearch);

		return Up.removeObj(ptr);
	}

	ptrSearch = Down.Search(ptr);

	if (!(ptrSearch == 0)) {
		if (ptrSearch == FirstVisitor)
			ValidateFirst(Down, ptrSearch);

		return Down.removeObj(ptr);
	}

	return false;
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

bool Floor::isWaitingUp() const {
	if (Up.IsEmpty())
		return false;

	return true;
}

bool Floor::isWaitingDown() const {
	if (Down.IsEmpty())
		return false;

	return true;
}

bool Floor::DequeueUp(PickablePtr& ptr) {
	if (Up.peekTop() == FirstVisitor || Up.peekTop() == FirstCargo)
		ValidateFirst(Up, Up.peekTop());

	if (Up.Delete(ptr))
		return true;

	else
		return false;
}

bool Floor::DequeueDown(PickablePtr& ptr) {
	if (Down.peekTop() == FirstVisitor || Down.peekTop() == FirstCargo)
		ValidateFirst(Down, Down.peekTop());

	if (Down.Delete(ptr))
		return true;

	else
		return false;
}

void Floor::ValidateFirst(const LinkedHeap<PickablePtr>& LH, const PickablePtr& ptr) {

	if (!(FirstVisitor == 0) && FirstVisitor == ptr)
		FirstVisitor = searchForV(LH);

	if (!(FirstCargo == 0) && FirstCargo == ptr)
		FirstCargo = searchForC(LH);

}

PickablePtr Floor::searchForV(const LinkedHeap<PickablePtr>& LH) const {

	PickablePtr ptr = LH.peekTop();

	if (ptr == 0)
		return 0;

	PickablePtr ptr1(0);
	PickablePtr ptr2(0);

	if (ptr.getPickablePtr()->getType() == P || ptr == FirstVisitor) {
		ptr1 = searchForV(LH.getLeftSubTree());
		ptr2 = searchForV(LH.getRightSubTree());

		ptr1 = (ptr1 < ptr2) ? ptr2 : ptr1;
		if (ptr1 < 0)
			return 0;
		else return ptr1;
	}

	return ptr;

}


PickablePtr Floor::searchForC(const LinkedHeap<PickablePtr>& LH) const {

	PickablePtr ptr = LH.peekTop();

	if (ptr == 0)
		return 0;

	PickablePtr ptr1(0);
	PickablePtr ptr2(0);

	if (ptr.getPickablePtr()->getType() == P || ptr.getPickablePtr()->getType() == V || ptr == FirstCargo) {
		ptr1 = searchForV(LH.getLeftSubTree());
		ptr2 = searchForV(LH.getRightSubTree());

		if (ptr1 == 0)
			return ptr2;

		else if (ptr2 == 0)
			return ptr1;

		else
			return (ptr1 < ptr2) ? ptr2 : ptr1;
	}

	return ptr;

}

PickablePtr Floor::getFirstVisitor() const { return FirstVisitor; }