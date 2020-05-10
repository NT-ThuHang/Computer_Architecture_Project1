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
/*Hàm Cộng trên chuỗi 2 số dùng cho cả số nguyên lẫn chấm động*/
void Add(string& st, string x)
{
	bool stt1 = 1 - (st.find(".") == string::npos);
	bool stt2 = 1 - (x.find(".") == string::npos);
	int a = st.length(), b = x.length();
	if (stt1)
		a = st.find(".");
	if (stt2)
		b = x.find(".");
	if (a > b)
		x.insert(0, a - b, '0');
	else
		st.insert(0, b - a, '0');
	a = a > b ? a : b;
	b = a;
	if (stt1 == 1 && stt2 == 0)
	{
		x.insert(x.length(), 1, '.');
		x.insert(a + 1, st.length() - x.length(), '0');
	}
	else if (stt1 == 0 && stt2 == 1)
	{
		st.insert(st.length(), 1, '.');
		st.insert(a + 1, x.length() - st.length(), '0');
	}
	else
		if (stt1 == 1 && stt2 == 1)
		{
			if (st.length() < x.length())
				st.insert(st.length(), x.length() - st.length(), '0');
			else
				x.insert(x.length(), st.length() - x.length(), '0');
		}
	int l1 = st.length();
	int temp = 0;
	int res;
	string ans;
	for (int i = l1 - 1; i >= 0; i--)
	{
		if (st[i] == '.')
		{
			ans.insert(0, 1, '.');
			continue;
		}
		res = (st[i] - '0') + (x[i] - '0') + temp;
		ans.insert(0, 1, (char)(res % 10 + '0'));
		temp = res / 10;
	}
	if (temp != 0)
		ans.insert(0, 1, (char)(temp + '0'));
	st = ans;
}
// DivideBy2 chia số nguyên (co du)
void divideBy2HaveMod(string& st)
{
	int n = st.length();
	int temp = 0;
	string ans;
	for (int i = 0; i < st.length(); i++)
	{
		if (st[i] == '.')
		{
			ans.insert(ans.length(), 1, '.');
			continue;
		}
		temp = temp * 10 + (st[i] - '0');
		ans.insert(ans.length(), 1, (char)(temp / 2 + '0'));
		temp = temp % 2;
	}
	while (ans[0] == '0')
		ans.erase(0, 1);
	if (ans[0] == '.')
		ans.insert(0, 1, '0');
	if (temp != 0 && ans.find(".") == string::npos)
		ans.insert(ans.length(), 1, '.');
	while (temp != 0)
	{
		temp = temp * 10;
		ans.insert(ans.length(), 1, (char)(temp / 2 + '0'));
		temp = temp % 2;
	}
	st = ans;
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

Qfloat& Qfloat::operator=(const Qfloat& n)
{
	return (*this);
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
	Qfloat a = *this;

	if (a.isInf()) {
		if (a.isNegative()) return "-Inf";
		return "Inf";
	}
	if (a.isNaN())
		return "NaN";
	if (a.isZero())
		return "0";
	if (a.isDenormalized())
		return "Denormalized";

	//Lấy exp;
	int exp = 0;
	int vt = 15;
	while (vt > 0)
	{
		if ((a.data[vt / 32] >> (31 - vt % 32)) & 1)
			exp |= (1 << (15 - vt));
		vt--;
	}
	exp = exp - K;
	// Vị trí số 1 đầu tiên
	//Với trường hợp số biểu diễn được thì vị trí số 1 đầu tiên luôn bằng 0
	//Nếu trường hợp không chuẩn hóa được thì chưa chắc
	int VTso1 = 0;
	if (exp == -K)
	{
		exp = -K + 1;
		for (int i = 16; i < 128; i++)
			if (a.getBit(i) == 1)
			{
				VTso1 = i;
				break;
			}
		if (VTso1 == 0)
			return "0";
	}
	string temp;// lưu giá trị nhị phân
	vt = 16;
	while (vt < 128)
	{
		if ((a.data[vt / 32] >> (31 - vt % 32)) & 1)
			temp.insert(temp.length(), 1, '1');
		else
			temp.insert(temp.length(), 1, '0');
		vt++;
	}
	while (temp.length() > 0 && temp[temp.length() - 1] == '0')
		temp.erase(temp.length() - 1, 1);
	temp.insert(0, 1, '1');
	string x = "0";//phan nguyen
	if (exp < 0)
	{
		while (exp < 0)
		{
			temp.insert(0, 1, '0');
			exp++;
		}
	}
	else if (exp > 112)
	{
		temp.insert(temp.length(), exp - 112, '1');
	}
	string tmp = "1";
	for (int i = exp; i >= 0; i--)
	{
		if (temp[i] == '1')
			Add(x, tmp);
		tmp=Multiply(tmp,2);
	}
	string tmp1 = "1";
	for (int i = exp + 1; i < temp.length(); i++)
	{
		divideBy2HaveMod(tmp1);
		if (temp[i] == '1')
		{
			Add(x, tmp1);
		}
	}
	if ((a.data[0] >> 31) & 1)
		x.insert(0, 1, '-');
	return x;
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


