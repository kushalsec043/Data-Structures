#include"Book_Inventory.h"
#include<iostream>

using namespace std;

int main()
{
	Book_Inventory *book = new Book_Inventory();

	book->readInventory("BookData.txt");

	book->printInventory();

}