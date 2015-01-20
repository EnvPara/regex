#ifndef _TRANSTABLE_H_
#define _TRANSTABLE_H_
class TransTable
{
public:
	TransTable(int rowNum, int colNum);
	~TransTable();
	void SetValue(int i, int j, int value);
	int GetValue(int i, int j);
	int Transit(int current, char input, char *edge);
	void clear();
	int rowNumber;
	int colNumber;
	int **Matrix;//ถþฮฌสýื้
};
#endif