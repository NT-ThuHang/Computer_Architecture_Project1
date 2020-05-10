#pragma once
#include "QInt.h"

/* Class thực hiện các hàm thao tác cho operator >>, <<, ror, rol */
class BitManipulation
{
public:
	// Hàm dịch 1 bit
	static void logLeftShift_1(QInt& x);
	static void logRightShift_1(QInt& x);

	// Hàm dịch y bit
	static QInt& logicalLeftShift(const QInt& x, int y);
	static QInt& logicalRightShift(const QInt& x, int y);
	static QInt& arithmeticRightShift(const QInt& x, int y);

	// Hàm thao tác cho ror, rol
	static QInt& leftRotate(const QInt& x, int y);
	static QInt& rightRotate(const QInt& x, int y);
	BitManipulation();
	~BitManipulation();
};

