#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


//������
void HeapAdjustDown(vector<int> &A, int start, int end)		//start ���µ�����ֱ���ҵ����ʵ�λ��
{
	int cur = A[start];		//��ǰ�ڵ�
	int child = 2 * start + 1;		//��ǰ�ڵ������
	while (child < end)
	{
		//�ҳ����Һ���������, child+1Ϊ�Һ���
		if (child + 1 < end && A[child + 1] > A[child])
			child++;
		
		//�����ǰ�ڵ�������Һ��ӽڵ㣬���õ���
		if (cur >= A[child])
			break;
		
		A[start] = A[child];	//������ӽڵ�ֵ������ǰ�ڵ�
		start = child;		//���������ӽڵ�
		child = 2 * child + 1;
	}
	A[start] = cur;
}

//��������
void BuildHeap(vector<int> &A)
{
	int len = A.size();
	
	//�ӵ�һ����Ҷ�ӽڵ�len/2-1 ��ʼ������
	for (int i = len / 2 - 1; i >= 0; i--)
		HeapAdjustDown(A, i, len);
}

void Heap_sort(vector<int> &A)
{
	int len = A.size();

	BuildHeap(A);
	for (int i = len - 1; i > 0; i--)
	{
		//�Ѷ�Ԫ�أ����ֵ�������һ��Ԫ�ؽ�����Ȼ�����ʣ�µ�Ԫ�أ������һ��Ԫ���⣩
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