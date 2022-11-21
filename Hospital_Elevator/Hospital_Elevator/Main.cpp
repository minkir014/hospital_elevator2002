#include<iostream>
using namespace std;
#include "Queue.cpp"
int main() {
	// test queue
	LinkedQueue<int> q;
	cout << q.isEmpty() << endl; 
	int z;
	q.Peek(z);
	cout << z << endl; 
	q.Enqueue(4); 
	q.Enqueue(5); 
	q.Enqueue(7);
	
	q.Peek(z);
	cout << z << endl; 
	q.Dequeue(z); 
	cout << z << endl; 
	q.Peek(z);
	cout << z << endl;
	q.Dequeue(z);
	cout << z << endl;	
	cout << q.isEmpty() << endl; 
	q.Peek(z);
	cout << z << endl; 
	return 0; 
}