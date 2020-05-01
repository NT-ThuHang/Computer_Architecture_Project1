#pragma once
#include "QInt.h"

class BitManipulation
{
public:
	static void logLeftShift_1(QInt& x);
	static void logRightShift_1(QInt& x);

	static QInt& logicalLeftShift(const QInt& x, int y);
	static QInt& logicalRightShift(const QInt& x, int y);
	static QInt& arithmeticRightShift(const QInt& x, int y);

	static QInt& leftRotate(const QInt& x);
	static QInt& rightRotate(const QInt& x);
	BitManipulation();
	~BitManipulation();
};

