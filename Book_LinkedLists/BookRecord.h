#pragma once

using namespace std;

class BookRecord
{
private:

	BookRecord *m_pNext;

	char m_sTitle[129];
	long m_IStockNum;
	int m_iClassification;
	double m_dCost;
	int m_iCount;

public:

	BookRecord();
	BookRecord(const char *title, long sn, int cl, double cost);
	~BookRecord();

	void setNext(BookRecord *next);
	BookRecord *getNext();

	void setTitle(const char *title);
	void getTitle(char *title);

	void setStockNum(long sn);
	long getStockNum();

    void setClassification(int cl);
	int getClassification();

	void setCost(double c);
	double getCost();

	void setNumberInStock(int count);
	int getNumberInStock();

	void printRecord();

};