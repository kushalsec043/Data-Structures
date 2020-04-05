#pragma once
#include "CustomerList.h"

class EmployeeRecord
{
private:
	int    m_iEmployeeID;
	char   m_sLastName[32];
	char   m_sFirstName[32];
	int    m_iDeptID;
	double m_dSalary;
	CustomerList* m_pCustomerList;


public:

	//Public pointers 
	EmployeeRecord* m_pLeft;
	EmployeeRecord* m_pRight;

	// This function sets the pointer to a CustomerList object to NULL. 
	// This function is used by the removeEmployee() function in the EmployeeDatabase class. 
	void removeCustomerList();

	// This function deletes the CustomerList object and sets the pointer to a CustomerList 
	// object to NULL. It is used by the removeEmployee() function in the EmployeeDatabase class.
	void destroyCustomerList();

	//-----------------------------------------------------------------------------------------------------------------//

			// Constructor that sets member variables to initial values
	EmployeeRecord();

	// Constructor that sets member variables to the values passed into the function
	EmployeeRecord(int ID, char* fName, char* lName, int dept, double sal);

	// Destructor that cleans up and deallocates any memory/pointers
	~EmployeeRecord();

	// Returns int value stored in the member var m_iEmployeeID
	int getID();

	// A call to this function will copy the member var m_iDeptID into the int variable referenced by the function argument
	int getDept();

	// Copies the member var m_dSalary into the int variable pointed to by the function argument.
	double getSalary();

	// Sets the member var m_iEmployeeID to the value of its argument
	void setID(int ID);

	// Copies the member vars m_sFirstName and m_sLastName into the character arrays pointed to by the function arguments
	void getName(char* fName, char* IName);

	// Copies the function arguments into the member variables m_sFirstName and m_sLastName
	void setName(char* fName, char* IName);

	// Copies the function argument into the member variable m_iDeptID
	void setDept(int d);

	// Copies the function argument into the member variable m_dSalary
	void setSalary(double sal);

	// prints the data found in the employee's record
	void printRecord();

	// This function returns the pointer to the EmployeeRecord's CustomerList object.
	CustomerList* getCustomerList();

};
