#include "QInt.h"
//  -----------------------
// | Tính Toán Trên Chuỗi |
//  -----------------------
/* Hàm chia chuỗi cho 2*/
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

//Cấu trúc dữ liệu map chứa các giá trị nhị phân tương ứng với thập lục phân
map<string, string> BinToHexValue()
{
	map<string, string>mp;
	mp["0000"] = "0";
	mp["0001"] = "1";
	mp["0010"] = "2";
	mp["0011"] = "3";
	mp["0100"] = "4";
	mp["0101"] = "5";
	mp["0110"] = "6";
	mp["0111"] = "7";
	mp["1000"] = "8";
	mp["1001"] = "9";
	mp["1010"] = "A";
	mp["1011"] = "B";
	mp["1100"] = "C";
	mp["1101"] = "D";
	mp["1110"] = "E";
	mp["1111"] = "F";
	return mp;
}
//Cấu trúc dữ liệu map chứa các giá trị thập lục phân tương ứng nhị phan
map<string, string> HexToBinValue()
{
	map<string, string>mp;
	mp["0"] = "0000";
	mp["1"] = "0001";
	mp["2"] = "0010";
	mp["3"] = "0011";
	mp["4"] = "0100";
	mp["5"] = "0101";
	mp["6"] = "0110";
	mp["7"] = "0111";
	mp["8"] = "1000";
	mp["9"] = "1001";
	mp["A"] = "1010";
	mp["B"] = "1011";
	mp["C"] = "1100";
	mp["D"] = "1101";
	mp["E"] = "1110";
	mp["F"] = "1111";
	return mp;
}

//  -----------------------
// |   Nhóm Hàm Hỗ trợ    |
//  -----------------------
/*Hàm so sánh số QInt a, b với đầu ra:
- a = b: 0
- a < b: -1
- a > b: 1
*/
int QInt::compare(QInt a, QInt b)
{
	int sign1 = 0, sign2 = 0;
	if (((a.data[0] >> 31) & 1) == 1)
		sign1 = 1;
	if (((b.data[0] >> 31) & 1) == 1)
		sign2 = 1;

	if (sign1 == 0 && sign2 == 1)
		return 1;
	if (sign1 == 1 && sign2 == 0)
		return -1;

	if (sign1 == 1 && sign2 == 1) {
		a.convert2complement();
		b.convert2complement();
	}

	int comp = 0;
	bool flag = false;
	for (int i = 0; i < 4; i++) {
		for (int j = 31; j >= 0; j--) {
			if (((a.data[i] >> j) & 1) > ((b.data[i] >> j) & 1)) {
				comp = 1;
				flag = true;
				break;
			}
			else if (((a.data[i] >> j) & 1) < ((b.data[i] >> j) & 1)) {
				comp = -1;
				flag = true;
				break;
			}
		}
		if (flag)
			break;
	}

	if (comp == 0)
		return 0;

	if (sign1 == 1 && sign2 == 1) {
		comp = 0 - comp;
	}
	return comp;
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
	while (i >= 0 && ((data[i / 32] >> (31 - i % 32)) & 1) == 0) {
		i--;
	}
	i--;
	while (i >= 0) {
		data[i / 32] ^= (1 << (31 - i % 32));
		i--;
	}
}
//  -----------------------------------------
// |   Nhóm Hàm Định nghĩ toán tử so sánh   |
//  -----------------------------------------

bool QInt::operator<(QInt a)
{
	if (QInt::compare(*this, a) == -1)
		return true;
	return false;
}

bool QInt::operator>(QInt a)
{
	if (QInt::compare(*this, a) == 1)
		return true;
	return false;
}

bool QInt::operator==(QInt a)
{
	if (QInt::compare(*this, a) == 0)
		return true;
	return false;
}

bool QInt::operator<=(QInt a)
{
	int res = QInt::compare(*this, a);
	if (res == -1 || res == 0)
		return true;
	return false;
}

bool QInt::operator>=(QInt a)
{
	int res = QInt::compare(*this, a);
	if (res == 1 || res == 0)
		return true;
	return false;
}

QInt& QInt::operator=(const QInt& n)
{
	QNumeric::operator=(n);
	return (*this);
}

