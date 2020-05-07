#ifndef __QINT_H__
#define __QINT_H__
#include <iostream>
#include <string>
using namespace std;

class QInt
{
private:
	int data[4] = { 0 };
public:
	void convert2complement();
	void ScanQInt(string s);
	string PrintQInt();

	bool operator < (QInt a);
	bool operator > (QInt a);
	bool operator == (QInt a);
	bool operator <= (QInt a);
	bool operator >= (QInt a);
	QInt operator = (QInt a);
	friend class Comparison;
	friend class Conversion;
	QInt();
	~QInt();
};

#endif // !__QINT_H__



