#ifndef QUEUE_H
#define QUEUE_H

#include "QNode.h"

template <typename T>
class Queue
{
private:
	QNode<T>* Front;
	QNode<T>* Rear;
	int count;
public:
	Queue();
	~Queue();
	void Enqueue(T value);
	bool Dequeue(T& value);
	void Peek(T& value) const;
	bool isEmpty() const;
	int getCount() const;

};

#include "Queue.cpp"

#endif