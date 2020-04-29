#include "pch.h"
#include "BitManipulation.h"

/*
Input: Biến x kiểu QInt (128 bit)
Output: Chuỗi biểu diễn nhị phân tương ứng của x
*/
string BitManipulation::QIntToBinStr(const QInt& x)
{
	string bin;
	// Lặp qua 128 bit, lấy từng bit ra và thêm vào chuỗi kết quả
	for (int i = 0; i < 128; i++)
	{
		int bit = (x.data[i / 32] >> (31 - i % 32)) & 1;
		bin = bin + char(bit + '0');
	}
	return bin;
}

/*
Input: Chuỗi biểu diễn nhị phân x
Output: Biến x kiểu QInt (128 bit) tương ứng với biểu diễn nhị phân đó
*/
QInt& BitManipulation::BinStrToQInt(string s)
{
	QInt* res = new QInt();
	// Lặp qua từng kí tự, nếu là '1' thì gán vào bit tương ứng của QInt
	for (int i = 0; i < 128; i++)
	{
		int bit = s[i] - '0';
		if (bit == 1)
			res->data[i / 32] = res->data[i / 32] | (bit << (31 - i % 32));
	}
	return *res;
}

QInt& BitManipulation::logicalLeftShift(const QInt& x, int y)
{
	string bin = BitManipulation::QIntToBinStr(x);

	// Dời (128 - y) bit cuối sang trái y đơn vị
	long long i = 0;
	for (; i < bin.length() - y; i++)
	{
		bin[i] = bin[i + y];
	}
	// Gán giá trị 0 các bit còn lại ở cuối
	while (i < bin.length())
	{
		bin[i] = '0';
		i++;
	}

	QInt res = BitManipulation::BinStrToQInt(bin);
	return res;
}

QInt& BitManipulation::logicalRightShift(const QInt& x, int y)
{
	string bin = BitManipulation::QIntToBinStr(x);

	// Dời (128 - y) bit đầu sang phải y đơn vị
	long long i = bin.length() - 1;
	for (; i >= y; i--)
	{
		bin[i] = bin[i - y];
	}
	// Gán giá trị 0 các bit còn lại ở đầu
	while (i >= 0)
	{
		bin[i] = '0';
		i--;
	}

	QInt res = BitManipulation::BinStrToQInt(bin);
	return res;
}

QInt& BitManipulation::arithmeticRightShift(const QInt& x, int y)
{
	// Lấy bit ngoài cùng trái nhất
	int mlb = (x.data[0] >> 31) & 1;

	string bin = BitManipulation::QIntToBinStr(x);

	// Dời (128 - y) bit đầu sang phải y đơn vị
	long long i = bin.length() - 1;
	for (; i >= y; i--)
	{
		bin[i] = bin[i - y];
	}
	// Gán giá trị các bit còn lại ở đầu
	while (i >= 0)
	{
		bin[i] = char(mlb +'0');
		i--;
	}

	QInt res = BitManipulation::BinStrToQInt(bin);
	return res;
}


QInt& BitManipulation::leftRotate(const QInt& x)
{
	int mostLeftBit = (x.data[0] >> 31) & 1;
	QInt res = BitManipulation::logicalLeftShift(x, 1);

	// Đưa bit ngoài cùng bên trái (của x ban đầu) vào vị trí ngoài cùng bên phải
	if (mostLeftBit == 1)
		res.data[3] = res.data[3] | 1;
	else
		res.data[3] = res.data[3] & (~1);
	
	//string test = BitManipulation::QIntToBinStr(res);
	return res;
}

QInt& BitManipulation::rightRotate(const QInt& x)
{
	int mostRightBit = x.data[3] & 1;
	QInt res = BitManipulation::logicalRightShift(x, 1);

	if (mostRightBit == 1)
		res.data[0] = res.data[0] | (1 << 31);
	else
		res.data[0] = res.data[0] & (~(1 << 31));
	return res;
}



