#include <iostream>
#include "DFA.h"
using namespace std;
int main()
{
	DFA DFA_each;
	DFA_each.InputRegex();//��������
	DFA_each.InsertNode();//��������
	DFA_each.RegextoPost();//תΪ��׺���ʽ
	DFA_each.GetEdgeNumber();//ɨ���沨��ʽ�г������������ַ�����Ŀ
	DFA_each.Thompson();//��Thompson���취����NFA
	DFA_each.NFAtoDFA();//�����Ӽ����취 NFA��DFA
	DFA_each.SetStart();//��NFA״̬ͼ��1�Ž����ΪNFAͼ�Ŀ�ʼ״̬
	DFA_each.GetAcceptState();////�õ�NFA�Ľ���״̬����
	return 0;
}