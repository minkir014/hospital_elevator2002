#include<iostream>
using namespace std;
#include "ArrayBag.h"
#include "LinkedQueue.h"
#include "LinkedHeap.h"

class OO {
private:
	int* a;

public:
	OO() {}
	OO(int* aheh) : a(aheh) {}
	void setItem(int* aa) {
		a = aa;
	}
	bool operator<(OO obj) { return *a < *(obj.a); }
	bool operator>(OO obj) { return *a > *(obj.a); }
	bool operator==(OO obj) { return *a == *(obj.a); }
	bool operator<=(OO obj) { return *a <= *(obj.a); }
	bool operator>=(OO obj) { return *a >= *(obj.a); }




};

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

	int** a = new int*[14];
	int abb[14] = {5, 10, 100, 150, 20, 200, -100, 150, 90, 20, 30, 30, -50, 300};

	OO oo[14];

	LinkedHeap<OO> LH;

	for (int i = 0; i < 14; i++) {
		a[i] = new int(abb[i]);
		oo[i].setItem(a[i]);
		LH.Insert(oo[i]);
	}

	for (int i = 13; i >= 0; i--)
	{
		*a[i] = abb[13 - i];
		//a[i] = new int(abb[i]);
	}

	LH.ReBuild();

	/*LH.Insert(5);
	LH.Insert(10);
	LH.Insert(100);
	LH.Insert(150);
	LH.Insert(20);
	LH.Insert(200);
	LH.Insert(-100);
	LH.Insert(150);
	LH.Insert(90);
	LH.Insert(20);
	LH.Insert(30);
	LH.Insert(30);
	LH.Insert(-50);
	LH.Insert(300);*/

	LH.Delete();
	LH.Delete();
	LH.Delete();




	return 0;
}