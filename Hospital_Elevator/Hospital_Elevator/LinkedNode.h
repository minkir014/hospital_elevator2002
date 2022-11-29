#ifndef LINKEDNODE_H
#define LINKEDNODE_H

template<typename T>
class LinkedNode
{
private:
	T item;
	LinkedNode<T>* next;

public:
	LinkedNode() { this->next = nullptr; }
	LinkedNode(T newItem) {
		item = newItem;
		next = nullptr;
	}
	void setItem(T newItem) { item = newItem; }
	void setNext(LinkedNode<T>* nextNodePtr) { next = nextNodePtr; }
	T getItem() const
	{
		return item;

	}
	LinkedNode<T>* getNext() const
	{
		return this->next;
	}

};

#endif	
