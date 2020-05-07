#pragma once
#ifndef __QBIT_H__
#define __QBIT_H__
#include <string>
#include <iostream>
using namespace std;
class QBit
{
protected:
	int data[4];//Kiểu int 4 byte = >QBit 128 bits
public:
	//Nhóm hàm phụ trợ
	void setBit(int pos, int bit);
	int getBit(int pos)const;
	//Nhóm hàm toán tử cơ bản trong xử lí Bit
	QBit& operator =(const QBit& n);
	QBit operator >> (int k)const;
	QBit operator << (int k)const;
	QBit arithmeticRightShift(int k)const;
	QBit rol(int k)const;	// left rotate
	QBit ror(int k)const;	// right rotate
	QBit operator ~() const;
	QBit operator |(const QBit& n) const;
	QBit operator &(const QBit& n) const;
	QBit operator ^(const QBit& n) const;
	//Nhóm hàm khởi tạo,hủy
	QBit(const QBit&);
	QBit();
	~QBit();
};
#endif // !__QBIT_H__
