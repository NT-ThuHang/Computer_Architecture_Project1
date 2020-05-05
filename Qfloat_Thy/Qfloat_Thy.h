#ifndef _Qfloat_H
#define _Qfloat_H
#include <iostream>
#include <string>
using namespace std;

class Qfloat
{
private:
	int data[4] = { 0 };
public:
	static string divideBy2(string s);
	static string sum(string a, string b);
	static string multiply(string a, int b);
	static string multiplication(string a, string b);
	static string Pow(string x, int k);
	string negativePowOf2(string decimal);
	bool isZero();
	bool isInf();
	bool isNaN();
	void ScanQfloat(string s, int k);
	string PrintQfloat();
	Qfloat();
	~Qfloat();
};

#endif // !_Qfloat_H



