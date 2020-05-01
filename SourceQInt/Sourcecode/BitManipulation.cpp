//#include "pch.h"
#include "BitManipulation.h"

/*
Input: Số QInt x
Output: Số QInt x sau khi dịch trái logic cho 1
Thực hiện: dịch từng phần tử data của QInt, đồng thời dùng 2 biến leftBit, rightBit để lưu bit
trái nhất và phải nhất của mỗi phần tử, sau đó gán lại cho phần từ bên cạnh tương ứng
*/
void BitManipulation::logLeftShift_1(QInt& x)
{
	int leftBit = 0, rightBit = 0;

	for (int i = 3; i >= 0; i--)
	{
		leftBit = (x.data[i] >> 31) & 1;
		x.data[i] = x.data[i] << 1;

		if (rightBit == 1)
			x.data[i] = x.data[i] | 1;

		rightBit = leftBit;
	}
}

/*
Input: Số QInt x
Output: Số QInt x sau khi dịch phải logic cho 1
Thực hiện: dịch từng phần tử data của QInt, đồng thời dùng 2 biến leftBit, rightBit để lưu bit
trái nhất và phải nhất của mỗi phần tử, sau đó gán lại cho phần từ bên cạnh tương ứng
*/
void BitManipulation::logRightShift_1(QInt& x)
{
	int leftBit = 0, rightBit = 0;

	for (int i = 0; i < 4; i++)
	{
		rightBit = x.data[i] & 1;
		x.data[i] = x.data[i] >> 1;

		if (leftBit == 1)
			x.data[i] = x.data[i] | (1 << 31);
		else // leftBit == 0
			x.data[i] = x.data[i] & (~(1 << 31));

		leftBit = rightBit;
	}
}

QInt& BitManipulation::logicalLeftShift(const QInt& x, int y)
{
	QInt res = x;
	if (y > 127)
	{
		// toàn bộ bit bị dịch ra hết => x = 0
		for (int i = 0; i < 4; i++)
		{
			res.data[i] = 0;
		}
	}
	else
	{
		for (int i = 0; i < y; i++)
		{
			BitManipulation::logLeftShift_1(res);
		}
	}
	return res;
}

QInt& BitManipulation::logicalRightShift(const QInt& x, int y)
{
	QInt res = x;
	if (y > 127)
	{
		// toàn bộ bit bị dịch ra hết => x = 0
		for (int i = 0; i < 4; i++)
			res.data[i] = 0;
	}
	else
	{
		for (int i = 0; i < y; i++)
			BitManipulation::logRightShift_1(res);
	}
	return res;
}

QInt& BitManipulation::arithmeticRightShift(const QInt& x, int y)
{
	// Lưu bit ngoài cùng bên trái của data[0]
	int mostLeftBit = (x.data[0] >> 31) & 1;
	if (mostLeftBit == 0)
		return BitManipulation::logicalRightShift(x, y);

	// mostLeftBit = 1
	QInt res = x;
	if (y > 127)
	{
		// toàn bộ bit bị dịch ra hết, x sẽ chứa toàn là bit 1 => x = -1
		for (int i = 0; i < 4; i++)
			res.data[i] = -1;
	}
	else
	{
		for (int i = 0; i < y; i++)
		{
			BitManipulation::logRightShift_1(res);
			// Gán bit 1 vào đầu data[0] sau mỗi lần dịch (theo quy tắc dịch số học)
			res.data[0] = res.data[0] | (1 << 31);
		}
	}
	return res;
}

QInt& BitManipulation::leftRotate(const QInt& x)
{
	// Lưu bit ngoài cùng bên trái của data[0]
	int mostLeftBit = (x.data[0] >> 31) & 1;

	QInt res = BitManipulation::logicalLeftShift(x, 1);
	// Chuyển bit về cuối
	if (mostLeftBit == 1)
	{
		res.data[3] = res.data[3] | 1;
	}
	return res;
}

QInt& BitManipulation::rightRotate(const QInt& x)
{
	// Lưu bit ngoài cùng bên phải của data[3]
	int mostRightBit = x.data[0] & 1;

	QInt res = BitManipulation::logicalRightShift(x, 1);
	// Chuyển bit về đầu
	if (mostRightBit == 1)
	{
		res.data[0] = res.data[0] | (1 << 31);
	}
	return res;
}

BitManipulation::BitManipulation()
{
}

BitManipulation::~BitManipulation()
{
}

