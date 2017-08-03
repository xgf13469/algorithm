#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

/********************************************************
*�������ƣ�GetNumInPos
*����˵����num һ����������
*		   pos ��ʾҪ��õ����εĵ�posλ����
*˵����    �ҵ�num�Ĵӵ͵��ߵĵ�posλ������
*********************************************************/
int GetNumInPos(int num, int pos)
{
	int temp = 1;
	for (int i = 0; i < pos - 1; i++)
		temp *= 10;

	return (num / temp) % 10;
}

#define MAXPOS 10    //���λ��λ��


//LSD:�Ӹ�λ��ʼ�����λ��
void Radix_sort(vector<int> &A)
{
	int len = A.size();
	vector<vector<int>> radixArray(10);  //��Ϊ0~9�����пռ�

	for (int pos = 1; pos <= MAXPOS; pos++)    //�Ӹ�λ��ʼ�����λ��
	{
		for (int i = 0; i < len; i++)    //�������
		{
			int num = GetNumInPos(A[i], pos);
			radixArray[num].push_back(A[i]);
		}

		for (int i = 0, j = 0; i < 10; i++)    //�ռ�
		{
			while (!radixArray[i].empty())
			{
				A[j++] = radixArray[i].front();		//ȡ�ײ��������β���ԭ����
				radixArray[i].erase(radixArray[i].begin());		//�Ƴ��ײ�Ԫ��
			}
		}
	}
}


//MSD:�����λ��ʼ����λ
void RadixSort(vector<int> &A, int d)
{
	int len = A.size();
	vector<vector<int>> radixArray(10);  //��Ϊ0~9�����пռ䣬�ö��б���ÿ��Ͱ���������

	//λ������0�������鳤�ȴ���1
	if (d >= 1 && len > 1)
	{
		for (int i = 0; i < len; i++)    //�������
		{
			int num = GetNumInPos(A[i], d);
			radixArray[num].push_back(A[i]);
		}

		for (int i = 0, j = 0; i < 10; i++)    //�ռ�
		{
			RadixSort(radixArray[i], d-1);		//�ݹ飬����Ͱ�Ӵθ�λ��ʼ����
			while (!radixArray[i].empty())
			{
				A[j++] = radixArray[i].front();		//ȡ�����ײ��������β���ԭ����
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