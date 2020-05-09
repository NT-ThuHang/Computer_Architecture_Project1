#pragma once
#ifndef __QINT_H__
#define __QINT_H__

#include <iostream>
#include <string>
using namespace std;
class QInt
{
private:
	int data[4];
public:
	// Hàm chuyển thành số bù 2
	void convert2complement();
	bool operator < (QInt a);
	bool operator > (QInt a);
	bool operator == (QInt a);
	bool operator <= (QInt a);
	bool operator >= (QInt a);
	QInt operator = (QInt a);

	QInt& operator<<(int y);
	QInt& operator>>(int y);	// theo c++ thì toán tử >> là shift số học
	QInt& logicalRightShift(int y);
	QInt& rol();	// left rotate
	QInt& ror();	// right rotate

	QInt& operator + (QInt);
	QInt& operator - (QInt);
	QInt& operator * (QInt);
	QInt& operator / (QInt);
	QInt& operator % (QInt);

	QInt& operator & (QInt y);
	QInt& operator | (QInt y);
	QInt& operator ^ (QInt y);
	QInt& operator ~ ();

	// Hàm kiểm tra tràn số QInt
	bool overflow(string s);
	// Hàm kiểm tra số nhỏ nhất của QInt
	bool isMinQInt();
	// Hàm reset lại QInt = 0
	void resetQInt();

	friend istream& operator >> (istream&, QInt&);
	friend ostream& operator << (ostream&, QInt);
	void ScanQInt(string s);
	string PrintQInt();

	friend class Comparison;
	friend class BitManipulation;
	friend class BasicOperation;
	friend class Conversion;
	QInt();
	~QInt();
};
#endif


