#include "TransTable.h"
//构造函数
TransTable::TransTable(int rowNum, int colNum)
{
	rowNumber = rowNum;
	colNumber = colNum;
	Matrix[rowNumber][colNumber] = { 0 };
}
void TransTable::TransitCol(int num)
{
	colNumber = num;
}
void TransTable::TransitRow(int num)
{
	rowNumber = num;
}
//析构函数
TransTable::~TransTable()
{
	clear();
}
//设置元素的值
void TransTable::SetValue(int i, int j, int value)
{
	Matrix[i][j] = value;
}
//得到元素的值
int  TransTable::GetValue(int i, int j)
{
	return Matrix[i][j];
}
// 状态转移函数
int TransTable::Transit(int current, char input, char *edge)
{
	for (int i = 0; edge[i] != '\0'; i++)
	{
		if (input == edge[i])
		{
			return Matrix[current][i];
		}
	}
	return -1;
}
// 清空转移矩阵
void TransTable::clear(void)
{
	for (int i = 0; i<rowNumber; i++)
	{
		delete[] Matrix[i];
	}
	delete Matrix;
}