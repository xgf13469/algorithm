#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

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


//LSD:从个位开始到最高位数
void Radix_sort(vector<int> &A)
{
	int len = A.size();
	vector<vector<int>> radixArray(10);  //分为0~9的序列空间

	for (int pos = 1; pos <= MAXPOS; pos++)    //从个位开始到最高位数
	{
		for (int i = 0; i < len; i++)    //分配过程
		{
			int num = GetNumInPos(A[i], pos);
			radixArray[num].push_back(A[i]);
		}

		for (int i = 0, j = 0; i < 10; i++)    //收集
		{
			while (!radixArray[i].empty())
			{
				A[j++] = radixArray[i].front();		//取首部数据依次插入原数组
				radixArray[i].erase(radixArray[i].begin());		//移除首部元素
			}
		}
	}
}


//MSD:从最高位开始到个位
void RadixSort(vector<int> &A, int d)
{
	int len = A.size();
	vector<vector<int>> radixArray(10);  //分为0~9的序列空间，用队列保存每个桶分配的数据

	//位数大于0，且数组长度大于1
	if (d >= 1 && len > 1)
	{
		for (int i = 0; i < len; i++)    //分配过程
		{
			int num = GetNumInPos(A[i], d);
			radixArray[num].push_back(A[i]);
		}

		for (int i = 0, j = 0; i < 10; i++)    //收集
		{
			RadixSort(radixArray[i], d-1);		//递归，对子桶从次高位开始分配
			while (!radixArray[i].empty())
			{
				A[j++] = radixArray[i].front();		//取队列首部数据依次插入原数组
				radixArray[i].erase(radixArray[i].begin());
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
		cout << "LSD :" << it << "  ";

	Radix_sort(a, 2);
	
	for (auto it : a)
		cout << "MSD :" << it << "  ";
	
	system("pause");
	return 0;
}