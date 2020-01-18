#include<iostream>
#include<fstream>   // This header gives you all the file I/O functions
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include"BookRecord.h"
#include"Book_Inventory.h"

using namespace std;

Book_Inventory::Book_Inventory()
{
	m_pHead = NULL;
}
Book_Inventory::~Book_Inventory()
{
	delete m_pHead;
}
bool Book_Inventory::getNextLine(char *line, int lineLen)
{
	int done = false;

    while(!done)
    {
        m_InFile.getline(line, lineLen);
        
        if(m_InFile.good())    // If a line was successfully read
        {
            if(strlen(line) == 0)  // Skip any blank lines
                continue;
            else if(line[0] == '#')  // Skip any comment lines
                continue;
            else 
				return true;    // Got a valid data line so return with this line
        }
        else // No valid line read, meaning we reached the end of file
        {
            strcpy(line, ""); // Copy empty string into line as sentinal value
            return false;
        }
    } // end while
    return false; // Cannot reach this point but include a return to avoid compiler warning
                  //   that not all paths return a value.
}
bool Book_Inventory::readInventory(const char *filename)         // Read inventory file and build the list
{
	char     line[128];
     int      numBooks;

	 BookRecord *iptr;

     // define other variables here as needed

    m_InFile.open(filename, ifstream::in);

    if(!m_InFile.is_open())
    {
        // m_InFile.is_open() returns false if the file could not be found or
        //    if for some other reason the open failed.
        cout << "Unable to open file" << filename << "\nProgram terminating...\n";
        return false;
    }
    // Read number of books
    getNextLine(line, 128);
    numBooks = atoi(line);

    for(int i=0; i<numBooks; i++)
    {
        // ------------------------------------------
        // Your code to read the inventory goes here
        // ------------------------------------------
		iptr = new BookRecord();

		getNextLine(line,128);
		iptr->setStockNum(atol(line));
		getNextLine(line,128);
		iptr->setTitle(line);
		getNextLine(line,128);
		iptr->setClassification(atoi(line));
		getNextLine(line,128);
		iptr->setCost(atof(line));
		getNextLine(line,128);
		iptr->setNumberInStock(atoi(line));

		addBook(iptr);
    }
    return true;	
}
bool Book_Inventory::addBook(BookRecord *br)           		// Add the given book to the list 
{
	BookRecord *temp=NULL;
	BookRecord *back=NULL;

	if(br != NULL)
	{
		if(m_pHead == NULL)
		{
			m_pHead = br;
			return true;
		}
		else
		{
			temp = m_pHead;
			back = NULL;

			while((temp != NULL) && (temp->getStockNum() < br->getStockNum()))
			{
				back = temp;
				temp = temp->getNext(); 
			}

			if(back == NULL)
			{
			br->setNext(temp);
			m_pHead = br;
			}
			else if(temp != NULL)
			{
			back->setNext(br); 
			br->setNext(temp);
			}
			else if(temp == NULL)
			{
			back->setNext(br);
			br->setNext(temp);
			}
			else
			{
			back->setNext(br); 
			}
		return true;
		}
	}
	return false;
}
BookRecord *Book_Inventory::removeBook(long stockNum)   		// Remove a book from the list or print message if not found
{
	BookRecord *temp = NULL;
	BookRecord *back = NULL;

	if(m_pHead == NULL)
	{
		return NULL;
	}

	else
	{
    temp = m_pHead;
	back = NULL;

	while((temp != NULL) && (temp->getStockNum() != stockNum))
	{
		back = temp;
		temp = temp->getNext();
	}

	if(temp == NULL)
	{
		return NULL;
	}

	else if(back == NULL)
	{
		m_pHead = m_pHead->getNext();
		return temp;
	}
	else 
	{
		back->setNext(temp->getNext());
		 return temp;
	}
	}
	return NULL;
}
 
BookRecord *Book_Inventory::searchByStockNumber(long stockNum) 	// Search by stock number return pointer to node or NULL if not found
{
	BookRecord *temp=NULL;

	if(m_pHead==NULL)
	{
		return NULL;
		//cout<<"Empty list encountered"<<endl;
	}
	else
	{
	temp=m_pHead;
	
	while(temp!=NULL && temp->getStockNum()!=stockNum)
	{
		temp=temp->getNext();
	}
	if(temp!=NULL)
	{
		return temp;
	}
	else if(temp==NULL)
	{
		return NULL;
		//cout<<"Not found after several operations"<<endl;
	}
	else
	{
		return NULL;
	}
	}
	return NULL;
}

