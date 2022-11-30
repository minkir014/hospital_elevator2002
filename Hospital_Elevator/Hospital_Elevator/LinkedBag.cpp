#include "LinkedBag.h"

template <typename T>
LinkedBag<T>::LinkedBag() : Head(nullptr), count(0)
{

}

template <typename T>
LinkedBag<T>::LinkedBag(const LinkedBag<T>& B)
{
	count = B.count;
	LinkedNode<T>* org = B.Head;
	if (!org)
		Head = nullptr;
	else
	{
		Head = new LinkedNode<T>;
		Head->setItem(org->getItem());
		LinkedNode<T>* P = Head;
		org = org->getNext();
		while (org)
		{
			T item = org->getItem();
			LinkedNode<T>* temp = new LinkedNode<T>(item);
			P->setNext(temp);
			P = P->getNext();
			org = org->getNext();
		}
		P->setNext(nullptr);
	}
}

template <typename T>
bool LinkedBag<T>::isEmpty() const
{
	return Head == nullptr;
}

template <typename T>
int LinkedBag<T>::GetSize() const
{
	return count;
}

template <typename T>
LinkedNode<T>* LinkedBag<T>::getPointer(const T& entry) const
{
	bool found = false;
	LinkedNode<T>* P = Head;
	while (!found && (P != Head))
	{
		if (entry == P->getItem())
			found = true;
		else
			P = P->getNext();
	}
	return P;
}

template <typename T>
bool LinkedBag<T>::add(const T& entry)
{
	LinkedNode<T>* newNode = new LinkedNode<T>;
	newNode->setItem(entry);
	newNode->setNext(Head);
	Head = newNode;
	count++;
}

template <typename T>
bool LinkedBag<T>::remove(T& entry) 
{
	LinkedNode<T>* newNode = getPointer(entry);
	bool check = !isEmpty() && (newNode != nullptr);
		if (check)
		{
			newNode->setItem(Head->getItem());
			LinkedNode<T>* Del = Head;
			Head = Head->getNext();

			Del->setNext(nullptr);
			delete Del;
			Del = nullptr;

			count--;
		}
		return check;
}

template <typename T>
void LinkedBag<T>::clear()
{
	LinkedNode<T>* Del = Head;
	while (Head)
	{
		Head = Head->getNext();
		Del->setNext(nullptr);
		delete Del;
		Del = nullptr;
	}
	count = 0;
}

template <typename T>
LinkedBag<T>::~LinkedBag() 
{
	clear();
}