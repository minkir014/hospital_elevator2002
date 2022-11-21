#include"ArrayBag.h"

template <typename T>
ArrayBag<T>::ArrayBag(int cap) : capacity(cap)
{
	items = new T[capacity];
	count = 0;
}

template <typename T>
ArrayBag<T>::ArrayBag(const ArrayBag<T>& B) :capacity(B.capacity)
{
	items = new T[capacity];
	for (int i = 0; i < B.count; i++)
		items[i] = B.items[i];
	count = B.count;
}

template <typename T>
ArrayBag<T>::~ArrayBag()
{
	delete[] items;
}

template <typename T>
int ArrayBag<T>::GetSize() const
{
	return count;
}

template <typename T>
int ArrayBag<T>::GetCapacity() const
{
	return capacity;
}

template <typename T>
bool ArrayBag<T>::isEmpty() const
{
	if (count == 0)
		return true;
	return false;
}

template <typename T>
bool ArrayBag<T>::isFull() const
{
	if (count == capacity)
		return true;
	return false;
}

template <typename T>
bool ArrayBag<T>::add(const T& entry)
{
	if (isFull())
		return false;
	items[count++] = entry;
	return true;
}

template <typename T>
bool ArrayBag<T>::remove(T& entry)
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