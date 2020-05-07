#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "QInt.h"
#include "Qfloat.h"
using namespace std;
int main()
{
	freopen("Text.txt", "rt", stdin);
	/*string st;
	cin >> st;
	cout << st.length();*/
	QInt a, b;
	cin >> a;
	cin >> b;
	cout << "a la: " << a << endl;
	cout << "b la: " << b << endl;
	QInt c;
	c = (a >> 2);
	cout << "Test dich phai: " << c << endl;
	c = a << 2;
	cout << "Test dich trai: " << c << endl;
	c = b.arithmeticRightShift(2);
	cout << "Test dich phai so hoc" << c<<endl;
	c = a.rol(1);
	cout << "Test dich rol: " << c << endl;
	c = a.ror(2);
	cout << "Test dich ror: " << c << endl;
	c = ~a;
	cout << "Test Toan Tu ~: " << c << endl;
	c = a & b;
	cout << "Test &: " << c << endl;
	c = a | b;
	cout << "Test |: " << c << endl;
	c = a ^ b;
	cout << "Test ^: " << c << endl;
	if (a == b)
	{
		cout << 1 << endl;
	}
	else
		cout << 0 << endl;
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
	Qfloat x, y;
	cin >> x;
	cin >> y;
	cout << "So x la: " << x << endl;
	cout << "So y la: " << y << endl;
	return 0;
}