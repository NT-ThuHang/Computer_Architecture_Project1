#include "Qfloat.h"

// Hàm set bit tại vị trí pos
void Qfloat::setBit(int pos, int bit)
{
	if (bit == 1)
		data[pos / 32] |= (1 << (31 - pos % 32));
}

// Hàm lấy bit tại vị trí pos
int Qfloat::getBit(int pos)
{
	return ((data[pos / 32] >> (31 - pos % 32)) & 1);
}

/*Chi chuoi cho 2 không lấy phầnn dư*/
string DivideBy2(string s)
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

// Hàm cộng 2 chuỗi
string Sum(string a, string b)
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

/*Nhan chuoi cho 1 so nguyen*/
string Multiply(string a, int b)
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
string Multiplication(string a, string b)
{
	string ans = "";
	string res = "";
	int n = b.length();
	for (int i = 0; i < b.length(); i++) {
		res = "";
		for (int k = 0; k < i; k++)
			res += "0";
		string t = Multiply(a, b[n - 1 - i] - '0');
		res = t + res;
		ans = Sum(ans, res);
	}
	return ans;
}

/* Hàm tính x^k, với x: chuỗi, k: số nguyên */
string Power(string x, int k)
{
	if (k == 0)
		return "1";
	if (k == 1)
		return x;
	string tmp = Power(x, k / 2);
	tmp = Multiplication(tmp, tmp);
	if (k % 2 == 1)
		return Multiplication(tmp, x);
	else
		return tmp;
}

// Hàm nhân phần thập phân cho 2 để chuyển về nhị phân của số thực
string decimalSolve(string decimal, string& res)
{
	int old_len;
	if (decimal.length() == 0)
		return "";
	old_len = decimal.length();
	decimal = Multiply(decimal, 2);
	if (decimal.length() > old_len) {
		decimal.erase(0, 1);
		res += "1";
	}
	else
		res += "0";

	int j = decimal.length() - 1;
	while (j >= 0 && decimal[j] == '0') {
		decimal.erase(j, 1);
		j--;
	}
	return decimal;
}

// Hàm tính phần thập phân của Qfloat ở dạng chuỗi
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
		pow2 = DivideBy2(pow2);
		if (decimal[i] == '1')
			res = Sum(res, pow2);
	}

	string added0 = "";
	for (int i = 0; i < n - res.length(); i++)
		added0 += "0";
	return added0 + res;
}

int Qfloat::compare(Qfloat a, Qfloat b)
{
	int sign1 = a.data[0] >> 31 & 1;
	int sign2 = b.data[0] >> 31 & 1;
	if (sign1 > sign2)
		return 1;
	else if (sign1 < sign2)
		return -1;
	int exp1 = 0, exp2 = 0;
	for (int i = 15; i > 0; i--)
	{
		if (a.data[i / 32] >> (31 - i % 32) & 1)
			exp1 |= (1 << (15 - i));
		if (b.data[i / 32] >> (31 - i % 32) & 1)
			exp2 |= (1 << (15 - i));
	}
	exp1 -= K;
	exp2 -= K;
	if (exp1 < exp2)
		return -1;
	else if (exp1 > exp2)
		return 1;
	int comp = 0;
	for (int i = 16; i < 128; i++)
	{
		if (((a.data[i / 32] >> (31 - i % 32) & 1) > ((b.data[i / 32] >> (31 - i % 32)) & 1)))
		{
			comp = 1;
			break;
		}
		else if (((a.data[i / 32] >> (31 - i % 32) & 1) < ((b.data[i / 32] >> (31 - i % 32)) & 1)))
		{
			comp = -1;
			break;
		}
	}
	if (comp == 0)
		return 0;
	if (sign1 == 1 && sign2 == 1)
		comp = 0 - comp;
	return comp;
}

// Hàm kiểm tra Qfloat có là số âm
bool Qfloat::isNegative()
{
	return (this->data[0] >> 31 & 1);
}

// Hàm kiểm tra Qfloat có là số 0
bool Qfloat::isZero()
{
	for (int i = 0; i < 4; i++) {
		if (data[i] != 0)
			return false;
	}
	return true;
}

// Hàm kiểm tra Qfloat có là số vô cùng
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

// Hàm kiểm tra Qfloat có là số NaN
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

