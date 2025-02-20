// Fig. 21.4: list.h
// // Template List class definition.
// Tevyn Payne
// COP 3330 Section 7
#ifndef LIST_H
#define LIST_H

#include <iostream>

using std::cout;

#include <new>
#include "listnode.h"  // ListNode class definition

template< class NODETYPE >
class List 
{

public:
	List();      // constructor
	~List();     // destructor
	void insertAtFront( const NODETYPE & );
	void insertAtBack( const NODETYPE & );
	bool removeFromFront( NODETYPE & );
	bool removeFromBack( NODETYPE & );
	bool isEmpty() const;
	void print() const;

	void insertMiddle (const NODETYPE & ,int);
	bool removeMiddle (NODETYPE & ,int);	
	int  count() const;
private:
	ListNode< NODETYPE > *firstPtr;  // pointer to first node
	ListNode< NODETYPE > *lastPtr;   // pointer to last node

// utility function to allocate new node
	ListNode< NODETYPE > *getNewNode( const NODETYPE & );
}; // end class List

// default constructor
template< class NODETYPE >
List< NODETYPE >::List() 
	: firstPtr( 0 ), 
	lastPtr( 0 ) 
{ 
// empty body

} // end List constructor

// destructor
template< class NODETYPE >
List< NODETYPE >::~List()
{
	if ( !isEmpty() )     // List is not empty
	{
		ListNode< NODETYPE > *currentPtr = firstPtr;
		ListNode< NODETYPE > *tempPtr;

		while ( currentPtr != 0 )         // delete remaining nodes
		{  
			tempPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
			delete tempPtr;

		}

	}

} // end List destructor

template< class NODETYPE >
void List< NODETYPE >::insertAtFront( const NODETYPE &value )
{
	ListNode< NODETYPE > *newPtr = getNewNode( value );

	if ( isEmpty() )  // List is empty
		firstPtr = lastPtr = newPtr;

	else   // List is not empty
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;

	} // end else

} // end function insertAtFront

template< class NODETYPE >
void List< NODETYPE >::insertAtBack( const NODETYPE &value )
{
	ListNode< NODETYPE > *newPtr = getNewNode( value );

	if ( isEmpty() )  // List is empty
		firstPtr = lastPtr = newPtr;

	else   // List is not empty
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;

	} // end else

} // end function insertAtBack

// delete node from front of list
template< class NODETYPE >
bool List< NODETYPE >::removeFromFront( NODETYPE &value )
{
	if ( isEmpty() )  // List is empty
		return false;  // delete unsuccessful

	else 
	{  
		ListNode< NODETYPE > *tempPtr = firstPtr;

		if ( firstPtr == lastPtr )
			firstPtr = lastPtr = 0;
		else
			firstPtr = firstPtr->nextPtr;

		value = tempPtr->data;  // data being removed
		delete tempPtr;

		return true;  // delete successful

	} // end else

} // end function removeFromFront
// delete node from back of list
template< class NODETYPE >
bool List< NODETYPE >::removeFromBack( NODETYPE &value )
{
	if ( isEmpty() )
		return false;  // delete unsuccessful

	else 
	{
		ListNode< NODETYPE > *tempPtr = lastPtr;

	if ( firstPtr == lastPtr )
		firstPtr = lastPtr = 0;
	else 
	{
		ListNode< NODETYPE > *currentPtr = firstPtr;

		// locate second-to-last element
		while ( currentPtr->nextPtr != lastPtr )
			currentPtr = currentPtr->nextPtr;

			lastPtr = currentPtr;
			currentPtr->nextPtr = 0;

	} // end else

	value = tempPtr->data;
	delete tempPtr;

	return true;  // delete successful

	} // end else

} // end function removeFromBack

// is List empty?
template< class NODETYPE > 
bool List< NODETYPE >::isEmpty() const 
{ 
return firstPtr == 0; 

} // end function isEmpty

// return pointer to newly allocated node
template< class NODETYPE >
ListNode< NODETYPE > *List< NODETYPE >::getNewNode( 
const NODETYPE &value )
{
	return new ListNode< NODETYPE >( value );

} // end function getNewNode

// display contents of List
template< class NODETYPE >
void List< NODETYPE >::print() const
{
	if ( isEmpty() )
	{
		cout << "The list is empty\n\n";
		return;

	} // end if

	ListNode< NODETYPE > *currentPtr = firstPtr;

	cout << "The list is: ";

	while ( currentPtr != 0 ) 
	{
		cout << currentPtr->data << ' ';
		currentPtr = currentPtr->nextPtr;

	} // end while

	cout << "\n\n";

} // end function print


template< class NODETYPE >
void List< NODETYPE >::insertMiddle( const NODETYPE &value, int mid )
{
	ListNode< NODETYPE > *currentPtr = firstPtr;
	ListNode< NODETYPE > *newPtr = getNewNode( value );


	if ( isEmpty() )  // List is empty
		firstPtr = lastPtr = newPtr;

	else if(mid <= 1)
		insertAtFront(value);

	else
	{
		for(int i = 0; i < mid-2; i++)
		{

			currentPtr = currentPtr->nextPtr;

			if( currentPtr == 0)
			{
				insertAtBack(value);
				return;
			}


		}//end of for loop

		newPtr->nextPtr = currentPtr->nextPtr;     // point new node to currents  next node
		currentPtr->nextPtr  = newPtr;       // point current pointer at new node now

	}//end of else statement
}//end of insert middle function

template< class NODETYPE >
bool List< NODETYPE >::removeMiddle (NODETYPE & value ,int midl)
{

	ListNode< NODETYPE > *tempPtr = firstPtr;
	ListNode< NODETYPE > *currentPtr = firstPtr;

	if ( isEmpty() )
		return false;  // delete unsuccessful

	else
	{   

		if(midl >= count())
		{
			removeFromBack(value);
			return true;
		}

		if(midl == 2)
		{
			tempPtr = tempPtr -> nextPtr;
			currentPtr -> nextPtr = tempPtr -> nextPtr;
			value = tempPtr -> data;
			delete tempPtr;
			return true;
		}

		for(int i =0; i < midl - 2; i++)
		{
			currentPtr = currentPtr->nextPtr;
			tempPtr = currentPtr -> nextPtr;
		}


		if ( midl <= 1)
		{   
			removeFromFront(value);
			return true;
		}
		currentPtr -> nextPtr  = tempPtr->nextPtr;

		value = tempPtr->data;

		delete tempPtr;

		return true;

	}//end of else

}

template< class NODETYPE >
int List< NODETYPE >::count() const	//count the amount of nodes in the list
{
	ListNode< NODETYPE > *currentPtr = firstPtr;

	int count = 0;

	while(currentPtr != NULL)
	{
		currentPtr = currentPtr->nextPtr;
		count++;
	}

	return count;
}
#endif

/**************************************************************************
* (C) Copyright 1992-2003 by Deitel & Associates, Inc. and Prentice      *
* Hall. All Rights Reserved.                                             *
*                                                                        *
* DISCLAIMER: The authors and publisher of this book have used their     *
* best efforts in preparing the book. These efforts include the          *
* development, research, and testing of the theories and programs        *
* to determine their effectiveness. The authors and publisher make       *
* no warranty of any kind, expressed or implied, with regard to these    *
* programs or to the documentation contained in these books. The authors *
* and publisher shall not be liable in any event for incidental or       *
* consequential damages in connection with, or arising out of, the       *
* furnishing, performance, or use of these programs.                     *
*************************************************************************/
