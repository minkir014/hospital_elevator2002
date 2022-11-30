#pragma once
using namespace std;
template <typename T>
class BagADT
{
public:
	//ArrayBagADT(int cap) = 0;
	virtual bool isEmpty() const = 0;
	virtual int GetSize() const = 0;
	virtual bool add(const T& entry) = 0;
	virtual bool remove(T& entry) = 0;
	//virtual void clear() = 0;
	//virtual ~ArrayBagADT() = 0;

};