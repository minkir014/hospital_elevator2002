#ifndef _ARRBAG_H
#define _ARRBAG_H
#include"Bag.h"

template <typename T>
class ArrayBag : public BagADT<T>
{
private:
	const int capacity;
	int count;
	T* items;

public:
	ArrayBag(int cap);
	ArrayBag(const ArrayBag<T>& B); //Copy constructor
	~ArrayBag();

	int GetSize() const;
	int GetCapacity() const;

	bool isEmpty() const;
	bool isFull() const;

	bool add(const T& entry);
	bool remove(T& entry);

};

#include "ArrayBag.cpp"

#endif