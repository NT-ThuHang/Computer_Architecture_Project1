#include "FileHandler.h"

FileHandler::FileHandler()
{
}

FileHandler::FileHandler(string inpFileName, string outFileName, string dataType)
{
	this->inp = inpFileName;
	this->out = outFileName;
	this->type = dataType;
}

FileHandler::~FileHandler()
{
}

QInt FileHandler::readQInt(string num, string base)
{
	QInt x;
	if (base == "10")
	{
		stringstream s;
		s << num;
		s >> x;
	}
	else if (base == "2")
	{
		Conversion convert;
		x = convert.BinToDec(num);
	}
	else if (base == "16")
	{
		Conversion convert;
		x = convert.HexToDec(num);
	}
	return x;
}

void FileHandler::writeQInt(QInt x, string base, ofstream& fileOut)
{
	if (base == "10")
	{
		fileOut << x << endl;
		//cout << x << endl;
	}
	else if (base == "2")
	{
		Conversion convert;
		string bin = convert.DecToBin(x);
		fileOut << bin << endl;
		//cout << bin << endl;
	}
	else if (base == "16")
	{
		Conversion convert;
		string hex = convert.DecToHex(x);
		fileOut << hex << endl;
		//cout << hex << endl;
	}
}

/*
Đọc từng dòng trong file input và gọi hàm xử lí thích hợp
*/
void FileHandler::execute(string inpFileName, string outFileName, string dataType)
{
	//cout << "Input: " << inpFileName << endl;
	//cout << "Output: " << outFileName << endl;
	this->inp = inpFileName;
	this->out = outFileName;
	this->type = dataType;

	// Mở file input và xử lí lỗi
	ifstream fileInp(inpFileName);
	if (fileInp.fail())
	{
		cout << "Loi khong mo dc file " << inpFileName << endl;
		return;
	}
	// Mở file output
	ofstream fileOut(outFileName);
	if (fileOut.fail())
	{
		cout << "Loi khong mo dc file " << outFileName << endl;
		return;
	}

	while (!fileInp.eof())
	{
		// Đọc 1 dòng
		string line;
		getline(fileInp, line);
		
		// Phân tích từng thành phần của dòng
		vector<string> args;
		stringstream spliter;
		spliter << line;
		while (!spliter.eof())
		{
			string temp;
			spliter >> temp;
			args.push_back(temp);
		}

		// Xử lí phép toán tương ứng
		// Với kiểu QInt
		if (type == "1")
		{
			// QInt: chuyển đổi cơ số
			if (args.size() == 3 && args[1] != "~")
			{
				this->QIntConversion(args, fileOut);
			}
			// QInt: toán tử tính toán
			else if (args.size() == 4 || (args.size() == 3 && args[1] == "~"))
			{
				this->QIntOperation(args, fileOut);
			}
		}
		// Với kiểu QFloat (xử lí sau)
		else if (type == "2")
		{
			// QFloat: đọc input dạng số thực dec
			if (args.size() == 3 && args[0] == "10" and args[1] == "2")
			{
				Qfloat x;
				stringstream s;
				s << args[2];
				s >> x;

				fileOut << x.DectoBin() << endl;
				//cout << x.DectoBin() << endl;
			}
			// QFloat: đọc input dãy bit biểu diễn số chấm động
			else if (args.size() == 3 && args[0] == "2" and args[1] == "10")
			{
				Qfloat x;
				x = Qfloat::BinToDec(args[2]);

				fileOut << x << endl;
				//cout << x << endl;
			}
		}
		
	}

	fileInp.close();
	fileOut.close();
}

// Xử lí các yêu cầu chuyển đổi cơ số
void FileHandler::QIntConversion(vector<string> args, ofstream& fileOut)
{
	//QInt x;  // lưu số nguyên input (base 10)

	// Xử lí đọc số input ở nhiều dạng cơ số
	QInt x = this->readQInt(args[2], args[0]);

	// Xử lí chuyển sang cơ số theo yêu cầu
	this->writeQInt(x, args[1], fileOut);
}

void FileHandler::QIntOperation(vector<string> args, ofstream& fileOut)
{
	QInt x, y, res;
	bool comp;

	// TH đặc biệt: toán tử ~ chỉ có 1 toán hạng
	if (args[1] == "~")
	{
		// Đọc số input
		x = this->readQInt(args[2], args[0]);
		x = ~x;
		this->writeQInt(x, args[0], fileOut);
		return;
	}

	// Đọc số input
	x = this->readQInt(args[1], args[0]);
	y = this->readQInt(args[3], args[0]);
	
	if (args[2] == "+")
	{
		res = x + y;
	}
	else if (args[2] == "-")
	{
		res = x - y;
	}
	else if (args[2] == "*")
	{
		res = x * y;
	}
	else if (args[2] == "/")
	{
		if (args[3] == "0")
		{
			fileOut << "Phep chia khong hop le!" << endl;
			return;
		}
		res = x / y;
	}
	else if (args[2] == "%")
	{
		if (args[3] == "0")
		{
			fileOut << "Phep chia khong hop le!" << endl;
			return;
		}
		res = x % y;
	}
	else if (args[2] == ">")
	{
		comp = x > y;
		if (comp)
			fileOut << "True" << endl;
		else
			fileOut << "False" << endl;
		return;
	}
	else if (args[2] == "<")
	{
		comp = x < y;
		if (comp)
			fileOut << "True" << endl;
		else
			fileOut << "False" << endl;
		return;
	}
	else if (args[2] == "==")
	{
		comp = x == y;
		if (comp)
			fileOut << "True" << endl;
		else
			fileOut << "False" << endl;
		return;
	}
	else if (args[2] == ">=")
	{
		comp = x >= y;
		if (comp)
			fileOut << "True" << endl;
		else
			fileOut << "False" << endl;
		return;
	}
	else if (args[2] == "<=")
	{
		comp = x <= y;
		if (comp)
			fileOut << "True" << endl;
		else
			fileOut << "False" << endl;
		return;
	}
	else if (args[2] == "&")
	{
		res = x & y;
	}
	else if (args[2] == "|")
	{
		res = x | y;
	}
	else if (args[2] == "^")
	{
		res = x ^ y;
	}
	else if (args[2] == "<<")
	{
		int z = stoi(args[3]);
		res = x << z;
	}
	else if (args[2] == ">>")
	{
		int z = stoi(args[3]);
		res = x >> z;
	}
	else if (args[2] == "ror")
	{
		int z = stoi(args[3]);
		res = x.ror(z);
	}
	else if (args[2] == "rol")
	{
		int z = stoi(args[3]);
		res = x.rol(z);
	}

	this->writeQInt(res, args[0], fileOut);
}
