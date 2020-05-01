#pragma once
#ifndef  __CONVERSION_H__
#define __CONVERSION_H__

#include "QInt.h"
#include <map>

class Conversion
{
private:
	int data[4] = { 0 };
public:
	/* Quy uoc QInt la Dec vi ham in ket qua da chuyen qua thap phan nen cac chuyen doi qua thap phan chi can doi qua QInt*/
	string DecToBin(QInt);			//Chuyen Tu Thap Phan sang Nhi Phan
	QInt BinToDec(string);			//Chuyen Tu Nhi Phan sang Thap Phan
	string BinToHex(string);		//Chuyển từ chuỗi nhị phân sang thập lục phân
	string DecToHex(QInt);		    //chuyển từ chuỗi thập phân sang thập lục phân
	/* Cho DecToHex co doi mot xiu cho du lieu vao thay vi string la QInt vi luc nhap vao da auto chuyen tu chuoi Thap phan sang QInt */
	map<string, string> BinToHexValue();	//chứa các giá trị nhị phân tương ứng với thập lục phân
	QInt HexToDec(string);		//set chuỗi thập lục phân vào QInt
	/*SetToHex tuong duong voi HexToDec nen doi la cho giong cau truc dat ten ben tren nhe! va kieu tra ve la QInt luon*/


	Conversion();
	~Conversion();
};
#endif // ! __CONVERSION_H__
