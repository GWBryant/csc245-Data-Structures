#include <cstddef> 
#include <iostream>

using namespace std;

template<class ItemType>
struct NodeType
{
	ItemType info;
	NodeType<ItemType>*	next;
	NodeType<ItemType>*	back;
};

template <class ItemType>		
DList<ItemType>::DList()		// Class constructor
{
    length = 0;
    head = NULL;
}

template <class ItemType>
DList<ItemType>::~DList   ()		
{
	// Post: List is empty; All items have been deallocated.
	makeEmpty();
}

template <class ItemType>
void DList<ItemType>::makeEmpty()
{
    	// Post: List is empty; all items have been deallocated.
    	while(head != NULL)
	{
		deleteLocation(last());
	}
}

template <class ItemType>
void DList<ItemType>::deleteItem (ItemType item)	
{
	//  Pre :  item to be deleted is passed in via parameter 
        // Post :  item is deleted if it exists in list 
	if(inList(item))
	{
		deleteLocation(location(item));
	}
	else
		cout << "Item is not in the list." << endl;
	

}

template <class ItemType>
bool DList<ItemType>::inList (ItemType item) const
{
	//  Pre :  item to be located is passed in via parameter 
        // Post :  function returns bool value if item is found
	NodeType<ItemType>* newNode = new NodeType<ItemType>;
	newNode = head;
	if(!isEmpty())
	{
		while(newNode != NULL)
		{
			if(item == newNode -> info)
				return true;
			else
				newNode = newNode -> next;
		}
		return false;
	}
 	else
		return false;
}

template <class ItemType>
bool DList<ItemType>::isEmpty() const		
{
	// Post : function returns true if list is empty, false otherwise
	if(length == 0)
		return true;
	else
		return false;
	
}

template <class ItemType>
void DList<ItemType>::print() const	
{
	// Pre  : List is not empty 
	// Post : Items in List have been printed to screen
	if(!isEmpty())
	{
		NodeType<ItemType>* newNode = new NodeType<ItemType>;
		newNode = head;
		while(newNode != NULL)
		{
			cout << newNode -> info << endl;
			newNode = newNode -> next;
		}
	}
	else
		cout << "Your list is empty" << endl;

}
	
template <class ItemType>
void DList<ItemType>::insertHead(ItemType item)	
{
	//  Pre : item to be inserted is passed in via parameter
        // Post : item is inserted at head of list;  Former first node is 
        //        linked back to this new one via double link;
        //        Length incremented;  Special case handled if list is empty 
	NodeType<ItemType>* newNode = new NodeType<ItemType>;
	newNode -> info = item;
	newNode -> back = NULL;

	if(head != NULL)
	{
		head -> back = newNode;
		newNode -> next = head;
	}	
	else
		newNode -> next = NULL;

	head = newNode;
	length++;
}

template <class ItemType>
void DList<ItemType>::appendTail(ItemType item)
{
	//  Pre :  item to be inserted is passed in via parameter
        // Post :  item is added to tail of list; Former last node
        //         is linked to this new one via double link 
	NodeType<ItemType>* newNode = new NodeType<ItemType>;
	newNode -> info = item;
	newNode -> next = NULL;

	if(head != NULL)
	{
		newNode -> back = last();
		last() -> next = newNode;
	}
	else
	{
		newNode -> back = NULL;
		head = newNode;
	}
	length++;

}

template <class ItemType>
int DList<ItemType>::lengthIs() const	
{
	// Post : Function returns current length of list
	return length;  
}

template <class ItemType>
NodeType<ItemType>* DList<ItemType>::location(ItemType item) const	
{
	//  Pre : item to be located is passed in via parameter 
        // Post : function returns address of item being searched for --
        //        if not found, NULL is returned
        NodeType<ItemType>* newNode = new NodeType<ItemType>;
	newNode = head;  
	if(inList(item))
	{	
		while(newNode != NULL)
		{
			if(item == (newNode -> info))
				return newNode;
			else
				newNode = newNode -> next;
		}
	}
	//else
		return NULL;	
}

template <class ItemType>
NodeType<ItemType>* DList<ItemType>::last() const	
{
	// Post : Function returns location of current last item in list
	NodeType<ItemType>* lastNode = new NodeType<ItemType>;
	if(length == 0)
	{
		cout << "Your list is empty." << endl;
		return NULL;
	}
	else if(length == 1)
		return head;
	else	
	{
		lastNode = head;
		for(int i = 0; i < length-1; i++)
		{
			lastNode = lastNode -> next;
		}
		return lastNode;
	}			
}

template <class ItemType>
void DList<ItemType>::deleteLocation (NodeType<ItemType>* delPtr)	
{

	//  Pre : Item to be deleted exits in list and its location
        //        is passed in via parameter
                   
	// Post : Location passed in is removed from list;  Length
        //        is decremented, and location is deallocated 

        // Special Cases Handled for Deleting Only One Item in List,
        // The Head Item of List, and the Tail Item of List
	if(length == 0)
	{
		cout << "Your list is empty." << endl;
	}
	else if(length == 1)
	{
		delete delPtr;
		delPtr = NULL;
		head = NULL;
		length--;
	}
	else if(delPtr == head)
	{
		head = head -> next;
		delete delPtr;
		delPtr = NULL;
		length--;
	}
	else if(delPtr == last())
	{
		(delPtr -> back) -> next = NULL;
		delete delPtr;
		delPtr = NULL;
		length--;
	}
	else
	{
		(delPtr -> next) -> back = delPtr -> back;
		(delPtr -> back) -> next = delPtr -> next;
		delete delPtr;
		delPtr = NULL;
		length--;
	}
}
