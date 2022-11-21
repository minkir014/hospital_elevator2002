#ifndef  _LINKED_QUEUE_H
#define _LINKED_QUEUE_H
#include "Queue.h"


template <typename T>
class LinkedQueue : public QueueADT<T> {
private:
	QNode<T>* Front;
	QNode<T>* Rear;
	int count;
public:
	LinkedQueue();
	~LinkedQueue();

	bool isEmpty() const;
	int getCount() const;

	void Enqueue(T value);
	bool Dequeue(T& value);
	bool Peek(T& value) const;

};

#include "LinkedQueue.cpp"

#endif