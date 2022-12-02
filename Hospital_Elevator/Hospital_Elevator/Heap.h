#pragma once

template <typename T>
class Heap {

public:
	virtual bool ReBuild() = 0;

	virtual bool Insert(const T& Value) = 0;

	virtual bool Delete(T& Value) = 0;

	virtual T peekTop() const = 0;
	
	virtual bool IsEmpty() const = 0;

	virtual int getCount() const = 0;

	virtual ~Heap() {};
};