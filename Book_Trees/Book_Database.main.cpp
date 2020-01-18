#include<iostream>
#include"Book_Database.h"

using namespace std;


int main()
{
	Book_Database *iptr = new Book_Database();

	iptr->readDatabase("BookData.txt");
	//iptr->PrintDatabase();
	
	BookRecord *temp;
	temp = iptr->removeBook(890);

	cout<<temp->getStockNum();

	temp = iptr->removeBook(345);

	cout<<temp->getStockNum();

	temp = iptr->removeBook(567);

	cout<<temp->getStockNum();
	iptr->PrintDatabase();
}
