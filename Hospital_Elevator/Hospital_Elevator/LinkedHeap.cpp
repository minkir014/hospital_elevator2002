#include "LinkedHeap.h"
#include <cmath>

template <typename T>
LinkedHeap<T>::LinkedHeap() : root(nullptr), count(0) { }

template <typename T>
LinkedHeap<T>::~LinkedHeap() {
	DestroyHeap(root);
	count = 0;
}

template <typename T>
bool LinkedHeap<T>::DestroyHeap(HeapNode<T>* SubTreeRoot) {
	if (SubTreeRoot == nullptr)
		return false;

	DestroyHeap(SubTreeRoot->getLeft());
	DestroyHeap(SubTreeRoot->getRight());
	delete SubTreeRoot;
}


template <typename T>
HeapNode<T>* LinkedHeap<T>::reHeapUp(HeapNode<T>* Parent, HeapNode<T>* Child) {
	if (Parent->getData() < Child->getData()) {
		T temp = Parent->getData();
		Parent->setData(Child->getData());
		Child->setData(temp);
	}
	return Parent;
}

template <typename T>
HeapNode<T>* LinkedHeap<T>::reHeapDown(HeapNode<T>* Parent) {
	HeapNode<T>* Large = nullptr;
	
	if (Parent->getLeft() != nullptr && Parent->getRight() == nullptr)
		Large = Parent->getLeft();
	else if (Parent->getLeft() == nullptr)
		return Parent;
	else if (Parent->getLeft()->getData() >= Parent->getRight()->getData())
		Large = Parent->getLeft();
	else
		Large = Parent->getRight();


	if (Parent->getData() < Large->getData()) {
		T temp = Parent->getData();
		Parent->setData(Large->getData());
		Large->setData(temp);
		return Large;
	}
	return Parent;
}

template <typename T>
bool LinkedHeap<T>::Insert(const T& Value) {
	HeapNode<T>* newNode = new HeapNode<T>(Value);
	if (root == nullptr) {
		root = newNode;
		count++;
		return true;
	}

	int determiner = log2f(count + 1);
	determiner = powf(2, determiner);

	insert(root, newNode, determiner);
	return true;
}

template <class T>
HeapNode<T>* LinkedHeap<T>::insert(HeapNode<T>* parent, HeapNode<T>* newNode, int determiner) {
	int newDeterminer = (count + 1) * 2 / determiner;
	HeapNode<T>* newParent = nullptr;

	if (newDeterminer % 2 == 0)
		if (parent->getLeft() == nullptr) {
			parent->setLeftPtr(newNode);
			count++;
		}
		else
			newParent = insert(parent->getLeft(), newNode, determiner / 2);

	else
		if (parent->getRight() == nullptr) {
			parent->setRightPtr(newNode);
			count++;
		}
		else
			newParent = insert(parent->getRight(), newNode, determiner / 2);

	return reHeapUp(parent, (newParent) ? newParent : newNode);
}

template <typename T>
bool LinkedHeap<T>::Delete() {
	if (root == nullptr)
		return false;

	if (count == 1) {
		delete root;
		root = nullptr;
		count--;
		return true;
	}

	int determiner = log2f(count);
	determiner = powf(2, determiner);
	int n = 2;


	HeapNode<T>* ptr = root;

	while (ptr != nullptr) {
		if (int(count * n / determiner) % 2 == 0) {
			if (ptr->getLeft()->getLeft() == nullptr)
				break;
			ptr = ptr->getLeft();

		}
		else {
			if (ptr->getRight()->getLeft() == nullptr)
				break;
			ptr = ptr->getRight();
		}

		n *= 2;
	}

	if (int(count * n / determiner) % 2 == 0) {
		root->setData(ptr->getLeft()->getData());
		delete ptr->getLeft();
		ptr->setLeftPtr(nullptr);
	}
	else {
		root->setData(ptr->getRight()->getData());
		delete ptr->getRight();
		ptr->setRightPtr(nullptr);
	}

	ptr = root;
	HeapNode<T>* reHeapedPtr = reHeapDown(ptr);
	while (ptr != reHeapedPtr) {
		ptr = reHeapedPtr;
		reHeapedPtr = reHeapDown(ptr);
	}

	count--;
	return true;

}

template <typename T>
bool LinkedHeap<T>::Rebuild(HeapNode<T>* SubTreeRoot) {
	if (SubTreeRoot == nullptr)
		return false;

	reHeapDown(SubTreeRoot);
	Rebuild(SubTreeRoot->getLeft());
	Rebuild(SubTreeRoot->getRight());

	HeapNode<T>* ptr = SubTreeRoot;
	HeapNode<T>* reHeapedPtr = reHeapDown(ptr);
	while (ptr != reHeapedPtr) {
		ptr = reHeapedPtr;
		reHeapedPtr = reHeapDown(ptr);
	}

}

template <typename T>
bool LinkedHeap<T>::ReBuild() {
	if (root == nullptr)
		return false;

	if (count == 1)
		return true;

	Rebuild(root);
}

template <typename T>
T LinkedHeap<T>::peekTop() const { if (root != nullptr)  return root->getData(); else return 0;  }

template <typename T>
bool LinkedHeap<T>::IsEmpty() const { return !count; }

template <typename T>
int LinkedHeap<T>::getCount() const { return count; }

template <typename T>
const LinkedHeap<T> LinkedHeap<T>::getRightSubTree() const {
	LinkedHeap<T> LH;
	LH.root = root->getRight();

	return LH;
}

template <typename T>
T LinkedHeap<T>::Search(T key) const {
	if (root == nullptr)
		return 0;

	if (key == root->getData())
		return root->getData();

	search(key, root);
}

template <typename T>
T LinkedHeap<T>::search(T key, HeapNode<T>* subTreeRoot) const {
	if (subTreeRoot == nullptr)
		return 0;

	if (key == subTreeRoot->getData())
		return subTreeRoot->getData();

	search(key, subTreeRoot->getLeft());
	search(key, subTreeRoot->getRight());
}

template <typename T>
const LinkedHeap<T> LinkedHeap<T>::getLeftSubTree() const {
	LinkedHeap<T> LH;
	LH.root = root->getLeft();

	return LH;
}