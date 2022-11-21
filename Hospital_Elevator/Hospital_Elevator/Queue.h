#ifndef QUEUE_H
#define QUEUE_H
#include "QNode.h"
template <typename T>
class QueueADT
{
public:
	virtual void Enqueue(T value) = 0;
	virtual  bool Dequeue(T& value) = 0;
	virtual bool Peek(T& value) const = 0;
	virtual bool isEmpty() const = 0;
	virtual int getCount() const = 0;

};

#endif