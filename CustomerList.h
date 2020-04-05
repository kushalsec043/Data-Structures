#pragma once
#include "Store.h"

class CustomerList
{
private:
	Store* m_pHead;
	int ID;

public:

	CustomerList();		        // constructor
	CustomerList(int ID, char* fName, char* lName, int dept, double sal);
	~CustomerList();			// destructor
	bool addStore(Store* s);
	bool updateStore(int ID, char* name, char* addr, char* city, char* st, char* zip);
	void printStoresInfo();
	Store* removeStore(int ID);
	Store* getStore(int ID);

};
