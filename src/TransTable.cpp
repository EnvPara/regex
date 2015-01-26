#include "TransTable.h"
//���캯��
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
//��������
TransTable::~TransTable()
{
	clear();
}
//����Ԫ�ص�ֵ
void TransTable::SetValue(int i, int j, int value)
{
	Matrix[i][j] = value;
}
//�õ�Ԫ�ص�ֵ
int  TransTable::GetValue(int i, int j)
{
	return Matrix[i][j];
}
// ״̬ת�ƺ���
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
// ���ת�ƾ���
void TransTable::clear(void)
{
	for (int i = 0; i<rowNumber; i++)
	{
		delete[] Matrix[i];
	}
	delete Matrix;
}