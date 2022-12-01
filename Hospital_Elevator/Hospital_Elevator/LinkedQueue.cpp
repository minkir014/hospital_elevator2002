#include "LinkedQueue.h"

template <typename T>
LinkedQueue<T>::LinkedQueue() {
	count = 0;
	Front = nullptr;
	Rear = nullptr;
}


template <typename T>
LinkedQueue<T>::~LinkedQueue() {
	T tempval;
	while (!this->isEmpty()) {
		this->Dequeue(tempval);
	}
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const {
	return (Front == nullptr && Rear == nullptr);
}

template <typename T>
int LinkedQueue<T>::getCount() const { return count; }

template <typename T>
void LinkedQueue<T>::Enqueue(T & value) {
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

template <typename T>
bool LinkedQueue<T>::Dequeue(T& value) {
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

template <typename T>
bool LinkedQueue<T>::Peek(T& value) const {
	if (!this->isEmpty()) {
		value = Front->getItem();
		return true;
	}
	else return false;
}