void Book_Inventory::searchByClassification(int cl)   			// Search for all books given classification, print all data
{
	int m = 0;
	BookRecord *temp=NULL;

	if(m_pHead==NULL)
	{
		cout<<"Empty Inventory"<<endl;
		//cout<<"Empty list encountered"<<endl;
	}
	else
	{
	temp=m_pHead;
	
	cout<<"\n          Books found with the Given Classification are being listed       \n"<<endl;
	while(temp!=NULL)
    {
	if(temp!=NULL && temp->getClassification()== cl)
	{
		//cout<<"The Book with the given has been found"<<endl;
		temp->printRecord();
		
		cout<<"\n-------------------------------------------------------------------------------------"<<endl;
		temp = temp->getNext();
		m++;
	}
	else
	{
		temp = temp->getNext();
    }
	
    }
    }
	if(m=0)
	{
		cout<<"Not found after all operations"<<endl;
		//cout<<"Not found after several operations"<<endl;
	}
	else
	{
		cout<<" Did find atleat one or more books with the given classification "<<endl;
	}
}
	


void Book_Inventory::searchByCost(double min, double max)		// Search for all books within the given cost range
{
	BookRecord *temp=NULL;
	int n=0;

	if(m_pHead==NULL)
	{
		cout<<"Empty list encountered"<<endl;
	}
	else
	{
	temp = m_pHead;
	cout<<"\n            Books found with the Given Cost are being listed       "<<endl;
	while(temp!=NULL)
    {
	if(temp!=NULL && ((min) < (temp->getCost())))
	{
		if((temp->getCost()) < (max))
		{
		//cout<<"The Book with cost between the range has been found"<<endl;
		cout<<"\n-------------------------------------------------------------------------------------"<<endl;
		temp->printRecord();
		temp=temp->getNext();
		n++;
		}
		else
		{
			temp = temp->getNext();
		}
	}
	else
	{
		temp=temp->getNext();
	}
    }
    }
	if(n==0)
	{
		cout<<"\n\n Not found after several operations"<<endl;
	}																														
	else
	{
		cout<<"\n\n Did find atleat one or more books with the given cost range "<<endl;
	}
}

int Book_Inventory::getNumberInStock(long sn)           		// Get number of books in stock for the given stock number 
{
	BookRecord *temp=NULL;

	if(m_pHead==NULL)
	{
		return NULL;
		cout<<"Empty list encountered"<<endl;
	}
	else
	{
	temp=m_pHead;
	
	while(temp!=NULL && temp->getStockNum() != sn)
	{
		temp=temp->getNext();
	}
	if(temp!=NULL)
	{
		return temp->getNumberInStock();
	}
	else if(temp==NULL)
	{
		return NULL;
	}
	else
	{
		return NULL;
	}
	}
	return NULL;
}

void Book_Inventory::printInventory()
{
	BookRecord *temp;
	
	cout <<"    ****************************  List of Books *************************** " << endl;
	cout <<"-------------------------------------------------------------------------------------" << endl;

	if(m_pHead == NULL) //reports no items in the list
	{
		cout << "\tList is currently empty.\n" << endl;
	}
	else 
	{
		temp = m_pHead;

		while(temp!=NULL)
		{
			temp->printRecord();
			cout<<"\n-------------------------------------------------------------------------------------"<<endl;
			temp = temp->getNext();
		}
	}
}


void Book_Inventory::ClearInventory()                             // Remove all items from the list
{
	BookRecord *m_list;
	
	m_list = m_pHead;

	if(m_list == NULL) //reports no items in the list
	{
		cout << "\tList is currently empty.\n" << endl;
	}
	else 
	{
		while(m_list!=NULL)
		{
			removeBook(m_list->getStockNum());
			m_list = m_list->getNext();
		}
	}
    cout<<"\n\nCleared all items from the list"<<endl;
}








