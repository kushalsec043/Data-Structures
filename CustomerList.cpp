#include <iostream>
#include "CustomerList.h"
#include "Store.h"

using namespace std;

//----------------------------
// Default Class Constructor
//----------------------------
CustomerList::CustomerList()
{
	cout << "Constructor List" << endl;
}

//--------------------------------
// Parameterized Class Constructor
//--------------------------------
CustomerList::CustomerList(int ID, char* fName, char* lName, int dept, double sal)
{
}

//----------------------------
// Default Class Destructor
//----------------------------
CustomerList::~CustomerList()
{
	cout << "Destructor" << endl;
}

//-------------------------------------------------------------------------------------------------
// This function takes a pointer to a Store object which already contains all data on a store. 
// It will then insert the Store object into the linked list in order, sorted by the store ID. 
// It then returns TRUE if the Store was successfully added to the list.
//-------------------------------------------------------------------------------------------------
bool CustomerList::addStore(Store* s)
{

	Store* temp, * back;

	//checking to see if the memory allocation failed
	if (s == NULL) return false;

	//Initializing the store next to null
	s->m_pNext = nullptr;

	//checking to see if the list is empty
	if (m_pHead == nullptr)
	{
		cout << "The new store is empty" << endl;
		m_pHead = s;
		return true;
	}
	else
	{
		temp = m_pHead;
		back = NULL;
		// Cycles throught the list until it reaches the correct place
		while ((temp != NULL) && (temp->getStoreID() < s->getStoreID()))
		{
			back = temp;
			temp = temp->m_pNext;
		}
		// Checks to see if adding at the head of the list
		if (back == NULL)
		{
			s->m_pNext = m_pHead;
			m_pHead = s;
			return true;
		}
		// this is inserting somewhere else in the list
		else
		{
			back->m_pNext = s;
			s->m_pNext = temp;

		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
// This function takes an integer store ID as an argument.
// It'll search the list, locate the Store object with that ID if one is present, remove it from the list and return the Store object.
// The function will return NULL if it failed to find the Store in the list.
//-------------------------------------------------------------------------------------------------
Store* CustomerList::removeStore(int ID)
{
	Store* temp, * back;

	// Checks for the empty store
	if (ID == NULL) return NULL;

	// Searches the list for the store that needs to be deleted
	temp = m_pHead;
	back = NULL;

	while ((temp != NULL) && (ID != temp->getStoreID()))
	{
		back = temp;
		temp = temp->m_pNext;
	}

	// Checks to see if the store was found
	if (temp == NULL) return NULL; // Store was not found so it returns NULL
	else if (back == NULL)
	{
		m_pHead = m_pHead->m_pNext;
		return temp;
	}
	else // Deletes a node somewhere else in the list
	{
		back->m_pNext = temp->m_pNext;
		return temp;
	}
	return NULL;
}

//-------------------------------------------------------------------------------------------------
// This function takes an integer store ID. 
// It'll then search the list, locate the Store object, if present, and return a pointer to the Store object. 
// It shall return NULL if the Store was not found in the list.
//-------------------------------------------------------------------------------------------------
Store* CustomerList::getStore(int ID)
{
	Store* temp;

	temp = m_pHead;

	while ((temp != NULL) && (ID != temp->getStoreID()))
	{
		temp = temp->m_pNext;
	}

	// If item not found or list is empty return false
	if (temp == NULL) return NULL;
	else
	{
		Store* retItem = new Store;
		*retItem = *temp;	     // Block copies the entire structure 
		retItem->m_pNext = NULL; // Clears this pointer
		return retItem;	         // Returns the copy
	}
}

//-------------------------------------------------------------------------------------------------
// This function takes a list of arguments defining changes in the store data. 
// The first argument gives the store ID. 
// The remaining arguments are char arrays containing the new data on that store. 
// The function will search the list and locate the store then update all data for that store. 
// The function will return TRUE if it successfully updated the data or FALSE if it failed to find the store.
//-------------------------------------------------------------------------------------------------
bool CustomerList::updateStore(int ID, char* name, char* addr, char* city, char* st, char* zip)
{
	Store* temp;

	temp = m_pHead;

	while ((temp != NULL) && (ID != temp->getStoreID()))
	{
		temp = temp->m_pNext;
	}

	// If item not found or list is empty return false
	if (temp == NULL) return false;
	else
	{
		temp->setStoreID(ID);
		temp->setStoreName(name);
		temp->setStoreAddress(addr);
		temp->setStoreCity(city);
		temp->setStoreState(st);
		temp->setStoreZip(zip);
	}
	return true;
}

//-----------------------------------------------------------------
// This function prints all data on each store in the list.
//-----------------------------------------------------------------
void CustomerList::printStoresInfo()
{
	Store* temp;

	if (m_pHead == NULL)	// Report no items in the list
	{
		cout << "\t List is currently empty.\n";
	}
	else
	{
		temp = m_pHead;
		while (temp != NULL)
		{
			printStoresInfo();
			temp = temp->m_pNext;
		}
	}
	return;
}


