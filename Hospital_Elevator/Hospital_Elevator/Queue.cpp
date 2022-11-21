#ifndef QUEUE_CPP
#define QUEUE_CPP
#include "Queue.h"
template <typename T> 
class LinkedQueue : public QueueADT<T> {
private:
	QNode<T>* Front;
	QNode<T>* Rear;
	int count;
public : 
	LinkedQueue() {
		count = 0;
		Front = nullptr;
		Rear = nullptr;
	}
	~LinkedQueue() {
		T tempval;
		while (!this->isEmpty()) {
			this->Dequeue(tempval);
		}
	}
	bool isEmpty() const {
		return (Front == nullptr && Rear == nullptr);
	}
	int getCount() const { return count; }
	void Enqueue(T value) {
		count++;
		QNode<T>* newNodePtr = new QNode<T>(value);
		if (Front == nullptr && Rear == nullptr) {
			Front = newNodePtr;
			Rear = newNodePtr;

		}
		else {
			Rear->setNext(newNodePtr);
			Rear = newNodePtr;
		}
	}
	bool Dequeue(T& value) {
		if (this->isEmpty()) { return false; }
		QNode<T>* tempPtr = Front;
		value = Front->getItem();
		if (count == 1) {
			Front = nullptr;
			Rear = nullptr;
		}
		else {
			Front = Front->getNext();
		}
		delete tempPtr;
		count--;
	}
	bool Peek(T& value) const {
		if (!this->isEmpty()) {
			value = Front->getItem();
			return true;
		}
		else return false; 
	}
};
#endif 