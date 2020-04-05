#include "EmployeeDatabase.h"
#include "EmployeeRecord.h"

using namespace std;

void EmployeeDatabase::printEmployeeRecords(EmployeeRecord* rt)
{
	if (rt != NULL)
	{
		printEmployeeRecords(rt->m_pLeft);
		printEmployeeRecords(rt->m_pRight);
	}

	//cout << "printEmployeeRecords" << endl;
}

void EmployeeDatabase::destroyTree(EmployeeRecord* rt)
{
	if (rt == NULL) return;  // This is to test if there is nothing to clear
	if (rt->m_pLeft != NULL) destroyTree(rt->m_pLeft); // this clears left sub-tree
	if (rt->m_pRight != NULL) destroyTree(rt->m_pRight); // this clears the right sub-tree
	delete rt;	// This destroys the node
	return;
	//cout << "destroyTree" << endl;
}

EmployeeDatabase::EmployeeDatabase()
{
	m_pRoot = NULL;
	return;

	//cout << "constructor" << endl;
}

EmployeeDatabase::~EmployeeDatabase()
{
	destroyTree(m_pRoot); // recursivly destroys the tree's data
	return;

	//cout << "destructor" << endl;
}

bool EmployeeDatabase::addEmployee(EmployeeRecord* e)
{
	EmployeeRecord* temp;
	EmployeeRecord* back;

	temp = m_pRoot;
	back = NULL;

	while (temp != NULL) // This loops until temp is at the end of the tree
	{
		back = temp;
		if (e->getID() < temp->getID())
			temp = temp->m_pLeft;
		else // seeing which node to go to next
			temp = temp->m_pRight;
	}

	// This attaches the new node to the node that is back pointing to 
	if (back == NULL) // This attaches as root node in a new tree 
		m_pRoot = e;
	else
	{
		if (e->getID() < back->getID())
			back->m_pLeft = e;
		else
			back->m_pRight = e;
	}
	return(true);

	//cout << "addEmployee" << endl;
	return false;
}

EmployeeRecord* EmployeeDatabase::getEmployee(int ID)
{
	// Variables used in the function 
	EmployeeRecord* dupNode;
	EmployeeRecord* temp;

	temp = m_pRoot;
	while ((temp != NULL) && (temp->getDept() != ID))
	{
		if (ID < temp->getDept())
			temp = temp->m_pLeft;  // Search key comes before this node.
		else
			temp = temp->m_pRight; // Search key comes after this node 
	}
	if (temp == NULL)
		return temp;	// Search key not found
	else
		dupNode = new EmployeeRecord();
	*dupNode = *temp;			// Copies the data structure
	dupNode->m_pLeft = NULL;	// Sets the pointers to NULL
	dupNode->m_pRight = NULL;

	return dupNode;   // Found it so returns a duplicate

//cout << "getEmployee" << endl;

}

EmployeeRecord* EmployeeDatabase::removeEmployee(int ID)
{
	EmployeeRecord* back;
	EmployeeRecord* temp;
	EmployeeRecord* delParent;    // Parent of node to delete
	EmployeeRecord* delNode;      // Node to delete
	EmployeeRecord* dupNode;

	temp = m_pRoot;
	back = NULL;

	// This finds the node to delete 
	while ((temp != NULL) && (ID != (temp->getID())))
	{
		back = temp;
		if (ID < temp->getID())
			temp = temp->m_pLeft;
		else
			temp = temp->m_pRight;
	}

	if (temp == NULL)
	{
		return NULL;
	}
	else
	{
		delNode = temp;
		delParent = back;
	}

	// Case 1: Deleting node with no children or one child 
	if (delNode->m_pRight == NULL)
	{
		if (delParent == NULL)
		{
			m_pRoot = delNode->m_pLeft;
			return delNode;
		}
		else
		{
			if (delParent->m_pLeft == delNode)
				delParent->m_pLeft = delNode->m_pLeft;
			else
				delParent->m_pRight = delNode->m_pLeft;
			return delNode;
		}
	}
	else if (delNode->m_pLeft == NULL)
	{
		if (delParent == NULL)		// If deleting the root this will happen  
		{
			m_pRoot = delNode->m_pRight;
			return delNode;
		}
		else
		{
			if (delParent->m_pLeft == delNode)
				delParent->m_pLeft = delNode->m_pRight;
			else
				delParent->m_pRight = delNode->m_pRight;
			return delNode;
		}
	}
	else // Case 2: Deleting node with two children 
	{
		dupNode = new EmployeeRecord;
		*dupNode = *temp;			// Copies the data structure
		dupNode->m_pLeft = NULL;	// Sets the pointers to NULL
		dupNode->m_pRight = NULL;

		temp = delNode->m_pLeft;
		back = delNode;
		while (temp->m_pRight != NULL)
		{
			back = temp;
			temp = temp->m_pRight;
		}
		// Copies the replacement values into the node that'll be deleted 
		delNode->getID = (temp->getID);
		delNode->getSalary = (temp->getSalary);
		delNode->getDept = (temp->getDept);
		delNode->getName = (temp->getName);

		// This removes the replacement node from the tree 
		if (back == delNode)
			back->m_pLeft = temp->m_pLeft;
		else
			back->m_pRight = temp->m_pLeft;
		delete temp;
		return dupNode;
	}

	//cout << "removeEmployee" << endl;

}

