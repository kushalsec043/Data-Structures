//--------------------------------------------------------------------------
// Programming assignment 3 demonstration program
// Author: Dr. Rick Coleman
// Date: April 3, 2006
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// Programming assignment 2 demonstration program
// Author: Dr. Rick Coleman
//--------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include "EmployeeDatabase.h"
#include "EmployeeRecord.h"
#include "CustomerList.h"
#include "Store.h"
using namespace std;

#define GRADING
//#define DEBUG

int main(void)
{
	char FILENAME[64] = "Prog3Data.txt";
	char fName[64], lName[64];
	EmployeeDatabase* empDB;
	EmployeeRecord* empRec;
	char ans[8];

	double grade = 0.0;
	double maxGrade = 0.0;

	cout << "========================================================================\n";
	cout << "              DEMONSTRATION OF PROGRAMMING ASSIGNMENT 3\n";
	cout << "========================================================================\n\n";
	cout << "Instantiating EmployeeDatabase.\n";
	cout.flush();
	empDB = new EmployeeDatabase();
	cout << "Building database.\n";
	empDB->buildDatabase(FILENAME);
	cout.flush();

	// Print all records
	cout.flush();
	empDB->printEmployeeRecords();
#ifdef GRADING
	cout.flush();
	cout << "\nIs DB printout OK? (Press y then Enter if OK, or press any other key then Enter if not.)\n";
	cin >> ans;
	if (strcmp(ans, "y") == 0)
	{
		grade += 3.0; // 4 points for successful building of database and printout
	}
	maxGrade += 3.0;
	cout << "Grade = " << grade << " out of " << maxGrade << "\n";
#else
	cout.flush();
	cout << "\nEmployee database built. Press Enter to continue.\n";
	cin.getline(ans, 8, '\n');
#endif

	// Test the search function
	cout << "\n========== Testing search function ==========\n\n";
	cout.flush();
	// Test search for root
	cout << "Searching for employee 5678 ... ";
	cout.flush();
	empRec = empDB->getEmployee(5678);
	if (empRec != NULL)
	{
		cout << "success\n";
		cout.flush();
		//		empRec->setName("Just", "Testing");
		empRec->getName(fName, lName);
		cout << "getName returned " << fName << " " << lName;
		cout.flush();
#ifdef GRADING
		if ((strcmp(fName, "Sue") == 0) && (strcmp(lName, "Smythe") == 0))
			grade += 2.0;
		else
			cout << ", but name in the record is not correct.";
		maxGrade += 2.0;
		cout << "Grade = " << grade << " out of " << maxGrade << "\n";
		cout.flush();
#endif
	}
	else
	{
		cout << "failed to find the record.";
		cout.flush();
		maxGrade += 2.0;
	}
	cout << "\n\n";
	cout.flush();

	// Test search for a leaf
	cout << "Searching for employee 9876 ... ";
	cout.flush();
	empRec = empDB->getEmployee(9876); // Get the root
	if (empRec != NULL)
	{
		cout << "success\n";
		cout.flush();
		empRec->getName(fName, lName);
#ifdef GRADING
		if ((strcmp(fName, "Harry") == 0) && (strcmp(lName, "Potter") == 0))
			grade += 2.0;
		else
			cout << ", but name in the record is not correct.";
		maxGrade += 2.0;
		cout << "Grade = " << grade << " out of " << maxGrade << "\n";
		cout.flush();
#endif
	}
	else
	{
		cout << "failed to find the record.";
		maxGrade += 2.0;
	}
	cout << "\n\n";
	cout.flush();

	// Test search for ID known to not be in the database
	cout << "Searching for employee 9999 (known to not be in the database) ...\n";
	cout.flush();
	empRec = empDB->getEmployee(9999); // Try to get one not there
	if (empRec == NULL)
	{
		cout << "   Success, no such employee found\n";
#ifdef GRADING
		grade += 2.0;
		maxGrade += 2.0;
		cout << "Grade = " << grade << " out of " << maxGrade << "\n";
#else
		cout.flush();
		cout << "\nTesting of search function completed. Press Enter to continue.\n";
		cout.flush();
		cin.getline(ans, 8, '\n');
#endif
	}
	else
	{
		cout << "failed to find the record.";
		cout.flush();
		maxGrade += 2.0;
	}
	cout << "\n\n";
	cout.flush();

	// Test the delete function
	cout << "\n========== Testing the delete function ==========\n\n";
	cout.flush();

	// Test 0: try to remove a node not in the tree
	cout << "Trying to remove a node not in the tree.\n";
	cout.flush();
	empRec = empDB->removeEmployee(9999);
	if (empRec != NULL)
	{
		cout << "Failed. Actually returned node " << (empRec->getID()) << endl << endl;
		cout.flush();
		delete empRec;
	}
	else
	{
		cout << "Successfully reported failure to find a non-existant node.\n\n";
#ifdef GRADING
		grade += 1.0;
		maxGrade += 1.0;
		cout << "Grade = " << grade << " out of " << maxGrade << "\n";
#endif
	}
	cout.flush();

	// Test 1: remove leaf
	cout << "Removing leaf node not root.\n";
	cout.flush();
	empRec = empDB->removeEmployee(8765);
	if ((empRec != NULL) && empRec->getID() == 8765)
	{
		cout << "Successfully removed leaf node not root.\n\n";
		cout.flush();
#ifdef GRADING
		grade += 1.0;
		maxGrade += 1.0;
		cout << "Grade = " << grade << " out of " << maxGrade << "\n\n";
#endif
		delete empRec;
	}
	else
	{
		cout << "Failed to remove leaf node.\n\n";
		maxGrade += 1.0;
	}
	cout.flush();

	// Test 2: remove node with 2 children not root
	cout << "Removing node not root with two children.\n";
	cout.flush();
	empRec = empDB->removeEmployee(7890);
	if ((empRec != NULL) && empRec->getID() == 7890)
	{
		cout << "Successfully removed node not root with two children\n\n";
		cout.flush();
#ifdef GRADING
		grade += 2.0;
		maxGrade += 2.0;
		cout << "Grade = " << grade << " out of " << maxGrade << "\n\n";
		cout.flush();
#endif
		delete empRec;
	}
	else
	{
		cout << "Failed to delete node not root with two children\n\n";
		maxGrade += 2.0;
	}
	cout.flush();

	// Set up for next test
	cout << "Removing another leaf node to set up for next test.\n\n";
	cout.flush();
	empRec = empDB->removeEmployee(4567);
	if (empRec != NULL)
		delete empRec;

	// Test 3: remove node with one child on right, not root
	cout << "Removing node not root with one child on right.\n";
	cout.flush();
	empRec = empDB->removeEmployee(1234);
	if ((empRec != NULL) && empRec->getID() == 1234)
	{
		cout << "Successfully removed node not root with one child on the right\n\n";
		cout.flush();
#ifdef GRADING
		grade += 2.0;
		maxGrade += 2.0;
		cout << "Grade = " << grade << " out of " << maxGrade << "\n\n";
		cout.flush();
#endif
		delete empRec;
	}
	else
	{
		cout << "Failed to remove node not root with one child on right\n\n";
		maxGrade += 2.0;
	}
	cout.flush();

	// Test 4: remove node with one child on left, not root
	cout << "Removing node not root with one child on left.\n";
	cout.flush();
	empRec = empDB->removeEmployee(3456);
	if ((empRec != NULL) && empRec->getID() == 3456)
	{
		cout << "Successfully removed node not root with one child on the left\n\n";
		cout.flush();
#ifdef GRADING
		grade += 2.0;
		maxGrade += 2.0;
		cout << "Grade = " << grade << " out of " << maxGrade << "\n\n";
#endif
		delete empRec;
	}
	else
	{
		cout << "Failed to remove node not root with one child on left\n\n";
		maxGrade += 2.0;
	}
	cout.flush();

	// Test 5: remove root node with 2 children
	cout << "Removing the root node with 2 children.\n";
	cout.flush();
	empRec = empDB->removeEmployee(5678);
	if ((empRec != NULL) && empRec->getID() == 5678)
	{
		cout << "Successfully removed root\n\n";
		cout.flush();
#ifdef GRADING
		grade += 2.0;
		maxGrade += 2.0;
		cout << "Grade = " << grade << " out of " << maxGrade << "\n\n";
#endif
		delete empRec;
	}
	else
	{
		cout << "Failed to delete the root\n\n";
		maxGrade += 2.0;
	}
	cout.flush();

	// Test 6: remove root node with 1 child on right
	cout << "Removing the root node with 1 child on right.\n";
	cout.flush();
	empRec = empDB->removeEmployee(2345);
	EmployeeRecord* savRec = NULL;
	if ((empRec != NULL) && empRec->getID() == 2345)
	{
		cout << "Successfully removed root with one child on right.\n\n";
		cout.flush();
#ifdef GRADING
		grade += 2.0;
		maxGrade += 2.0;
		cout << "Grade = " << grade << " out of " << maxGrade << "\n\n";
		cout << "Saving node 2345 just removed for reinsertion to set up for another test.\n";
#endif
		savRec = empRec;
		savRec->m_pLeft = savRec->m_pRight = NULL;
	}
	else
	{
		cout << "Failed to delete the root\n\n";
		maxGrade += 2.0;
	}
	cout.flush();

	// Set up for next test
	cout << "Removing 2 other nodes and adding 2345 back to set up for next test.\n\n";
	cout.flush();
	empRec = empDB->removeEmployee(7654);
	if (empRec != NULL)
		delete empRec;
	empRec = empDB->removeEmployee(9876);
	if (empRec != NULL)
		delete empRec;
	empDB->addEmployee(savRec);

	// Test 7: remove root node with 1 child on left
	cout << "Removing the root node with 1 child on left.\n";
	cout.flush();
	empRec = empDB->removeEmployee(6789);
	if ((empRec != NULL) && empRec->getID() == 6789)
	{
		cout << "\n\nSuccessfully removed root with one child on left.\n\n";
		cout.flush();
#ifdef GRADING
		grade += 2.0;
		maxGrade += 2.0;
		cout << "Grade = " << grade << " out of " << maxGrade << "\n";
#endif
	}
	else
	{
		cout << "\n\nFailed to delete the root\n";
		maxGrade += 2.0;
	}
	cout.flush();

	// Test 8: remove root node as leaf (last in tree).
	cout << "Removing the root node as a leaf (last in tree).\n";
	cout.flush();
	empRec = empDB->removeEmployee(2345);
	if ((empRec != NULL) && empRec->getID() == 2345)
	{
		cout << "\n\nSuccessfully removed root as last in tree.\n\n";
		cout.flush();
#ifdef GRADING
		grade += 2.0;
		maxGrade += 2.0;
		cout << "Grade = " << grade << " out of " << maxGrade << "\n\n";
#endif
	}
	else
	{
		cout << "\n\nFailed to delete the root\n";
		maxGrade += 2.0;
	}
	cout.flush();

	cout << "========================================================================\n\n";
#ifdef GRADING
	cout << "Final Grade = " << grade << " out of " << maxGrade << "\n";
#endif
	//cout.flush();
	//inFile.close();

	cout << "========================================================================\n";
	cout << "            END DEMONSTRATION OF PROGRAMMING ASSIGNMENT 3\n";
	cout << "========================================================================\n\n";
	cout.flush();
	cout << "Press Enter to continue...";
	getc(stdin);

	return 0;
}

////--------------------------------------------/
