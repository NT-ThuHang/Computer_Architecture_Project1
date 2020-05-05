#include "Qfloat.h"

string Qfloat::divideBy2(string s)
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

string Qfloat::sum(string a, string b)
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

string Qfloat::multiply(string a, int b)
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
string Qfloat::multiplication(string a, string b)
{
	string ans = "";
	string res = "";
	int n = b.length();
	for (int i = 0; i < b.length(); i++) {
		res = "";
		for (int k = 0; k < i; k++)
			res += "0";
		string t = Qfloat::multiply(a, b[n - 1 - i] - '0');
		res = t + res;
		ans = sum(ans, res);
	}
	return ans;
}

/* Hàm tính x^k, với x: chuỗi, k: số nguyên */
string Qfloat::Pow(string x, int k)
{
	if (k == 0)
		return "1";
	if (k == 1)
		return x;
	string tmp = Pow(x, k / 2);
	tmp = Qfloat::multiplication(tmp, tmp);
	if (k % 2 == 1)
		return Qfloat::multiplication(tmp, x);
	else
		return tmp;
}

string decimalSolve(string decimal, string &res)
{
	int old_len;
	if (decimal.length() == 0)
		return "";
	old_len = decimal.length();
	decimal = Qfloat::multiply(decimal, 2);
	if (decimal.length() > old_len) {
		decimal.erase(0, 1);
		res += "1";
	}
	else
		res += "0";

	int j = decimal.length() - 1;
	while (j >= 0 and decimal[j] == '0') {
		decimal.erase(j, 1);
		j--;
	}
	return decimal;
}

string Qfloat::negativePowOf2(string decimal)
{
	if (decimal.length() == 0)
		return "";

	int n = decimal.length();
	string pow2 = "1";
	for (int i = 0; i < n; i++)
		pow2 += "0";

	string res = "";
	for (int i = 0; i < n; i++) {
		pow2 = Qfloat::divideBy2(pow2);
		if (decimal[i] == '1')
			res = sum(res, pow2);
	}

	string added0 = "";
	for (int i = 0; i < n - res.length(); i++)
		added0 += "0";
	return added0 + res;
}

bool Qfloat::isZero()
{
	for (int i = 0; i < 4; i++) {
		if (data[i] != 0)
			return false;
	}
	return true;
}

bool Qfloat::isInf()
{
	for (int i = 1; i <= 15; i++) {
		if (((data[i / 32] >> (31 - i % 32)) & 1) != 1)
			return false;
	}
	for (int i = 16; i < 32; i++) {
		if (((data[i / 32] >> (31 - i % 32)) & 1) != 0)
			return false;
	}
	if ((data[1] != 0) || (data[2] != 0) || (data[3] != 0))
		return false;
	return true;
}

bool Qfloat::isNaN()
{
	for (int i = 1; i <= 15; i++) {
		if (((data[i / 32] >> (31 - i % 32)) & 1) != 1)
			return false;
	}
	for (int i = 16; i < 32; i++) {
		if (((data[i / 32] >> (31 - i % 32)) & 1) != 0)
			return true;
	}
	if ((data[1] != 0) || (data[2] != 0) || (data[3] != 0))
		return true;
	return false;
}



