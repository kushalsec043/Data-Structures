#pragma once
#include <fstream>
#include "EmployeeRecord.h"

class EmployeeDatabase
{
private:
	EmployeeRecord* m_pRoot;
	fstream inFile;

	// prints data on all employees in the database 
	void printEmployeeRecords(EmployeeRecord* rt);

	//traverses all nodes in the tree and deletes them all
	void destroyTree(EmployeeRecord* rt);

public:
	// Default Constructor
	EmployeeDatabase();

	// Default Destructor
	~EmployeeDatabase();

	// Takes a pointer to a completed EmployeeRecord object and inserts the obj. into the tree
	bool addEmployee(EmployeeRecord* e);

	// Searches the tree and returns a pointer to the employee whose ID matches the func arg
	EmployeeRecord* getEmployee(int ID);

	// Searches the tree using an employee ID, if found it removes the node from the tree and returns it.
	EmployeeRecord* removeEmployee(int ID);

	// This function calls the private printEmployeeRecords() function which then
	// recursivly prints all nodes in the tree
	void printEmployeeRecords();

	// Reads and builds a database from a char array
	bool buildDatabase(char* dataFile);

	bool getNextLine(char* line, int lineLen);





};