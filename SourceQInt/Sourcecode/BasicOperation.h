#pragma once
#ifndef __BASICOPERATION_H__
#define __BASICOPERATION_H__

#include "QInt.h"
class BasicOperation
{
public:
	QInt AddQInt(QInt, QInt);
	QInt SubQInt(QInt, QInt);
	QInt MultipleQInt(QInt, QInt);
	QInt DivideQInt(QInt, QInt);
	QInt ModQInt(QInt, QInt);
	BasicOperation();
	~BasicOperation();
};
#endif // !__COMPARISON_H__
