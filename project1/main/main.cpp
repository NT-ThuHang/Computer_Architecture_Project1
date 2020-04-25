#include "QInt.h"

int main()
{
	string s = "-891243829999";

	QInt x;
	x.ScanQInt(s);
	cout << x.PrintQInt();
}