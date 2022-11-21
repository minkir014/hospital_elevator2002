
#ifndef QUEUE_CPP
#define QUEUE_CPP

#include "Queue.h"
template <typename T> 
Queue<T>::Queue() {
	count = 0; 
	Front = nullptr; 
	Rear = nullptr;  
}
template <typename T>
Queue<T>::~Queue() {
	T tempval; 
	while (!this->isEmpty()) {
		this->Dequeue(tempval); 
	}
}
template <typename T>
bool Queue<T>::isEmpty() const {
	return (Front == nullptr && Rear == nullptr); 
}
template <typename T>
int Queue<T>::getCount() const { return count; }
template <typename T>
void Queue<T>::Enqueue(T value) {
	count++;
	QNode<T>* newNodePtr = new QNode<T>(value); 
	if (Front == nullptr && Rear == nullptr) {
		Front =newNodePtr; 
		Rear = newNodePtr; 

	}
	else {
		Rear->setNext(newNodePtr); 
		Rear = newNodePtr;
	}	 
}
template <typename T>
bool Queue<T>::Dequeue(T& value) {
	if (this->isEmpty() ) { return false; }
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
// value of T unchanged if  empty queue
void Queue<T>::Peek(T& value) const {
	if (!this->isEmpty()) {
		value = Front->getItem(); 
		return; 
	}
}

#endif 