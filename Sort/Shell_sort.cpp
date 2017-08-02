#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


//希尔排序
//希尔排序与插入排序很相似，插入排序相当于每次 d=1
void Shell_sort(vector<int> &A)
{
	int len = A.size();
	int d = len / 2;
	while (d > 0)
	{
		for (int i = d; i < len; ++i)
		{
			int key = A[i];
			int j = i - d;
			while (j >= 0 && A[j] > key)
			{
				A[j + d] = A[j];
				j -= d;
			}
			A[j + d] = key;
		}
		d /= 2;
	}
}


//插入排序
void Insert_sort(vector<int> &A)
{
	int len = A.size();
	for (int i = 1; i < len; ++i)
	{
		int key = A[i];
		int j = i - 1;
		while (j >= 0 && A[j] > key)
		{
			A[j + 1] = A[j];
			--j;
		}
		A[j + 1] = key;
	}
}

int main()
{
	int a1[] = {13,3,18,5,2,17,8,12,10,9,6,4,1,11,15,14,7,16};
	vector<int> a(&a1[0], &a1[18]);

	Shell_sort(a);
	
	for (auto it : a)
		cout << it << "  ";

	system("pause");
	return 0;
}