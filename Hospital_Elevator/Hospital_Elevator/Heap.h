#pragma once

template <typename T>
class Heap {

public:
	virtual bool Create() = 0;

	virtual bool Insert(const T& Value) = 0;

	virtual bool Delete(T& value) = 0;
	
	virtual bool IsEmpty() const = 0;

	virtual int getCount() const = 0;

	virtual ~Heap() = 0;
};