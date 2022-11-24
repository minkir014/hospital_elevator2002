#pragma once

template <typename T>
class HeapNode {
private:
	T data;
	HeapNode<T>* left;
	HeapNode<T>* right;

public:
	HeapNode() : left(nullptr), right(nullptr) {}
	HeapNode(T dataItem, HeapNode<T>* lftptr = nullptr, HeapNode<T>* rightptr = nullptr) : data(dataItem), left(lftptr), right(rightptr) {}
	
	T getData() { return data; }
	HeapNode<T>* getRight() { return right; }
	HeapNode<T>* getLeft() { return left; }

	void setData(T data) { this->data = data; }
	void setRightPtr(HeapNode<T>* right) { this->right = right; }
	void setLeftPtr(HeapNode<T>* left) { this->left = left; }

};