QInt QInt::operator+(const QInt& q) const
{
	QInt a = *this;
	QInt b = q;
	QInt ans;
	int k = 127;
	int temp = 0;
	bool x;
	bool y;
	QInt temp1 = a;
	if (temp1.data[0] >> 31 & 1)
		temp1.convert2complement();
	QInt temp2 = b;
	if (temp2.data[0] >> 31 & 1)
		temp2.convert2complement();
	while (k >= 1)
	{
		x = a.data[k / 32] & 1;
		y = b.data[k / 32] & 1;
		if (x == 1 && y == 1)
		{
			if (temp == 1)
				ans.data[k / 32] |= (1 << (31 - k % 32));
			temp = 1;
		}
		else
		{
			if ((x == 0 && y == 1) || (x == 1 && y == 0))
			{
				if (temp == 0)
					ans.data[k / 32] |= (1 << (31 - k % 32));
				else
					temp = 1;
			}
			else
			{
				if (x == 0 && y == 0)
				{
					if (temp == 1)
					{
						ans.data[k / 32] |= (1 << (31 - k % 32));
						temp = 0;
					}
				}
			}
		}
		a.data[k / 32] = a.data[k / 32] >> 1;
		b.data[k / 32] = b.data[k / 32] >> 1;
		k--;
	}
	if ((a.data[0] >> 31 & 1) == (b.data[0] >> 1 & 1))
	{
		if (a.data[0] >> 1 & 1)
			ans.data[0] |= (1 << 31);
	}
	else
	{
		if (temp1 < temp2)
		{
			if (b.data[0] >> 1 & 1)
				ans.data[0] |= (1 << 31);
		}
		else if (temp1 > temp2)
		{
			if (a.data[0] >> 1 & 1)
				ans.data[0] |= (1 << 31);
		}
	}
	return ans;
}

QInt QInt::operator-(const QInt& q) const
{
	QInt a = *this;
	QInt b = q;
	b.convert2complement();
	QInt ans = a + b;
	return ans;
}

QInt QInt::operator*(const QInt& q) const
{
	QInt a = *this;
	QInt b = q;
	QInt ans, temp;
	bool sign = 0;
	if (a.data[0] >> 31 & 1)
	{
		sign = 1 - sign;
		a.convert2complement();
	}
	if (b.data[0] >> 31 & 1)
	{
		sign = 1 - sign;
		b.convert2complement();
	}
	int k = 127;
	while (!(b == temp))
	{
		if (b.data[k / 32] & 1)
			ans = ans + a;
		a = a << 1;
		b = b >> 1;
	}
	if (sign == 1)
		ans.convert2complement();
	return ans;
}

QInt QInt::operator/(const QInt& q) const
{
	QInt a = *this;
	QInt b = q;
	QInt ans, mod, temp;
	bool sign_a = 0, sign_b = 0;
	if (a.data[0] >> 31 & 1)
	{
		sign_a = 1;
		a.convert2complement();
	}
	if (b.data[0] >> 31 & 1)
	{
		sign_b = 1;
		b.convert2complement();
	}
	int x = 0;
	while (x < 128)
	{
		if (a.data[x / 32] >> (31 - x % 32) & 1)
			break;
		x++;
	}
	while (x <= 127)
	{
		mod = mod << 1;
		if (a.data[x / 32] >> (31 - x % 32) & 1)
		{
			mod.data[3] |= 1;
		}
		ans = ans << 1;
		if (mod >= b)
		{
			ans.data[3] |= 1;
			mod = mod - b;
		}
		x++;
	}
	if (mod >= b)
	{
		ans.data[3] |= 1;
		mod = mod - b;
	}
	if (sign_a != sign_b)
		ans.convert2complement();
	return ans;
}

