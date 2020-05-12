#define _CRT_SECURE_NO_WARNINGS
#include "QInt.h"
#include "Conversion.h"
#include "FileHandler.h"
using namespace std;
int main(int argc, char* argv[])
{
	// Ktra tham số dòng lệnh phải có 4 thành phần: file exe, file inp, file out, kiểu dữ liệu
	if (argc < 4 || argc > 4)
	{
		cout << "Tham so dong lenh khong hop le!" << endl;
		return -1;
	}

	string inp = argv[1];
	string out = argv[2];
	string type = argv[3];

	// dùng để test đọc file bth
	/*string inp = "QInt_input.txt";
	string out = "QInt_output.txt";
	string type = "1";*/
	/*string inp = "QFloat_input.txt";
	string out = "QFloat_output.txt";
	string type = "2";*/

	FileHandler f;
	f.execute(inp, out, type);

	//system("pause");
	return 0;
}