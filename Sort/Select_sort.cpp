#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


//—°‘Ò≈≈–Ú
void Select_sort(vector<int> &A)
{
	int len = A.size();
	for (int i = 0; i < len - 1; ++i)
	{
		int min = i;
		for (int j = i + 1; j < len; ++j)
			if (A[j] < A[min])
				min = j;

		swap(A[min], A[i]);
	}
}

int main()
{
	int a1[] = {13,3,18,5,2,17,8,12,10,9,6,4,1,11,15,14,7,16};
	vector<int> a(&a1[0], &a1[18]);

	Select_sort(a);

	for (auto it : a)
		cout << it << "  ";

	system("pause");
	return 0;
}