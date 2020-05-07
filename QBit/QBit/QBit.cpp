#include "QBit.h"
//ok rồi
void QBit::setBit(int pos, int bit)
{
	if (bit==1)
		data[pos / 32] |= (1 << (31 - pos % 32));
}
//ok rồi
int QBit::getBit(int pos)const
{
	return ((data[pos / 32] >> (31 - pos % 32)) & 1);
}
//ok rồi
QBit& QBit::operator =(const QBit& n) {
	for (int i = 0; i < 4; i++)
		data[i] = n.data[i];
	return (*this);
}
//ok rồi
QBit QBit::operator>>(int k) const//dịch phải
{
	QBit a = *this;
	while (k != 0)
	{
		bool x = 0, y = 0;
		for (int i = 0; i < 4; i++)
		{
			x = a.data[i] & 1;
			a.data[i] = a.data[i] >> 1;
			if (y == 1)
				a.data[i] |= (1 >> 31);
			y = x;
		}
		k--;
	}
	return a;
}
//ok rồi
QBit QBit::operator<<(int k)const
{
	QBit a = *this;
	while (k != 0)
	{
		bool x = 0, y = 0;
		for (int i = 3; i >= 0; i--)
		{
			x = a.data[i] >> 31 & 1;
			a.data[i] = a.data[i] << 1;
			if (y == 1)
				a.data[i] |= 1;
			y = x;
		}
		k--;
	}
	return a;
}
//ok rồi
QBit QBit::arithmeticRightShift(int k)const
{
	QBit x = *this;
	// Lưu bit ngoài cùng bên trái của data[0]
	int mostLeftBit = (x.data[0] >> 31) & 1;
	if (mostLeftBit == 0)
		return x >> k;

	// mostLeftBit = 1
	if (k > 127)
	{
		// toàn bộ bit bị dịch ra hết, x sẽ chứa toàn là bit 1 => x = -1
		for (int i = 0; i < 4; i++)
			x.data[i] = -1;
	}
	else
	{
		for (int i = 0; i < k; i++)
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
			// Gán bit 1 vào đầu data[0] sau mỗi lần dịch (theo quy tắc dịch số học)
			x.data[0] = x.data[0] | (1 << 31);
		}
	}
	return x;
}
//ok rồi
QBit QBit::rol(int k) const
{
	QBit x = *this;
	for (int i = 0; i < k; i++)
	{
		// Lưu bit ngoài cùng bên trái của data[0]
		int mostLeftBit = (x.data[0] >> 31) & 1;
		x = x << 1;
		// Chuyển bit về cuối
		if (mostLeftBit == 1)
		{
			x.data[3] = x.data[3] | 1;
		}
	}
	return x;
}
//ok rồi
QBit QBit::ror(int k) const
{
	QBit x = *this;
	for (int i = 0; i < k; i++)
	{
		// Lưu bit ngoài cùng bên phải của data[3]
		int mostRightBit = x.data[0] & 1;

		QBit x = x >> 1;
		// Chuyển bit về đầu
		if (mostRightBit == 1)
		{
			x.data[0] = x.data[0] | (1 << 31);
		}
	}
	return x;
}
//ok rồi
QBit QBit::operator~() const
{
	QBit temp = *this;
	int i = 127;
	do
	{
		temp.data[i / 32] = (1 << (31 - (i % 32))) ^ temp.data[i / 32];
		i--;
	} while (i >= 0);
	return temp;
}
//ok rồi
QBit QBit::operator|(const QBit& n) const
{
	QBit x = *this;
	QBit temp;
	int i = 127;
	bool bitx, bity;
	do
	{
		bitx = (x.data[i / 32] >> (31 - (i % 32)) & 1);
		bity = (n.data[i / 32] >> (31 - (i % 32)) & 1);
		if (bitx + bity != 0)
			temp.data[i / 32] |= (1 << (31 - (i % 32)));
		i--;
	} while (i >= 0);
	return temp;
}
//ok rồi
QBit QBit::operator&(const QBit& y) const
{
	QBit x = *this;
	QBit temp;
	int i = 127;
	bool bitx, bity;
	do
	{
		bitx = (x.data[i / 32] >> (31 - (i % 32)) & 1);
		bity = (y.data[i / 32] >> (31 - (i % 32)) & 1);
		if (bitx + bity == 2)
			temp.data[i / 32] |= (1 << (31 - (i % 32)));
		i--;
	} while (i >= 0);
	return temp;
}
//ok rồi
QBit QBit::operator^(const QBit& y) const
{
	QBit temp;
	QBit x = *this;
	int i = 127;
	bool bitx, bity;
	do
	{
		bitx = (x.data[i / 32] >> (31 - (i % 32)) & 1);
		bity = (y.data[i / 32] >> (31 - (i % 32)) & 1);
		if (bitx + bity == 1)
			temp.data[i / 32] = (1 << (31 - (i % 32))) | temp.data[i / 32];
		i--;
	} while (i >= 0);
	return temp;
}
//ok rồi
QBit::QBit(const QBit& a)
{
	for (int i = 0; i < 4; i++)
		data[i] = a.data[i];
}
//ok rồi
QBit::QBit()
{
	for (int i = 0; i < 4; i++)
		data[i] = 0;
}
//ok rồi
QBit::~QBit()
{
}


