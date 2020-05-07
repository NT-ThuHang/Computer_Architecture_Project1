#ifndef __QLOAT_H__
#define __QLOAT_H__
#include "QBit.h"
class Qfloat:public QBit
{
private:
	//const int K = 16383;
	//Sign:1bit
	//Exponent:15 bit
	//Significant:112bit
	int K = (1 << 14) - 1;//2^14-1
public:
	//Hàm Kiểm tra Trường hợp đặc biệt
	bool isNegative();
	bool isInf();
	bool isZero();
	bool isNaN();
	//Hàm hổ trợ
	int compare(Qfloat a, Qfloat b);
	bool operator < (Qfloat);
	bool operator > (Qfloat);
	bool operator == (Qfloat);
	bool operator <= (Qfloat);
	bool operator >= (Qfloat);
	Qfloat& operator = (const Qfloat& n);
	//Nhóm Hàm Chuyển Đổi Về Chuỗi Tương ứng với hệ cơ số 2, 16
	string toBin()const;
	string toDec()const;
	//Nhóm Hàm Chuyển Đổi Về Qfloat từ Chuỗi của Hệ cơ số 2, 10, 16
	Qfloat& fromBin(const string&);
	Qfloat& fromDec(const string&);
	friend istream& operator >> (istream&, Qfloat&);
	friend ostream& operator << (ostream&, Qfloat);
	Qfloat() :QBit() {};
	Qfloat(const Qfloat& a) :QBit(a) {};
	Qfloat(const QBit& a) :QBit(a) {};
	~Qfloat();
};


#endif // !__QLOAT_H__
/*Tâm Thư: tui test chưa kĩ lắm ai test hộ tui với nếu rãnh nhé! Không thì đến thời điểm này tui chưa chắc nó acepted đâu :( */