#pragma once
#include "Heap.h"
#include "HeapNode.h"

template <typename T>
class LinkedHeap : Heap<T> {
private:
	HeapNode<T>* root;
	int count;
	
	HeapNode<T>* reHeapUp(HeapNode<T>* parent, HeapNode<T>* child);
	HeapNode<T>* reHeapDown(HeapNode<T>* parent);
	bool Rebuild(HeapNode<T>* SubTreeRoot);
	HeapNode<T>* insert(HeapNode<T>* parent, HeapNode<T>* newNode, int determiner);

	bool DestroyHeap(HeapNode<T>* SubTreeRoot);

	T search(T obj, HeapNode<T>* subTreeRoot) const;
public:
	LinkedHeap();
	~LinkedHeap();

	bool Insert(const T& Value);

	bool ReBuild();

	bool Delete();
	bool removeObj(const T& value);

	T peekTop() const;

	const LinkedHeap<T> getRightSubTree() const;

	const LinkedHeap<T> getLeftSubTree() const;

	T Search(T key) const;

	bool IsEmpty() const;
	int getCount() const;
};
#include "LinkedHeap.cpp"