void EmployeeDatabase::printEmployeeRecords()
{

	printEmployeeRecords(m_pRoot);

	//cout << "printEmployeeRecords public" << endl;
}

bool EmployeeDatabase::buildDatabase(char* dataFile)
{
	bool OK = true;
	int numEmp, id, dept, numStores, sID;
	double sal;
	EmployeeRecord* empRec;
	CustomerList* theList;
	Store* theStore;
	char inStr[128];
	char fName[32];
	char lName[32];
	char sName[64];
	char sAddr[64];
	char sSt[32];
	char sCity[32];
	char sZip[12];


	inFile.open(dataFile, ifstream::in);
	if (!inFile.is_open())
	{
		// inFile.is_open() returns false if the file could not be found or
		//    if for some other reason the open failed.
		cout << "Unable to open file" << dataFile << "\nProgram terminating...\n";
		cout << "Press Enter to continue...";
		getc(stdin);
		return false;
	}

	// Get number of employees
	getNextLine(inStr, 128);
	numEmp = atoi(inStr);
	for (int i = 0; i < numEmp; i++)
	{
		// Instantiate an EmployeeRecord
		empRec = new EmployeeRecord();
		// Read and set the ID
		getNextLine(inStr, 128);
		id = atoi(inStr);
		empRec->setID(id);
		// Read and set the name
		getNextLine(fName, 32);
		getNextLine(lName, 32);
		empRec->setName(fName, lName);
		// Read and set the Department ID
		getNextLine(inStr, 128);
		dept = atoi(inStr);
		empRec->setDept(dept);
		// Read and set the Salary
		getNextLine(inStr, 128);
		sal = atof(inStr);
		empRec->setSalary(sal);
		// Get the customer list
		theList = empRec->getCustomerList();
		// Get the number of stores
		getNextLine(inStr, 128);
		numStores = atoi(inStr);
		for (int j = 0; j < numStores; j++)
		{
			// Read the store ID
			getNextLine(inStr, 128);
			sID = atoi(inStr);
			// Read the store name
			getNextLine(sName, 64);
			// Read the store address
			getNextLine(sAddr, 64);
			// Read the store city
			getNextLine(sCity, 32);
			// Read the store state
			getNextLine(sSt, 32);
			// Read the store zip
			getNextLine(sZip, 11);
			// Create a new Store object
			theStore = new Store(sID, sName, sAddr, sCity, sSt, sZip);
			theList->addStore(theStore);
		}
		cout.flush();
		addEmployee(empRec);
	}
	inFile.close();
	return true;	// Successfully built the database

}

bool EmployeeDatabase::getNextLine(char* line, int lineLen)
{
	int    done = false;
	while (!done)
	{
		inFile.getline(line, 128);

		if (inFile.good())    // If a line was successfully read
		{
			if (strlen(line) == 0)  // Skip any blank lines
				continue;
			else if (line[0] == '#')  // Skip any comment lines
				continue;
			else return true;    // Got a valid data line so return with this line
		}
		else
		{
			strcpy(line, "");
			return false;
		}
	} // end while
	return false;
}
