#ifndef __QLOAT_H__
#define __QLOAT_H__

#include <iostream>
#include <string>
using namespace std;

class Qfloat
{
private:
	// const int K = 16383;
	// Sign: 1bit
	// Exponent: 15 bit
	// Significant: 112bit
	int data[4];
	int K = (1 << 14) - 1;//2^14-1
public:
	void setBit(int pos, int bit);
	int getBit(int pos);

	// Hàm kiểm tra các trường hợp đặc biệt
	bool isNegative();
	bool isInf();
	bool isZero();
	bool isNaN();
	bool isDenormalized();
	void resetQfloat();

	// Hàm so sánh Qfloat
	int compare(Qfloat a, Qfloat b);
	bool operator < (Qfloat);
	bool operator > (Qfloat);
	bool operator == (Qfloat);
	bool operator <= (Qfloat);
	bool operator >= (Qfloat);
	Qfloat& operator = (const Qfloat& n);

	// Hàm chuyển đổi giữa Qfloat và dấu chấm động
	string DectoBin();
	static Qfloat& BinToDec(const string&);

	// Hàm kiểm tra input dạng Qfloat string cho MFC app
	string checkInvalid(string s);

	// Hàm đọc xuất chuỗi
	Qfloat& ScanQfloat(const string&);
	string PrintQfloat();

	// Operator cin, cout Qfloat
	friend istream& operator >> (istream&, Qfloat&);
	friend ostream& operator << (ostream&, Qfloat);
	Qfloat();
	~Qfloat();
};


#endif // !__QLOAT_H__