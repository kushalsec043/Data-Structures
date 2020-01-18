#pragma once

class BookRecord
{
private:
	char m_sTitle[129];
	long m_IStockNum;
	int m_iClassification;
	double m_dCost;
	int m_iCount;

public:
	BookRecord();
	BookRecord(const char *title, long sn, int cl, double cost);
	~BookRecord();

	void setTitle(const char *title);
	void getTitle(char *title);

	void setStockNum(long sn);
	long getStockNum();

    void setClassification(int cl);
	void getClassification(int &cl);

	void setCost(double c);
	void getCost(double *c);

	void setNumberInStock(int count);
	int getNumberInStock();

	void printRecord();

};