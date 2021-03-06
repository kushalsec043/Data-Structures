#include<iostream>
#include"BookRecord.h"
#include<iomanip>
#include<conio.h>
#include<String.h>

using namespace std;

//Default Constructor
BookRecord::BookRecord()
{
	strcpy(m_sTitle," ");
	m_IStockNum = 0;
	m_iClassification = 0;
	m_dCost = 0;
	m_iCount = 0;
}

//Prameterized Constructor
BookRecord::BookRecord(const char *title, long sn, int cl, double cost)
{
	strcpy(m_sTitle,title);
	m_IStockNum = sn;
	m_iClassification = cl;
	m_dCost = cost;
	m_iCount = 1;
}
//Destructor
BookRecord::~BookRecord()
{

}

//Set Title And Get Title
void BookRecord::setTitle(const char *title)
{
	strcpy(m_sTitle,title);
}
void BookRecord::getTitle(char *title)
{
	strcpy(title,m_sTitle);
}

//Set StockNum and Get StockNum
void BookRecord::setStockNum(long sn)
{
	m_IStockNum = sn;
}
long BookRecord::getStockNum()
{
	return m_IStockNum;
}

//Set Classification and Get Classification
void BookRecord::setClassification(int cl)
{
	m_iClassification = cl;
}
void BookRecord::getClassification(int &cl)
{
	cl = m_iClassification;
}

//Set Cost and Get Cost
void BookRecord::setCost(double c)
{
	m_dCost = c;
}
void BookRecord::getCost(double *c)
{
	*c = m_dCost;
}

//Set NumberInStock and Get NumberInStock
void BookRecord::setNumberInStock(int count)
{
	m_iCount = count;
}
int BookRecord::getNumberInStock()
{
	return m_iCount;
}

//Print Record
void BookRecord::printRecord()
{
	cout<<"    Title       : "<<m_sTitle<<endl;
	cout<<" Stock Number   : "<<m_IStockNum<<endl;
	cout<<"Classification  : "<<m_iClassification<<endl;
	cout<<"     Cost       : $"<<m_dCost<<endl;
	cout<<"   In Stock     : "<<m_iCount<<endl;

	cout<<m_sTitle<<"  "<<m_IStockNum<<"  "<<m_iClassification<<"  "<<m_dCost<<"  "<<m_iCount;
}













