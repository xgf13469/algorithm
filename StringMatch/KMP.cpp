#include <string>
#include <iostream>
using namespace std;

//KMP �㷨
void getNext(const string &pstr, int next[])
{
	next[0] = 0;//�ַ����ĵ�һ���ַ������ǰ��׺����Ϊ0
	int j = 1;
	int	k = 0;
	for (; j < pstr.size(); ++j)//�ӵڶ����ַ���ʼ
	{
		while (k > 0 && pstr[j] != pstr[k])//�ݹ�����P[0]������P[i]��������ͬ��ǰ��׺���� k
			k = next[k - 1];
		if (pstr[j] == pstr[k])//�����ȣ���ô�����ͬǰ��׺���ȼ�1
			k++;

		next[j] = k;
	}
}
int kmp(const string src, const string pstr, int next[])
{
	int i = 0;
	int	k = 0;
	for (; i < src.size(); ++i)	//ÿ��ѭ��i����ƶ�1λ
	{
		while (k > 0 && src[i] != pstr[k])	//�����ƥ�䣬j �ƶ�����ʼλ��j=0������ƥ���λ��
			k = next[k - 1];

		if (src[i] == pstr[k])	//���ƥ�䣬��j Ҳ����ƶ�1λ
			k++;

		//�ҵ�һ���ͷ���
		if (k == pstr.size())
			return i - pstr.size() + 1;
	}
	return -1;
}

int main()
{
	string s("BBC ABCDAB ABCDABCDABDE");
	string p("ABCDABD");
	int next[100];
	getNext(p, next);
	for (int i = 0; i < p.size(); ++i)
		cout << p[i] << " " << next[i] << endl;
	cout << "match at : " << kmp(s, p, next)<< endl;
	
	system("pause");
	return 0;
}