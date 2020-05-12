#pragma once
#include <fstream>
#include <vector>
#include <sstream>
#include "QInt.h"
#include "Qfloat.h"
#include "Conversion.h"
using namespace std;

class FileHandler
{
private:
	string inp;
	string out;
	string type;	// 1: QInt, 2:QFloat
public:
	FileHandler();
	FileHandler(string inpFileName, string outFileName, string dataType);
	~FileHandler();

	QInt readQInt(string num, string base);
	void writeQInt(QInt x, string base, ofstream& fileOut);

	void execute(string inpFileName, string outFileName, string dataType);
	void QIntConversion(vector<string> args, ofstream& fileOut);
	void QIntOperation(vector<string> args, ofstream& fileOut);
};

