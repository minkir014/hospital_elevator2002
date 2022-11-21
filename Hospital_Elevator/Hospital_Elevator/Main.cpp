#include<iostream>
using namespace std;
#include "Queue.cpp"
#include "Bag.cpp"
int main() {
	// test 
	ArrayBag<int> q(10);
	q.add(1);
	q.add(2);
	q.add(3);
	cout << q.GetSize() << endl; 
	cout << q.GetCapacity() << endl; 
	int z = 2; 
	q.remove(z);
	cout << q.GetSize() << endl;
	cout << q.GetCapacity() << endl;


	return 0; 
}