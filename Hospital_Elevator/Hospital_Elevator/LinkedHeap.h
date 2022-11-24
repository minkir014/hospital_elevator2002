#pragma once
#include "Heap.h"
#include "HeapNode.h"

template <typename T>
class LinkedHeap {
private:
	HeapNode<T>* root;
	int count;
	
	HeapNode<T>* reHeapUp(HeapNode<T>* parent, HeapNode<T>* child);
	HeapNode<T>* reHeapDown(HeapNode<T>* parent);
	bool Rebuild(HeapNode<T>* SubTreeRoot);
	HeapNode<T>* insert(HeapNode<T>* parent, HeapNode<T>* newNode, int determiner);
public:
	LinkedHeap();
	//~LinkedHeap();

	bool Insert(const T& Value);

	bool ReBuild();


	bool Delete();

	bool IsEmpty() const;

	int getCount() const;
};

#include "LinkedHeap.cpp"