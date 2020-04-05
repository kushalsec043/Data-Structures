#include <iostream>
#include <fstream>
#include "CustomerList.h"
#include "EmployeeRecord.h"

using namespace std;


// This function sets the pointer to a CustomerList object to NULL. 
void EmployeeRecord::removeCustomerList()
{
	m_pCustomerList = NULL;
}

void EmployeeRecord::destroyCustomerList()
{
	delete m_pCustomerList;
	m_pCustomerList = NULL;
}

//Default class constructor
EmployeeRecord::EmployeeRecord()
{
	//cout << "constructor one check" << endl;
	m_iEmployeeID = 0;
	m_sLastName[32] = {};
	m_sFirstName[32] = {};
	m_iDeptID = 0;
	m_dSalary = 0.0;
	CustomerList* m_pCustomerList = new CustomerList();
}

//Overloaded constructor
EmployeeRecord::EmployeeRecord(int ID, char* fName, char* lName, int dept, double sal)
{
	//cout << "constructor two check" << endl;
	m_iEmployeeID = ID;
	strcpy(m_sFirstName, fName);
	strcpy(m_sLastName, lName);
	m_iDeptID = dept;
	m_dSalary = sal;
	CustomerList* m_pCustomerList = new CustomerList(ID, fName, lName, dept, sal);
}

// Destructor that cleans up and deallocates any memory/pointers
EmployeeRecord::~EmployeeRecord()
{
	if (m_pCustomerList != NULL)
	{
		delete m_pCustomerList;
	}

	//cout << "destructor check" << endl;
}

// Returns int value stored in the member var m_iEmployeeID
int EmployeeRecord::getID()
{
	//cout << "getID() check" << endl;
	cout << "EAHAAHAHH" << endl;
	cout << "ID: " << m_iEmployeeID << endl;
	return m_iEmployeeID;
}

// Copies the member var m_dSalary into the int variable pointed to by the function argument.
double EmployeeRecord::getSalary()
{
	//cout << "void getSalary(double *sal) check" << endl;
	return m_dSalary;
	//cout << *sal << endl;

}

// A call to this function will copy the member var m_iDeptID into the int variable referenced by the function argument
int EmployeeRecord::getDept()
{
	//cout << "getDept(int& d) check" << endl;
	return m_iDeptID;
}

// Sets the member var m_iEmployeeID to the value of its argument
void EmployeeRecord::setID(int ID)
{
	//cout << "setID(int ID) check" << endl;
	m_iEmployeeID = ID;
	return;
}

// Copies the member vars m_sFirstName and m_sLastName into the character arrays pointed to by the function arguments
void EmployeeRecord::getName(char* fName, char* lName)
{
	//cout << "getName(char *fName, char *IName) check" << endl;
	strcpy(fName, m_sFirstName);
	strcpy(lName, m_sLastName);
	//cout << m_sFirstName << m_sLastName << endl;

	return;
}

// Copies the function arguments into the member variables m_sFirstName and m_sLastName
void EmployeeRecord::setName(char* fName, char* lName)
{
	//cout << "setName(char *fName, char *IName) check" << endl;
	strcpy(m_sFirstName, fName);
	strcpy(m_sLastName, lName);

	return;
}


// Copies the function argument into the member variable m_iDeptID
void EmployeeRecord::setDept(int d)
{
	//cout << "setDept(int d) check" << endl;
	m_iDeptID = d;

	return;
}


// Copies the function argument into the member variable m_dSalary
void EmployeeRecord::setSalary(double sal)
{
	//cout << "void setSalary(double sal) check" << endl;
	m_dSalary = sal;

	return;
}

// prints the data found in the employee's record
void EmployeeRecord::printRecord()
{
	//cout << "void printRecord() check" << endl;
	cout << "Employee Recorddd" << endl;
	cout << "ID: " << m_iEmployeeID << endl;
	cout << "First name: " << m_sFirstName << endl;
	cout << "Last name: " << m_sLastName << endl;
	cout << "Department ID: " << m_iDeptID << endl;
	cout << "Salary: " << m_dSalary << endl;

	return;
}

CustomerList* EmployeeRecord::getCustomerList()
{
	cout << "getCustomerList() test" << endl;
	return nullptr;
}

