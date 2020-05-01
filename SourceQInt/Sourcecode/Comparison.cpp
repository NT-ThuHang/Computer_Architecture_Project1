#include "Comparison.h"

/*Hàm so sánh số QInt a, b với đầu ra:
- a = b: 0
- a < b: -1
- a > b: 1
*/
int Comparison::compare(QInt a, QInt b)
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

/*Hàm gán a = b*/
void Comparison::assign(QInt& a, QInt b)
{
	for (int i = 0; i < 4; i++)
		a.data[i] = b.data[i];
}

Comparison::Comparison()
{
}


Comparison::~Comparison()
{
}
