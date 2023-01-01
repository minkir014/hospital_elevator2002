#include "Floor.h";
#include "Defs.h";
#include "Queue.h";
#include "LinkedQueue.h";
#include "HeapNode.h";
#include "LinkedHeap.h"; 
#include "Pickableptr.h";

Floor::Floor(int Cfloor) : CurrentFloor(Cfloor), Up(false), Down(false) {
	FirstCargo[0] = 0;
	FirstVisitor[0] = 0;
	FirstVisitor[1] = 0;
	FirstCargo[1] = 0;
}

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
int Floor::getCurrentFloor() const { return CurrentFloor; }

void Floor::build() {
	Up.ReBuild();
	Down.ReBuild();
}

bool Floor::EnqueueUp(PickablePtr ptr) {
	if (FirstVisitor[0] == 0 && ptr.getPickablePtr()->getType() == V)
		FirstVisitor[0] = ptr;

	if (FirstCargo[0] == 0 && ptr.getPickablePtr()->getType() == C)
		FirstCargo[0] = ptr;

	bool u = Up.Insert(ptr);
	return u;
}
bool Floor::EnqueuDown(PickablePtr ptr) {
	if (FirstVisitor[1] == 0 && ptr.getPickablePtr()->getType() == V)
		FirstVisitor[1] = ptr;

	if (FirstCargo[1] == 0 && ptr.getPickablePtr()->getType() == C)
		FirstCargo[1] = ptr;

	return Down.Insert(ptr);

}

bool Floor::DeletePickable(PickablePtr& ptr) {

	PickablePtr ptrSearch = Up.Search(ptr);
	if (!(ptrSearch == 0)) {
		if (ptrSearch == FirstVisitor[0])
			ValidateFirst(Up, ptrSearch, 0);

		return Up.removeObj(ptr);
	}

	ptrSearch = Down.Search(ptr);

	if (!(ptrSearch == 0)) {
		if (ptrSearch == FirstVisitor[1])
			ValidateFirst(Down, ptrSearch, 1);

		return Down.removeObj(ptr);
	}

	return false;
}

PickablePtr Floor::peekTopPriority(ElevatorType elevatorType, int userType) {
	if (userType != -1)
		if (elevatorType == CE && userType == C) return FirstCargo[0] > FirstCargo[1] ? FirstCargo[0] : FirstCargo[1];

	PickablePtr temp = (Up.peekTop() > Down.peekTop() ? Up.peekTop() : Down.peekTop());

	if (temp == 0)
		return temp;

	if (temp.getPickablePtr()->getType() == C && elevatorType == CE)
		return temp;

	else if (temp.getPickablePtr()->getType() == V && elevatorType == CE)
		return 0;

	else if (temp.getPickablePtr()->getType() != C)
		return temp;

	else return 0;
}

PickablePtr Floor::peekTopPriorityDown(ElevatorType elevatorType, int userType) {
	if (userType != -1)
		if (elevatorType == CE && userType == C) return FirstCargo[1]; // To be modified...............

	PickablePtr temp = Down.peekTop();

	if (temp == 0)
		return temp;

	if (temp.getPickablePtr()->getType() == C && elevatorType == CE)
		return temp;

	else if (temp.getPickablePtr()->getType() == V && elevatorType == CE)
		return 0;

	else if (temp.getPickablePtr()->getType() != C)
		return temp;

	else
		return 0;

}

PickablePtr Floor::peekTopPriorityUp(ElevatorType elevatorType, int userType) {
	if (userType != -1)
		if (elevatorType == CE && userType == C) return FirstCargo[0]; // To be modified...............

	PickablePtr temp = Up.peekTop();

	if (temp == 0)
		return temp;

	if (temp.getPickablePtr()->getType() == C && elevatorType == CE)
		return temp;

	else if (temp.getPickablePtr()->getType() == V && elevatorType == CE)
		return 0;

	else if (temp.getPickablePtr()->getType() != C)
		return temp;

	else
		return 0;

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
	if (Up.peekTop() == FirstVisitor[0] || Up.peekTop() == FirstCargo[0])
		ValidateFirst(Up, Up.peekTop(), 0);

	if (Up.Delete(ptr))
		return true;

	else
		return false;
}

bool Floor::DequeueDown(PickablePtr& ptr) {
	if (Down.peekTop() == FirstVisitor[1] || Down.peekTop() == FirstCargo[1])
		ValidateFirst(Down, Down.peekTop(), 1);

	if (Down.Delete(ptr))
		return true;

	else
		return false;
}

void Floor::ValidateFirst(const LinkedHeap<PickablePtr>& LH, const PickablePtr& ptr, int UpOrDown) {

	if (!(FirstVisitor[UpOrDown] == 0) && FirstVisitor[UpOrDown] == ptr)
		FirstVisitor[UpOrDown] = searchForV(LH, UpOrDown);

	if (!(FirstCargo[UpOrDown] == 0) && FirstCargo[UpOrDown] == ptr)
		FirstCargo[UpOrDown] = searchForC(LH, UpOrDown);

}

PickablePtr Floor::searchForV(const LinkedHeap<PickablePtr>& LH, int UpOrDown) const {

	PickablePtr ptr = LH.peekTop();

	if (ptr == 0)
		return 0;

	PickablePtr ptr1(0);
	PickablePtr ptr2(0);

	if (ptr.getPickablePtr()->getType() == P || ptr == FirstVisitor[UpOrDown]) {
		ptr1 = searchForV(LH.getLeftSubTree(), UpOrDown);
		ptr2 = searchForV(LH.getRightSubTree(), UpOrDown);

		ptr1 = (ptr1 < ptr2) ? ptr2 : ptr1;
		if (ptr1.getPickablePtr()->getPriority() < 0)
			return 0;
		else return ptr1;
	}

	return ptr;

}


PickablePtr Floor::searchForC(const LinkedHeap<PickablePtr>& LH, int UpOrDown) const {

	PickablePtr ptr = LH.peekTop();

	if (ptr == 0)
		return 0;

	PickablePtr ptr1(0);
	PickablePtr ptr2(0);

	if (ptr.getPickablePtr()->getType() == P || ptr.getPickablePtr()->getType() == V || ptr == FirstCargo[UpOrDown]) {
		ptr1 = searchForV(LH.getLeftSubTree(), UpOrDown);
		ptr2 = searchForV(LH.getRightSubTree(), UpOrDown);

		if (ptr1 == 0)
			return ptr2;

		else if (ptr2 == 0)
			return ptr1;

		else
			return (ptr1 < ptr2) ? ptr2 : ptr1;
	}

	return ptr;

}

PickablePtr Floor::getFirstVisitor() { return (FirstVisitor[0] > FirstVisitor[1] ? FirstVisitor[0] : FirstVisitor[1]); }