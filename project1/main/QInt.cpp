﻿#include "QInt.h"

/*Hàm chia chuỗi cho 2
Đầu vào: chuỗi s
Đầu ra: chuỗi kết quả sau khi chia s cho 2
*/
string divideBy2(string s)
{
	int x;
	string res = "";
	int r = 0;
	for (int i = 0; i < s.length(); i++) {
		if (i == 0 && s[0] < '2') {
			r = 1;
			continue;
		}

		if (r == 0)
			x = s[i] - '0';
		else
			x = 10 + s[i] - '0';
		res += x / 2 + '0';
		r = x % 2;
	}
	return res;
}

/* Hàm cộng chuỗi a, b */
string sum(string a, string b)
{
	while (a.length() < b.length())
		a = "0" + a;
	while (a.length() > b.length())
		b = "0" + b;
	int r = 0, x;
	string res = "";
	for (int i = a.length() - 1; i >= 0; i--) {
		x = (a[i] - '0') + (b[i] - '0') + r;
		res = to_string(x % 10) + res;
		r = x / 10;
	}

	if (r > 0)
		res = to_string(r) + res;
	return res;
}

/* Hàm nhân chuỗi a với 1 số nguyên b */
string multiply(string a, int b)
{
	int r = 0, x;
	string res = "";
	for (int i = a.length() - 1; i >= 0; i--) {
		x = (a[i] - '0') * b + r;
		res = to_string(x % 10) + res;
		r = x / 10;
	}
	if (r > 0)
		res = to_string(r) + res;
	return res;
}

/* Hàm nhân chuỗi a và chuỗi b */
string multiplication(string a, string b)
{
	string ans = "";
	string res = "";
	int n = b.length();
	for (int i = 0; i < b.length(); i++) {
		res = "";
		for (int k = 0; k < i; k++)
			res += "0";
		string t = multiply(a, b[n - 1 - i] - '0');
		res = t + res;
		ans = sum(ans, res);
	}
	return ans;
}

/* Hàm tính x^k, với x: chuỗi, k: số nguyên */
string Pow(string x, int k)
{
	if (k == 0)
		return "1";
	if (k == 1)
		return x;
	string tmp = Pow(x, k / 2);
	tmp = multiplication(tmp, tmp);
	if (k % 2 == 1)
		return multiplication(tmp, x);
	else
		return tmp;
}

/*Hàm có 2 công dụng:
- Chuyển số dương sang số âm (ở dạng bù 2)
- Chuyển số âm (ở dạng bù 2) sang số dương
Cách hoạt động muốn chuyển sang số bù 2 và ngược lại:
- Nhìn từ phải sang trái, giữ nguyên các số 0 cho đến khi gặp số 1 đầu tiên (giữ nguyên số 1 đó)
- Đổi 0->1, 1->0 các bit còn lại
*/
void QInt::convert2complement()
{
	int i = 127;
	while (i >= 0 && data[i / 32] >> (31 - i % 32) == 0) {
		i--;
	}
	i--;
	while (i >= 0) {
		data[i / 32] ^= (1 << (31 - i % 32));
		i--;
	}
}

/* Hàm đọc dữ liệu cho QInt với đầu vào là chuỗi s */
void QInt::ScanQInt(string s)
{
	int sign = 0;
	if (s[0] == '-') {
		s.erase(0, 1);
		sign = 1;
	}
	
	int i = 127;
	while (s.length() > 1 || (s.length() == 1 && s[0] != 0)) {
		if ((s[s.length() - 1] - '0') % 2 == 1) {
			data[i / 32] |= 1 << (31 - (i % 32));
		}
		s = divideBy2(s);
		i--;
	}
	/*if (sign == 1)
		data[0] |= 1 << 31;*/
	if (sign == 1)
		this->convert2complement();
	/*for (int i = 0; i < 4; i++) {
		for (int j = 31; j >=0; j--) {
			int x = (data[i] >> j) & 1;
			cout << x;
		}
		cout << endl;
	}*/
}

/* Hàm xuất dữ liệu cho QInt */
string QInt::PrintQInt()
{
	int x, sign = 0;
	string powerOf2, res = "";
	if ((data[0] >> 31) & 1 == 1) {
		sign = 1;
		this->convert2complement();
	}

	for (int i = 0; i < 4; i++) {
		x = data[i];
		for (int j = 0; j < 32; j++) {
			if (i == 0 && j == 31)
				continue;
			if (x & 1 == 1) {
				powerOf2 = Pow("2", (3 - i) * 32 + j);
				res = sum(res, powerOf2);
			}
			x >>= 1;
		}
	}
	
	if (sign == 1)
		return "-" + res;
	return res;
}

QInt::QInt()
{
}


QInt::~QInt()
{
}