void Qfloat::ScanQfloat(string s, int k)
{
	string integral = "", res = "", decimal = "", temp;
	int expo, i, old_len, j, r;
	bool haveIntegral = false, haveDecimal = false;
	if (s.length() == 0)
		return;

	if (s[0] == '-') {
		s.erase(0, 1);
		data[0] |= (1 << 31);
	}
	for (i = 0; i < s.length(); i++) {
		if (s[i] == '.')
			break;
		integral += s[i];
	}
	
	if (integral != "0")
		haveIntegral = true;

	for (i = i + 1; i < s.length(); i++)
		decimal += s[i];

	if (decimal.length() > 0)
		haveDecimal = true;

	while (integral != "" && integral != "0") {
		if ((integral[integral.length() - 1] - '0') % 2 != 0)
			res = '1' + res;
		else
			res = '0' + res;
		integral = Qfloat::divideBy2(integral);
	}

	if (haveIntegral) {
		expo = res.length() - 1;
		res.erase(0, 1);
	}
	else {
		expo = 0;
		i = 0;
		while (haveDecimal) {
			decimal = decimalSolve(decimal, res);
			if (res.length() > 0 && res[res.length() - 1] == '1') {
				expo = -1 * res.length();
				res.erase(0, res.length());
				break;
			}
			i++;
		}
	}

	for (i = res.length(); i <= 112; i++) {
		if (decimal == "") {
			for (int j = i; j <= 112; j++)
				res += "0";
			break;
		}
		decimal = decimalSolve(decimal, res);
	}

	if (res[res.length() - 1] == '1') {
		i = res.length() - 2;
		while (i >= 0) {
			if (res[i] == '1')
				res[i] = '0';
			else {
				res[i] = '1';
				break;
			}
			i--;
		}
	}
	res.erase(res.length() - 1, 1);

	cout << "res length: " << res.length() << endl;
	//cout << expo << endl;
	expo += k;
	i = 15;
	while (expo > 0) {
		if (expo % 2 == 1)
			data[0] |= (1 << (31 - i));
		expo /= 2;
		i--;
	}

	i = 16;
	while (i < 128) {
		if (res[i - 16] == '1')
			data[i / 32] |= (1 << 31 - (i % 32));
		i++;
	}

	
	for (int i = 0; i < 4; i++) {
		for (int j = 31; j >=0; j--) {
			int x = (data[i] >> j) & 1;
			cout << x;
		}
		cout << endl;
	}
}

string Qfloat::PrintQfloat()
{
	int sign = 0, i;
	if (((data[0] >> 31) & 1) == 1)
		sign = 1;
	
	if (this->isZero())
		return "0";
	
	if (this->isInf()) {
		if (sign == 1)
			return "-Inf";
		else
			return "Inf";
	}

	if (this->isNaN())
		return "NaN";

	Qfloat temp = *this;
	int expo = 0;
	bool haveIntegral = true, haveDecimal = false;
	for (int i = 1; i <= 15; i++) {
		if (((temp.data[0] >> (31 - i)) & 1) == 1)
			expo |= (1 << (15 - i));
		/*for (int j = 31; j >= 0; j--) {
			int x = (expo >> j) & 1;
			cout << x;
		}
		cout << endl;*/
	}
	expo -= 16383;
	cout << expo << endl;

	string integral = "", decimal = "";
	int count = 0;
	if (expo > 0) {
		i = 16;
		integral = "1";
		while (count < expo) {
			if (i < 128)
				integral += to_string((data[i / 32] >> (31 - i % 32)) & 1);
			else
				integral += "0";
			i++;
			count++;
		}
	}
	else if (expo == 0) {
		int countBit1 = 0;
		int j = 16;
		while (j < 128) {
			if (((data[j / 32] >> (31 - j % 32)) & 1) == 1)
				countBit1++;
			j++;
		}
		
		if (countBit1 == 0) {
			integral = "0";
			haveDecimal = false;
		}
		else
			integral = "1";
		i = 16;
	}
	else {
		integral = "0";
		for (int i = 0; i < abs(expo) - 1; i++)
			decimal += "0";
		decimal += "1";
		i = 16;
	}

	while (i < 128) {
		decimal += to_string((data[i / 32] >> (31 - i % 32)) & 1);
		i++;
	}

	string res = "", powerOf2 = "";
	int n = integral.length();
	for (int i = 0; i < n; i++) {
		if (integral[i] == '1') {
			powerOf2 = Qfloat::Pow("2", n - 1 - i);
			res = sum(res, powerOf2);
		}
	}
	if (res.length() == 0)
		res = "0";
	
	//Xóa những số 0 ở cuối dãy decimal
	while (decimal.length() > 0 && decimal[decimal.length() - 1] == '0')
		decimal.erase(decimal.length() - 1, 1);


	string tmp = negativePowOf2(decimal);

	if (tmp.length() == 0) {
		if (sign == 1)
			return "-" + res;
		else
			return res;
	}
	
	if (sign == 1)
		return "-" + res + "." + tmp;
	return res + "." + tmp;
}

Qfloat::Qfloat()
{
}

Qfloat::~Qfloat()
{
}
