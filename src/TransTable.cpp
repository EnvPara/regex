#include "TransTable.h"
//构造函数
TransTable::TransTable(int rowNum,int colNum)
{
	rowNumber = rowNum;
	colNumber = colNum;
	Matrix = (int **)(new int*[rowNumber]);
	for (int i = 0; i < rowNumber; i++)
		Matrix[i] = new int[colNumber];
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