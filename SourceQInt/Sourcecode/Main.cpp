#define _CRT_SECURE_NO_WARNINGS
#include "QInt.h"
#include "Conversion.h"
using namespace std;
int main()
{
	freopen("Test.txt", "rt", stdin);
	QInt a, b, c;
	string st1;// test Nhi phan;
	string st2;// test Thap Luc Phan
	cin >> a;
	cin >> b;
	cin >> st1;
	cin >> st2;
	cout << a << endl << b << endl;
	if (a == b)
	{
		cout << 1<<endl;
	}
	else
		cout << 0<<endl;
	c = a << 4;
	cout << c <<endl;
	c = a + b;
	cout << "Tong la:" << c << endl;
	c = a - b;
	cout << "Hieu la:" << c << endl;
	c = a * b;
	cout << "Tich la" << c << endl;
	c = a / b;
	cout << "Thuong (nguyen) la:" << c << endl;
	c = a % b;
	cout << "Du: " << c << endl;
	Conversion convert;
	cout << "Chuyen a sang nhi phan " << convert.DecToBin(a)<<endl;
	cout << "Chuyen " << st1 << " sang thap phan(he 10) " << convert.BinToDec(st1)<<endl;
	cout << "Chuyen " << st1 << " sang thap luc phan(he 16) " << convert.BinToHex(st1) << endl;
	cout << "Chuyen " << st2 << " sang thap phan(he 10) " << convert.HexToDec(st2);
	return 0;
}