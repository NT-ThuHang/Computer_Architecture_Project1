#pragma once
#include <iostream>
#include <string>

using namespace std;
class QInt
{
private:
	unsigned int data[4];
	//explain
	//Domain of data[0] is [0,2^32] 
	//Domain of data[1] is [0,2^32] 
	//Domain of data[2] is [0,2^32] 
	//Domain of data[3] is [-2^31,2^32] 
public:
	void DivideString(string& a, int k);
	friend istream& operator >> (istream&, QInt&);
	friend ostream& operator << (ostream&, QInt);
	QInt();
	~QInt();
};





