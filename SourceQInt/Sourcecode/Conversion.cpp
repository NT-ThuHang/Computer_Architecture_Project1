#include "Conversion.h"

string Conversion::DecToBin(QInt a)
{
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

QInt Conversion::BinToDec(string s)
{
	QInt x;
	int i = 127;
	int d = s.length() - 1;
	while (d >= 0)
	{
		if (s[d] == '1')
			x.data[i / 32] = (1 << (31 - (i % 32))) | x.data[i / 32];
		d--;
		i--;
	}
	return x;
}

//Cấu trúc dữ liệu map chứa các giá trị nhị phân tương ứng với thập lục phân
map<string, string> Conversion::BinToHexValue()
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

/*Hàm chuyển từ chuỗi nhị phân sang chuỗi thập lục phân
INPUT: chuỗi nhị phân
OUTPUT: chuỗi thập lục phân*/
string Conversion::BinToHex(string s)
{
	//SetToBin(s); Doi cho nay xiu ne
	QInt a = Conversion::BinToDec(s);//Sua thanh cai nay ne
	string temp = "";
	int k = 0;
	map<string, string> mp = BinToHexValue();
	string res = "";

	for (int i = 0; i < 4; i++) {
		for (int j = 31; j >= 0; j--) {
			if (k != 4) {
				if (((a.data[i] >> j) & 1) == 1)
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

/*Hàm chuyển từ chuỗi thập phân sang chuỗi thập lục phân
INPUT: chuỗi số thập phân
OUTPUT : chuỗi thập lục phân*/
string Conversion::DecToHex(QInt x)
{
	/*QInt x;
	x.ScanQInt(s);*/

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

//Hàm set chuỗi thập lục phân vào QInt
QInt Conversion::HexToDec(string s)//nay doi cho kieu du lieu tra ve thanh QInt ne
{
	map<string, string>mp;
	mp["0"] = "0000";
	mp["0"] = "0001";
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
	QInt a;//nay them vo ne
	string tmp, hex;
	int i = 127;
	while (s.length() > 0) {
		tmp = s[s.length() - 1];
		hex = mp[tmp];
		for (int j = 3; j >= 0; j--) {
			if (hex[j] == '1')
				a.data[i / 32] |= 1 << (31 - (i % 32));
			i--;
		}
		s.erase(s.length() - 1, 1);
	}

	/*for (int i = 0; i < 4; i++)
		cout << data[i] << " ";*/
	return a;
}

Conversion::Conversion()
{
}

Conversion::~Conversion()
{
}
