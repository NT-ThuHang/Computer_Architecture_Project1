#pragma once
#ifndef __QINT_H__
#define __QINT_H__

#include "QBit.h"
#include <map>
class QInt :public QBit
{
public:
	string QINT_MAX = "170141183460469231731687303715884105727";
	string QINT_MIN = "-170141183460469231731687303715884105727";
	//Hàm hổ trợ
	int compare(QInt a, QInt b);
	//Hàm Chuyển Đổi Qua Dang Bu 2
	void convert2complement();
	//Nhóm hàm định nghĩa toán Tử so sánh
	bool operator < (QInt a);
	bool operator > (QInt a);
	bool operator == (QInt a);
	bool operator <= (QInt a);
	bool operator >= (QInt a);
	QInt& operator = (const QInt& n);
	//Nhóm hàm định nghĩa toán tử phép tính
	QInt operator + (const QInt&)const;
	QInt operator - (const QInt&)const;
	QInt operator * (const QInt&)const;
	QInt operator / (const QInt&)const;
	QInt operator % (const QInt&)const;
	//Nhóm Hàm Chuyển Đổi Về Chuỗi Tương ứng với hệ cơ số 2, 10, 16
	string toBin()const;
	string toHex()const;
	string toDec()const;
	//Nhóm Hàm Chuyển Đổi Về QInt từ Chuỗi của Hệ cơ số 2, 10, 16
	QInt& fromBin(const string&);
	QInt& fromDec(const string&);
	QInt& fromHex(const string&);
	//Nhóm Hàm Định nghĩa Nhập Xuât Cơ Bản
	friend istream& operator >> (istream&, QInt&);
	friend ostream& operator << (ostream&, QInt);
	QInt() :QBit() {};
	QInt(const QInt& a) :QBit(a) {};
	QInt(const QBit& a) :QBit(a) {};
	~QInt();
};
#endif //	!__QINT_H__