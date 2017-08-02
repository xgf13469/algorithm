#include <string>
#include <iostream>
using namespace std;

//KMP 算法
void getNext(const string &pstr, int next[])
{
	next[0] = 0;//字符串的第一个字符的最大前后缀长度为0
	int j = 1;
	int	k = 0;
	for (; j < pstr.size(); ++j)//从第二个字符开始
	{
		while (k > 0 && pstr[j] != pstr[k])//递归的求出P[0]···P[i]的最大的相同的前后缀长度 k
			k = next[k - 1];
		if (pstr[j] == pstr[k])//如果相等，那么最大相同前后缀长度加1
			k++;

		next[j] = k;
	}
}
int kmp(const string src, const string pstr, int next[])
{
	int i = 0;
	int	k = 0;
	for (; i < src.size(); ++i)	//每次循环i向后移动1位
	{
		while (k > 0 && src[i] != pstr[k])	//如果不匹配，j 移动到开始位（j=0）或者匹配的位置
			k = next[k - 1];

		if (src[i] == pstr[k])	//如果匹配，则j 也向后移动1位
			k++;

		//找到一个就返回
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