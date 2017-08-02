#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

//基数排序LSD:先地位后高位

/********************************************************
*函数名称：GetNumInPos
*参数说明：num 一个整形数据
*		   pos 表示要获得的整形的第pos位数据
*说明：    找到num的从低到高的第pos位的数据
*********************************************************/
int GetNumInPos(int num, int pos)
{
	int temp = 1;
	for (int i = 0; i < pos - 1; i++)
		temp *= 10;

	return (num / temp) % 10;
}

#define MAXPOS 10    //最高位的位数
void Radix_sort(vector<int> &A)
{
	int len = A.size();
	vector<queue<int>> radixArray(10);  //分为0~9的序列空间，用队列保存每个桶分配的数据

	for (int pos = 1; pos <= MAXPOS; pos++)    //从个位开始到最高位数
	{
		for (int i = 0; i < len; i++)    //分配过程
		{
			int num = GetNumInPos(A[i], pos);
			radixArray[num].push(A[i]);
		}

		for (int i = 0, j = 0; i < 10; i++)    //收集
		{
			while (!radixArray[i].empty())
			{
				A[j++] = radixArray[i].front();		//取队列首部数据依次插入原数组
				radixArray[i].pop();
			}
		}
	}
}

int main()
{
	int a3[] = { 13, 53, 16, 82, 6, 11, 43, 22, 35, 12 };
	vector<int> a(&a3[0], &a3[10]);

	Radix_sort(a);
	
	for (auto it : a)
		cout << it << "  ";

	system("pause");
	return 0;
}