QInt QInt::operator%(const QInt& q) const
{
	QInt a = *this;
	QInt b = q;
	QInt ans, mod, temp;
	bool sign_a = 0, sign_b = 0;
	if (a.data[0] >> 31 & 1)
	{
		sign_a = 1;
		a.convert2complement();
	}
	if (b.data[0] >> 31 & 1)
	{
		sign_b = 1;
		b.convert2complement();
	}
	int x = 0;
	while (x < 128)
	{
		if (a.data[x / 32] >> (31 - x % 32) & 1)
			break;
		x++;
	}
	while (x <= 127)
	{
		mod = mod << 1;
		if (a.data[x / 32] >> (31 - x % 32) & 1)
		{
			mod.data[3] |= 1;
		}
		ans = ans << 1;
		if (mod >= b)
		{
			ans.data[3] |= 1;
			mod = mod - b;
		}
		x++;
	}
	if (mod >= b)
	{
		ans.data[3] |= 1;
		mod = mod - b;
	}
	if (sign_a == 1 && !(mod == temp))
		mod.convert2complement();
	return mod;
}
//ok rồi
string QInt::toBin() const
{
	QInt a = *this;
	string temp = "";
	bool bit = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 31; j >= 0; j--)
		{
			bit = (a.data[i] >> j) & 1;
			temp = temp + char(bit + '0');
		}
	}
	while (temp[0] == '0')
		temp.erase(0, 1);
	return temp;
}
//ok rồi
string QInt::toHex() const
{
	QInt x = *this;
	string temp = "";
	int k = 0;
	map<string, string> mp = BinToHexValue();
	string res = "";

	for (int i = 0; i < 4; i++) {
		for (int j = 31; j >= 0; j--) {
			if (k != 4) {
				if (((x.data[i] >> j) & 1) == 1)
					temp += "1";
				else
					temp += "0";
				k++;
			}
			if (k == 4) {
				k = 0;
				if (res != "" || temp != "0000")
					res += mp[temp];
				temp = "";
			}
		}
	}

	return res;
}
//ok rồi
string QInt::toDec() const
{
	QInt a = *this;
	for (int i = 0; i < 4; i++)
		a.data[i] = data[i];
	int x, sign = 0;
	string powerOf2, res = "";
	if (((a.data[0] >> 31) & 1) == 1) {
		sign = 1;
		a.convert2complement();
	}

	for (int i = 0; i < 4; i++) {
		x = a.data[i];
		for (int j = 0; j < 32; j++) {
			if (i == 0 && j == 31)
				continue;
			if ((x & 1) == 1) {
				powerOf2 = Pow("2", (3 - i) * 32 + j);
				res = sum(res, powerOf2);
			}
			x >>= 1;
		}
	}
	if (sign == 1)
		res = "-" + res;
	if (res.length() == 0)
		return "0";
	else
		return res;
}
//ok rồi
QInt& QInt::fromBin(const string& s)
{
	int i = 127;
	int d = s.length() - 1;
	while (d >= 0)
	{
		if (s[d] == '1')
			setBit(i, 1);
		d--;
		i--;
	}
	return *this;
}//Ok rồi
//ok rồi
QInt& QInt::fromDec(const string&st)
{
	string s = st;
	//QInt a;
	int sign = 0;
	if (s[0] == '-') {
		s.erase(0, 1);
		sign = 1;
	}

	int i = 127;
	while (s.length() > 1 || (s.length() == 1 && s[0] != 0)) {
		if ((s[s.length() - 1] - '0') % 2 == 1) {
			setBit(i, 1);
		}
		s = divideBy2(s);
		i--;
	}
	if (sign == 1)
		QInt::convert2complement();
	/*for (int i = 0; i < 4; i++)
		cout << a.data[i] << " ";*/
	return *this;
}//ok rồi
//ok rồi
QInt& QInt::fromHex(const string& st)
{
	map<string, string> mp = HexToBinValue();
	string tmp, hex;
	string s = st;
	int i = 127;
	while (s.length() > 0) {
		tmp = s[s.length() - 1];
		hex = mp[tmp];
		for (int j = 3; j >= 0; j--) {
			if (hex[j] == '1')
				setBit(i, 1);//a.data[i / 32] |= 1 << (31 - (i % 32));
			i--;
		}
		s.erase(s.length() - 1, 1);
	}
	return *this;
}
//ok rồi
istream& operator>>(istream& is, QInt& a)
{
	string s;
	is >> s;
	a.fromDec(s);
	/*for (int i = 0; i < 4; i++)
		cout << a.data[i] << " ";*/
	//cout << a.toHex();
	return is;
}
//ok rồi
ostream& operator<<(ostream& os, QInt a)
{
	os << a.toDec();
	return os;
}

QInt::~QInt()
{
}