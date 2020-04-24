#include "QInt.h"

void DivideString(string& st, int k)
{
	int temp = 0, ans;//temp la bien nho //ans la bien luu ket qua thanh phan
	long n = st.length();
	while (n != 0)
	{
		int x = st[0] - '0';//chuyen ki tu so thanh so nguyen
		temp = temp * 10 + x;
		st.insert(st.length(), 1, (char)temp / k + '0');
		temp = temp % k;
		st.erase(0, 1);
		n--;
	}
	while (st[0] == '0')
	{
		st.erase(0, 1);
	}
}
istream& operator >>(istream& is, QInt& a)
{
	string st;
	is >> st;
	long k = 0;
	while (st.length() != 0)
	{
		if ((st[st.length() - 1] - '0') % 2 == 1)
		{
			a.data[k / 32] += pow(2, k % 32);

		}
		k++;
		DivideString(st, 2);
	}
	return is;
}
ostream& operator <<(ostream& os, QInt a)
{
	string st;
	for (int i = 0; i < 4; i++)
	{
		if (a.data[i] == 0)
			continue;
		while (a.data[i] != 0)
		{
			st.insert(0, 1, (char)(a.data[i] % 2 + '0'));
			a.data[i] /= 2;
		}
	}
	os << st;
	return os;
}
QInt::QInt()
{
	for (int i = 0; i < 4; i++)
		data[i] = 0;
}
QInt::~QInt()
{

}
