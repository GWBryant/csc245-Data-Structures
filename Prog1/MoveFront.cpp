#include <iostream>
#include "dlist.h"

using namespace std;
typedef int ItemType;

void PrintMenu(char &sel);
void HeadInsert(DList<ItemType> &myList);
void TailInsert(DList<ItemType> &myList);
void AccessItem(DList<ItemType> &myList);
void Delete(DList<ItemType> &myList);
void PrintList(DList<ItemType> &myList);
void PrintLength(DList<ItemType> &myList);
void FindandMove(DList<ItemType> &myList, int item);

int main()
{
	DList<ItemType> list;
	char sel;
	
	//keep user in menu until they quit the progam
	do
	{
		PrintMenu(sel);
		switch (toupper(sel))
		{
			case 'H' :   HeadInsert(list);  break;
			case 'T' :   TailInsert(list);  break;
			case 'A' :   AccessItem(list);  break;
			case 'D' :   Delete(list);  break;
			case 'P' :   PrintList(list); break;
			case 'L' :   PrintLength(list); break;
			case 'Q' :   cout << "\tExiting Program...\n"; break;
			default  :   cout << "\tError.  Try Again." << endl;	
		}
	}while(toupper(sel) != 'Q');
}

//print menu and take user input
void PrintMenu(char &sel)
{
	cout << "-------------------------------" << endl; 
	cout << "		menu		" << endl;
	cout << "-------------------------------" << endl;
	cout << "H: Insert item at head of list" << endl;
	cout << "T: Insert item at tail of list" << endl;
	cout << "A: Access item from list" << endl;
	cout << "D: Delete item from list" << endl;
	cout << "P: Print list" << endl;
	cout << "L: Print length of list" << endl;
	cout << "Q: Quit program" << endl;
	cout << "-------------------------------" << endl;
	cout << "Enter choice: ";
	cin >> sel; 
}	

//insert item at the head of the list
void HeadInsert(DList<ItemType> &myList)
{
	int item;
	cout << "\v\tItem to be inserted onto head of list: ";
	cin >> item;
	if(!myList.inList(item))
		myList.insertHead(item);
	else
		cout << "\tItem already in list. No duplicates allowed." << endl;
}

//insert item at the tail of the list
void TailInsert(DList<ItemType> &myList)
{
	int item;
	cout << "\v\tItem to be inserted onto head of list: ";
	cin >> item;
	if(!myList.inList(item))
		myList.appendTail(item);
	else
		cout << "\tItem already in list, No duplicates allowed." << endl;
}

//Access item from the list
void AccessItem(DList<ItemType> &myList)
{
	if(myList.lengthIs() > 0)
	{
		int item;
		cout << "\v\tItem to be accessed: ";
		cin >> item;
		FindandMove(myList,item);
	}
	else
		cout << "\v\tList is empty" << endl;
}

//delete item from list
void Delete(DList<ItemType> &myList)
{
	if(myList.lengthIs() > 0)
	{
		int item;
		cout << "\v\tItem to be deleted: ";
		cin >> item;
		if(myList.inList(item))
		{
			myList.deleteItem(item);
			cout << "\tItem successfully deleted from list." << endl;
		}
		else
			cout << "\tItem could not be found in list" << endl;
	}
	else
		cout << "\v\tList is empty" << endl; 
}

//print list
void PrintList(DList<ItemType> &myList)
{
	if(myList.lengthIs() > 0)
	{
		myList.print();
	}
	else
		cout << "\v\tList is empty" << endl;
}

//print the length of the list
void PrintLength(DList<ItemType> &myList)
{
	if(myList.lengthIs() > 0)
		cout << "\tLength of list: " << myList.lengthIs() << endl;
	else
		cout << "\tList is empty" << endl;
}

//find item and move it to the front of the list
void FindandMove(DList<ItemType> &myList,int item)
{
	if(myList.inList(item))
	{
		myList.deleteItem(item);
		myList.insertHead(item);
		cout << "\tItem was found and moved to front of list" << endl;
	}
	else
		cout << "\tItem could not be found in list" << endl;
}
