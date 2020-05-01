#include "BasicOperation.h"

QInt BasicOperation::AddQInt(QInt a, QInt b)
{
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

QInt BasicOperation::SubQInt(QInt a, QInt b)
{
	b.convert2complement();
	QInt ans = AddQInt(a, b);
	return ans;
}


QInt BasicOperation::MultipleQInt(QInt a, QInt b)
{
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

QInt BasicOperation::DivideQInt(QInt a, QInt b)
{
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

QInt BasicOperation::ModQInt(QInt a, QInt b)
{
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

BasicOperation::BasicOperation()
{
}

BasicOperation::~BasicOperation()
{
}



