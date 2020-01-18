#include<iostream>
#include"BookRecord.h"
#include"Book_Database.h"
#include<string>

using namespace std;

Book_Database::Book_Database()                            		// Class constructor
{
	m_pRoot = NULL;
}
Book_Database::~Book_Database ()                           		// Class destuctor
{
	ClearDatabase(m_pRoot);
}

bool Book_Database::readDatabase(const char *filename)           	// Read database from file
{
	char     line[128];
    int      numBooks;
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
    getNextLine(line, 127);
    numBooks = atoi(line);	// Convert the string to an int
         // Note: you can use atof(line) to convert a string to a double

    for(int i=0; i<numBooks; i++)
    {
        // Your code to read the database goes here
		BookRecord *iptr = new BookRecord();

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

bool Book_Database::addBook(BookRecord *br)                 		// Add the given book to the list
{
	if(br!=NULL)
	{
		if(m_pRoot==NULL)
		{
			m_pRoot = br;
			return true;
		}
		else if(m_pRoot!=NULL)
		{
		BookRecord *temp;
	    BookRecord *back;

	    temp = m_pRoot;
		back = NULL;

		while(temp!=NULL)
		{
			back=temp;

			if(temp->getStockNum()>br->getStockNum())
			{
				temp = temp->m_pLeft;
			}
			else
			{
				temp = temp->m_pRight;
			}
		}

		if(back==NULL)
		{
			m_pRoot = br;
			return true;
		}
		else
		{
			if(br->getStockNum()<back->getStockNum())
			{
				back->m_pLeft = br;
			    return true;
			}
			else
			{
				back->m_pRight = br;
			    return true;
			}
			return true;
         }
	   }
	}
	return false;
}
BookRecord *Book_Database::removeBook(long stockNum)              	// Remove a book from the list
{
	BookRecord *back = NULL;  
	BookRecord *temp = m_pRoot;  
	BookRecord *delParent = NULL;     
    BookRecord *delNode = NULL;
	
	if(temp!=NULL)
	{

	while(temp!=NULL && temp->getStockNum()!=stockNum)
	{
		back = temp;
		if(temp->getStockNum()>stockNum)
			{
				temp = temp->m_pLeft;
			}
		else 
			{
				temp = temp->m_pRight;
			} 
	}

	if(temp==NULL)
	{
		return NULL;
	}
	else 
	{
		delNode = temp;
		delParent = back;

		if(delNode->m_pRight == NULL)
			{
				
				if(delParent == NULL) 
				{
					m_pRoot = delNode->m_pLeft;
					
					delNode->m_pLeft = NULL;
					return delNode;
				}
				else
				{
					if(delParent->m_pLeft == delNode)
					{
						delParent->m_pLeft = delNode->m_pLeft;
					
						delNode->m_pLeft = NULL;
					return delNode;
					}
                    else
					{
						delParent->m_pRight = delNode->m_pLeft;
					
						delNode->m_pLeft = NULL;
					return delNode;
					}
				}
			}

		else if(delNode->m_pLeft == NULL)
			{

				     if(delParent == NULL) 
				   {
					   m_pRoot = delNode->m_pRight;
			
					   delNode->m_pRight = NULL;
					return delNode;
				}
				else
				{
					if(delParent->m_pLeft == delNode)
					{
						delParent->m_pLeft = delNode->m_pRight;
			
						delNode->m_pRight = NULL;
					return delNode;
					}
                    else
					{
						delParent->m_pRight= delNode->m_pRight;
                  
						delNode->m_pRight = NULL;
					return delNode;
					}
				}
				}
				else
				{
					temp = delNode->m_pLeft;
                    back = delNode;

					BookRecord *DupNode = new BookRecord();

					DupNode->setStockNum(delNode->getStockNum());
					DupNode->setClassification(delNode->getClassification());
					DupNode->setCost(delNode->getCost());
					DupNode->setNumberInStock(delNode->getNumberInStock());

					while(temp->m_pRight != NULL)
					{
						back = temp;
						temp = temp->m_pRight;
                    }

					delNode->setStockNum(temp->getStockNum());
					delNode->setClassification(temp->getClassification());
					delNode->setCost(temp->getCost());
					delNode->setNumberInStock(temp->getNumberInStock());
					
					if(back == delNode)
					{
						back->m_pLeft = temp->m_pLeft;
					}
					else
					{
						back->m_pRight = temp->m_pLeft;
					}
					delete temp;
					return DupNode;
				}
			}
			}

	return NULL;
}

BookRecord *Book_Database::searchByStockNumber(long stockNum)    	// Search for a book by stock number
{
	BookRecord *temp;
	temp = m_pRoot;
	
	while(temp!=NULL && temp->getStockNum()!=stockNum)
	{
		if(temp->getStockNum()>stockNum)
			{
				temp = temp->m_pLeft;
				//cout<<"Moved to left as book number is less "<<endl;
			}
			else
			{
				temp = temp->m_pRight;
				//cout<<"Moved to right as book number is less "<<endl;
			} 
	}
	if(temp!=NULL)
	{
		//cout<<"Book found at the root"<<endl;
		return temp;
	}
	else
	{
		return NULL;
	}
	return NULL;
}

void Book_Database::searchByClassification(int cl)         		// Search for all books of the given classification
{
	if(m_pRoot!=NULL)
	{
		cout<<"\n        Books with the Given Classification "<<endl;
		cout << "-------------------------------------------------------------\n" << endl;
	    searchByClassification(cl ,m_pRoot);
	}
	else
	{
		cout<<"No items to be displayed"<<endl;
	}
}
void Book_Database::searchByCost(double min, double max)   		// Search for all books whose cost is within the given range
{	
	if(m_pRoot!=NULL)
	{
		cout<<"\n        Books with the Given Cost Range   "<<endl;
		cout << "-------------------------------------------------------------\n" << endl;
	    searchByCost(min, max, m_pRoot);
	}
	else
	{
		cout<<"No items to be displayed"<<endl;
	}	
}

int Book_Database::getNumberInStock(long sn)					// Get number of books of given stock number in stock 
{
	BookRecord *temp;
	temp = m_pRoot;

	if(temp->getStockNum() == sn)
	{
		return temp->getNumberInStock();
	}
	while(temp!=NULL && temp->getStockNum()!=sn)
	{
		if(temp->getStockNum()>sn)
			{
				temp = temp->m_pLeft;
				//cout<<"Moved to left as book number is less "<<endl;
			}
			else
			{
				temp = temp->m_pRight;
				//cout<<"Moved to right as book number is less "<<endl;
			} 
	}
	if(temp!=NULL)
	{
		return temp->getNumberInStock();
	}
	else
	{
		return NULL;
	}
	return NULL;
}

void Book_Database::PrintDatabase()
{
	BookRecord *temp;
	
	cout <<"\n                   List of Books " << endl;
	cout << "-------------------------------------------------------------" << endl;

	if(m_pRoot == NULL) //reports no items in the list
	{
		cout << "\tList is currently empty.\n" << endl;
	}
	else 
	{
		temp = m_pRoot;

		if(temp!=NULL)
		{
			PrintDatabase(temp);
		}
	}
}

void Book_Database::PrintDatabase(BookRecord *rt)                	// Recursive print all
{
	if(rt != NULL)
	{
		PrintDatabase(rt->m_pLeft);
		rt->printRecord();
		PrintDatabase(rt->m_pRight);
	}
}
void Book_Database::ClearDatabase(BookRecord *rt)              	// Recursively remove any items from the list
{
	if(rt!=NULL)
  {
	  ClearDatabase(rt->m_pLeft);
	  ClearDatabase(rt->m_pRight);
	  delete rt;
  }
}

bool Book_Database::getNextLine(char *line, int lineLen)   		// Read next line from a file
{
	 int    done = false;
    while(!done)
    {
        m_InFile.getline(line, 128);
        
        if(m_InFile.good())    // If a line was successfully read
        {
            if(strlen(line) == 0)  // Skip any blank lines
                continue;
            else if(line[0] == '#')  // Skip any comment lines
                continue;
            else return true;    // Got a valid data line so return with this line
        }
        else
        {
            strcpy(line, "");	// Reached the end of the file
            return false;
        }
    } // end while
    return false;  // You can never get here but include the return anyway to keep the
                   // compiler from warning you that not all paths return a value.
}

void Book_Database::searchByClassification(int cl, BookRecord *rt)	// Recursive search by classification
{
	if(rt!=NULL)
  {
	  searchByClassification( cl, rt->m_pLeft);
	  
	  searchByClassification( cl, rt->m_pRight);

	  if(rt->getClassification() == cl)
	  {
		  rt->printRecord();
	  } 
  }
}

void Book_Database::searchByCost(double min, double max, BookRecord *rt) // Recursive search by cost range
{
	if(rt!=NULL)
  {
	  searchByCost( min,max, rt->m_pLeft);
	  
	  searchByCost( min,max, rt->m_pRight);

	  if((min) < rt->getCost())
	  {
		  if(rt->getCost() < (max))
		  {
		  rt->printRecord();
		  }
	  } 
  }
}
//end of program












