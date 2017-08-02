#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//  Lomuto版本
//int partition(vector<int> &A, int left, int right)
//{
//	int key = A[right];	//选最后一个元素作为基准
//	int pre = left - 1;
//	for (int i = left; i < right; ++i)
//	{
//		if (A[i] <= key)
//		{
//			++pre;
//			swap(A[pre], A[i]);
//		}
//	}
//	swap(A[pre + 1], A[right]);
//	return pre+1;
//}

//  Hoare版本
int partition(vector<int> &A, int left, int right)
{
	int key = A[left];	//选第一个元素作为基准
	while (left < right)
	{
		while (left < right && A[right] >= key)
			--right;
		swap(A[left], A[right]);

		while (left < right && A[left] <= key)
			++left;
		swap(A[left], A[right]);
	}
	return left;
}

void quick_sort(vector<int> &A,int left, int right)
{
	if (left < right)
	{
		int index = partition(A, left, right);
		quick_sort(A, left, index-1);
		quick_sort(A, index + 1, right);
	}
}

void Quick_sort(vector<int> &A)
{
	int len = A.size();
	quick_sort(A, 0, len-1);
}

int main()
{
	int a1[] = {13,3,18,5,2,17,8,12,10,9,6,4,1,11,15,14,7,16};
	vector<int> a(&a1[0], &a1[18]);

	Quick_sort(a);

	for (auto it : a)
		cout << it << "  ";

	system("pause");
	return 0;
}