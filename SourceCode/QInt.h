#pragma once
#include <iostream>
#include <string>

using namespace std;
class QInt
{
private:
	int data[4];
public:
	void DivideString(string& a, int k);
	friend istream& operator >> (istream&, QInt&);
	friend ostream& operator << (ostream&, QInt);
	QInt();
	~QInt();
};



