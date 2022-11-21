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
		items[count++] = entry;
		return true;
	}

	bool remove(T& entry)
	{
		if (isEmpty())
			return false;
		for (int i = 0; i < count; i++)
			if (items[i] == entry)
			{
				T temp = items[i];
				items[i] = items[count - 1];
				items[count - 1] = temp;
				count--;
				return true;
			}
		return false;
	
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