#include"Bag.h"
#include <iostream>
template <typename T>

class ArrayBag: public ArrayBagADT<T>
{
private:
	const int capacity;
	int count;
	T* items;

public:

	ArrayBag(int cap) : capacity(cap)
	{
		items = new T[capacity];
		count = 0;
	}

	int  GetSize() const
	{
		return count;
	}

	int  GetCapacity() const
	{
		return capacity;
	}

	bool isEmpty() const
	{
		if (count == 0)
			return true;
		return false;
	}

	bool isFull() const
	{
		if (count == capacity)
			return true;
		return false;
	}

	bool add(const T& entry)
	{
		if (isFull())
			return false;
		item[count] = entry;
		count++;
		return true;
	}

	bool remove(T& entry)
	{
		if (isEmpty())
			return false;
		entry = item[count];
		//item[count] = NULL;
		count--;
		return true;
	
	}
	
	~ArrayBag()
	{
		delete[]items;

	}

	//Copy constructor
	ArrayBag(const ArrayBag<T>& B) :capacity(B.capacity)
	{
		items = new T[capacity];
		for (int i = 0; i < B.count; i++)
			items[i] = B.items[i];
		count = B.count;
	}

	/*void clear()
	{

	}
	*/
};