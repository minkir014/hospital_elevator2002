#ifndef _LINKED_BAG_H
#define _LINKED_BAG_H

#include"Bag.h"
#include "LinkedNode.h"

template <typename T>
class LinkedBag : public BagADT<T>
{
private:
	
	LinkedNode<T>* Head;
	int count;

	LinkedNode<T>* getPointer(const T& entry) const;

public:
	LinkedBag();
	LinkedBag(const LinkedBag<T>& B); //Copy constructor
	~LinkedBag();

	int GetSize() const;

	bool isEmpty() const;

	bool add(const T& entry);
	bool remove(T& entry);
	void clear();

};

#include "LinkedBag.cpp"
;
#endif