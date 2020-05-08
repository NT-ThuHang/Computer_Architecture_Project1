#pragma once
#ifndef __QNUMERIC_H__
#define __QNUMERIC_H__
#include <string>
#include <iostream>
using namespace std;
class QNumeric
{
protected:
	int data[4];//Kiểu int 4 byte = >QNumeric 128 bits
public:
	//Nhóm hàm phụ trợ
	void setBit(int pos, int bit);
	int getBit(int pos)const;
	//Nhóm hàm toán tử cơ bản trong xử lí Bit
	QNumeric& operator =(const QNumeric& n);
	QNumeric operator >> (int k)const;
	QNumeric operator << (int k)const;
	QNumeric arithmeticRightShift(int k)const;
	QNumeric rol(int k)const;	// left rotate
	QNumeric ror(int k)const;	// right rotate
	QNumeric operator ~() const;
	QNumeric operator |(const QNumeric& n) const;
	QNumeric operator &(const QNumeric& n) const;
	QNumeric operator ^(const QNumeric& n) const;
	//Nhóm hàm khởi tạo,hủy
	QNumeric(const QNumeric&);
	QNumeric();
	~QNumeric();
};
#endif // !__QNUMERIC_H__
