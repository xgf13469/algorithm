#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


//堆排序
void HeapAdjustDown(vector<int> &A, int start, int end)		//start 向下调整，直到找到合适的位置
{
	int cur = A[start];		//当前节点
	int child = 2 * start + 1;		//当前节点的左孩子
	while (child < end)
	{
		//找出左右孩子中最大的, child+1为右孩子
		if (child + 1 < end && A[child + 1] > A[child])
			child++;
		
		//如果当前节点大于左右孩子节点，则不用调整
		if (cur >= A[child])
			break;
		
		A[start] = A[child];	//把最大孩子节点值赋给当前节点
		start = child;		//继续调整子节点
		child = 2 * child + 1;
	}
	A[start] = cur;
}

//建立最大堆
void BuildHeap(vector<int> &A)
{
	int len = A.size();
	
	//从第一个非叶子节点len/2-1 开始调整堆
	for (int i = len / 2 - 1; i >= 0; i--)
		HeapAdjustDown(A, i, len);
}

void Heap_sort(vector<int> &A)
{
	int len = A.size();

	BuildHeap(A);
	for (int i = len - 1; i > 0; i--)
	{
		//堆顶元素（最大值）和最后一个元素交换，然后调整剩下的元素（除最后一个元素外）
		swap(A[i], A[0]);
		HeapAdjustDown(A, 0, i - 1);
	}
}


int main()
{
	int a1[] = {13,3,18,5,2,17,8,12,10,9,6,4,1,11,15,14,7,16};
	vector<int> a(&a1[0], &a1[18]);

	Heap_sort(a);
	
	for (auto it : a)
		cout << it << "  ";

	system("pause");
	return 0;
}