// Hàm kiểm tra Qfloat có là số dạng không chuẩn
bool Qfloat::isDenormalized()
{
	for (int i = 1; i <= 15; i++) {
		if (((data[i / 32] >> (31 - i % 32)) & 1) != 0)
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

// Hàm reset data Qfloat = 0
void Qfloat::resetQfloat()
{
	for (int i = 0; i < 4; i++)
		data[i] = 0;
}

bool Qfloat::operator<(Qfloat a)
{
	if (Qfloat::compare(*this, a) == -1)
		return true;
	return false;
}

bool Qfloat::operator>(Qfloat a)
{
	if (Qfloat::compare(*this, a) == 1)
		return true;
	return false;
}

bool Qfloat::operator==(Qfloat a)
{
	if (Qfloat::compare(*this, a) == 0)
		return true;
	return false;
}

bool Qfloat::operator<=(Qfloat a)
{
	int res = Qfloat::compare(*this, a);
	if (res == -1 || res == 0)
		return true;
	return false;
}

bool Qfloat::operator>=(Qfloat a)
{
	int res = Qfloat::compare(*this, a);
	if (res == 1 || res == 0)
		return true;
	return false;
}

// Hàm chuyển từ Qfloat sang dấu chấm động
string Qfloat::DectoBin()
{
	Qfloat a = *this;
	string st;
	for (int i = 127; i >= 0; i--)
	{
		if ((a.data[i / 32] >> (31 - i % 32)) & 1)
			st.insert(0, 1, '1');
		else
			st.insert(0, 1, '0');
	}
	return st;
}

// Hàm xuất Qfloat
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

	if (this->isDenormalized())
		return "Denormalized";

	Qfloat temp = *this;

	int expo = 0;
	bool haveIntegral = true, haveDecimal = false;
	for (int i = 1; i <= 15; i++) {
		if (((temp.data[0] >> (31 - i)) & 1) == 1)
			expo |= (1 << (15 - i));
	}
	expo -= 16383;

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
			powerOf2 = Power("2", n - 1 - i);
			res = Sum(res, powerOf2);
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

// Hàm chuyển từ số chậm động sang Qfloat
Qfloat& Qfloat::BinToDec(const string& st)
{
	Qfloat a;

	for (int i = 127; i >= 0; i--)
	{
		if (st[i] == '1')
			a.setBit(i, 1);
	}
	return a;
}

// Hàm kiểm tra input của Qfloat
string Qfloat::checkInvalid(string s)
{
	string integral = "", res = "", decimal = "";
	int expo, i, j, r;
	bool haveIntegral = false, haveDecimal = false;
	if (s.length() == 0)
		return "NULL";

	if (s[0] == '-') {
		s.erase(0, 1);
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

	if ((integral == "0") && (decimal == "0")) {
		return "Valid";
	}

	while (integral != "" && integral != "0") {
		if ((integral[integral.length() - 1] - '0') % 2 != 0)
			res = '1' + res;
		else
			res = '0' + res;
		integral = DivideBy2(integral);
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

	cout << "expo: " << expo << endl;
	if (expo < (-1 * (1 << 14) - 2 - 112))
		return "Invalid";

	if (expo < (-1 * (1 << 14) - 2))
		return "Denormalized";

	if (expo > ((1 << 14) - 1))
		return "Invalid";

	return "Valid";
}

// Hàm đọc Qfloat dạng chuỗi số thực
Qfloat& Qfloat::ScanQfloat(const string& st)
{
	string s = st;
	string integral = "", res = "", decimal = "", temp;
	int expo, i, j, r;
	bool haveIntegral = false, haveDecimal = false;
	if (s.length() == 0)
		return *this;

	if (s == "0" || s == "-0") {
		this->resetQfloat();
		return *this;
	}

	if (s[0] == '-') {
		s.erase(0, 1);
		this->setBit(0, 1);
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

	if ((integral == "0") && (decimal == "0")) {
		this->resetQfloat();
		return *this;
	}

	while (integral != "" && integral != "0") {
		if ((integral[integral.length() - 1] - '0') % 2 != 0)
			res = '1' + res;
		else
			res = '0' + res;
		integral = DivideBy2(integral);
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

	// Cộng 1 vào dãy bit nếu bit đầu tiên bị cắt đi = 1
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
	expo += K;
	i = 15;
	while (expo > 0) {
		if (expo % 2 == 1)
			this->setBit(i, 1);
		expo /= 2;
		i--;
	}

	i = 16;
	while (i < 128) {
		if (res[i - 16] == '1')
			this->setBit(i, 1);
		i++;
	}
	return *this;
}

// Operator cin cho Qfloat
istream& operator>>(istream& is, Qfloat& a)
{
	string s;
	is >> s;
	a.ScanQfloat(s);
	return is;
}

// Operator cout cho Qfloat
ostream& operator<<(ostream& os, Qfloat a)
{
	os << a.PrintQfloat();
	return os;
}

Qfloat::Qfloat()
{
	for (int i = 0; i < 4; i++)
		data[i] = 0;
}

Qfloat::~Qfloat()
{
}


