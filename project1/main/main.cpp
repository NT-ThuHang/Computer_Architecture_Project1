#include "QInt.h"
#include "Comparison.h"

int main()
{
	// Thy test
	string s = "-4312413414";
	string t = "-1341251451243";
	QInt x, y;
	x.ScanQInt(s);
	y.ScanQInt(t);

	if (x >= y)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	x = y;
	cout << x.PrintQInt() << endl;
}