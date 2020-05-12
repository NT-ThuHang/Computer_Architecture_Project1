#ifndef __COMPARISON_H__
#define __COMPARISON_H__

#include "QInt.h"

/* Class thực hiện so sánh 2 số QInt, và gán bằng cho QInt */
class Comparison
{
public:
	int compare(QInt a, QInt b);
	void assign(QInt& a, QInt b);
	Comparison();
	~Comparison();
};

#endif // !__COMPARISON_H__
