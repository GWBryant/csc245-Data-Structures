#include <iostream>
#include "bst.h"

using namespace std;

int main()
{
	BinarySearchTree<int> T(0);
	
	T.insert(6);
	T.insert(2);
	T.insert(8);
	T.insert(1);
	T.insert(4);
	T.insert(3);
	T.remove(2);
	T.remove(6);

	cout << "Post order of tree: " << endl;
	T.postOrder();
	/*
	cout << "Height of tree: ";
	cout << T.height() << endl;
	cout << "Number of leaves: ";
	cout << T.numLeaves() << endl;
	T.isBalanced();
	T.insert(9);
	T.isBalanced();
*/
	return 0;
}
