#pragma once
#include "QInt.h"

class BitManipulation
{
public:
	static string QIntToBinStr(const QInt& x);
	static QInt& BinStrToQInt(string s);

	static QInt& logicalLeftShift(const QInt& x, int y);
	static QInt& logicalRightShift(const QInt& x, int y);
	static QInt& arithmeticRightShift(const QInt& x, int y);

	static QInt& leftRotate(const QInt& x);
	static QInt& rightRotate(const QInt& x);
};

