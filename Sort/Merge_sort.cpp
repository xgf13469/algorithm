#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//合并两个有序数组A[left..mid]和A[mid+1..right],使A有序
void merge(vector<int> &A, int left, int mid, int right)
{
	int index = 0;
	int i = left;	//第一个数组起点
	int j = mid+1;	//第二个数则起点

	vector<int> temp(right - left + 1);
	while (i <= mid && j <= right)
	{
		if (A[i] < A[j])
			temp[index++] = A[i++];
		else
			temp[index++] = A[j++];
	}
	while (i <= mid)
		temp[index++] = A[i++];
	while (j <= right)
		temp[index++] = A[j++];

	for (i = left,j=0; i <= right; i++,j++)
		A[i] = temp[j];
}
void mergesort(vector<int> &A, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		mergesort(A, left, mid);
		mergesort(A, mid + 1, right);
		merge(A, left, mid, right);
	}
}
void Merge_sort(vector<int> &A)
{
	int len = A.size();
	mergesort(A, 0, len-1);
}

int main()
{
	int a1[] = {13,3,18,5,2,17,8,12,10,9,6,4,1,11,15,14,7,16};
	vector<int> a(&a1[0], &a1[18]);

	Merge_sort(a);

	for (auto it : a)
		cout << it << "  ";

	system("pause");
	return 0;
}