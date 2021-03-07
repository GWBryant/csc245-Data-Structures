#include <iostream>
#include "BinaryHeap.h"

using namespace std;

int main()
{
	BinaryHeap<char> PQ(50);

	for(char c = 'A'; c <= 'J'; c++)
	{
		PQ.insert(c);
	}

	//PQ.deleteMin();
	cout << "Printing left subtree of the root of heap: ";
	PQ.printLtSubtree();
	cout << "The height of the heap is: " << PQ.Height() << endl;
	cout << "The maximum value of the heap is: " << PQ.findMax() << endl;
	return 0;
}
